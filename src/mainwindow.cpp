#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "graphic/GraphicItemManager.h"
#include "graphic/GraphicRect.h"
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
		srand(time(NULL));
		auto rect = new GraphicRect();
		
		int x = 20 * idx;
		int y = 20 * idx;
		rect->setX(x);
		rect->setY(y);
		rect->setWidth(20);
		rect->setHeight(20);
		++idx;
		GraphicItemManager::instance()->addItem(rect);
		render();
	});

	connect(ui->centralwidget, &GraphicWidget::signal_mousePos, this, &MainWindow::slot_PrintMousePos);

	connect(ui->actioncreateRect, &QAction::toggled, ui->centralwidget, [this](bool bCheck)
	{
		if (bCheck)
		{
			std::shared_ptr<RectOperator> spRectOperator =  std::make_shared<RectOperator>();
			ui->centralwidget->slot_setCADTool(spRectOperator);
			connect(spRectOperator.get(), &CADOperator::signal_exit, this, [this]() {ui->actioncreateRect->setChecked(false); });
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

void MainWindow::slot_PrintMousePos(const QPoint& pos)
{
	ui->statusbar->showMessage(QString("x:%1 y:%2").arg(pos.x()).arg(pos.y()));
}
