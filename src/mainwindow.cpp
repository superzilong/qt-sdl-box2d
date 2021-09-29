#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Graphic/GraphicItemManager.h"
#include "Graphic/GraphicRect.h"
#include <QDebug>
#include <QMouseEvent>

#include "GraphicWidget.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	setMouseTracking(true);
	centralWidget()->setMouseTracking(true);
	
	setWindowTitle("QMainWindow SDL Rendering GraphicWidget");
	setBaseSize(640, 480);
	resize(640, 480);

	connect(ui->actionRender, &QAction::triggered, this, [this]()
	{
		auto rect = new GraphicRect();
		int x = 1 * idx;
		int y = 1 * idx;
		rect->setX(x);
		rect->setY(y);
		rect->setWidth(1);
		rect->setHeight(1);
		rect->setColor(0xFF, 0xB3, 0x44);
		++idx;
		GraphicItemManager::instance()->addItem(rect);
		render();
	});

	connect(ui->centralwidget, &GraphicWidget::signal_mousePos, this, &MainWindow::slot_printMousePos);

	connect(ui->actioncreateRect, &QAction::toggled, ui->centralwidget, [this](bool bCheck)
	{
		if (bCheck)
		{
			auto currentCADTool = ui->centralwidget->getCurrentCADTool();
			if (currentCADTool)
			{
				emit currentCADTool->signal_exit();
			}
			std::shared_ptr<RectOperator> spRectOperator =  std::make_shared<RectOperator>(ui->centralwidget->getCoordConverter());
			ui->centralwidget->slot_setCADTool(spRectOperator);
			connect(spRectOperator.get(), &CADOperator::signal_exit, this, [this]() {ui->actioncreateRect->setChecked(false); });
		}
		else
		{
			ui->centralwidget->slot_setCADTool(nullptr);
		}
	});

	connect(ui->actionCreatCircle, &QAction::toggled, ui->centralwidget, [this](bool bCheck)
	{
		if (bCheck)
		{
			auto currentCADTool = ui->centralwidget->getCurrentCADTool();
			if (currentCADTool)
			{
				emit currentCADTool->signal_exit();
			}
			std::shared_ptr<CircleOperator> spCircleOperator = std::make_shared<CircleOperator>(ui->centralwidget->getCoordConverter());
			ui->centralwidget->slot_setCADTool(spCircleOperator);
			connect(spCircleOperator.get(), &CADOperator::signal_exit, this, [this]() {ui->actionCreatCircle->setChecked(false); });
		}
		else
		{
			ui->centralwidget->slot_setCADTool(nullptr);
		}
	});
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::render()
{
	this->ui->centralwidget->SDLRepaint();
}

void MainWindow::slot_printMousePos(const QPoint& pos)
{
	ui->statusbar->showMessage(QString("x:%1 y:%2").arg(pos.x()).arg(pos.y()));
}
