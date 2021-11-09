#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "Graphic/GraphicItemManager.h"
#include "Graphic/GraphicRect.h"
#include <QMouseEvent>

#include "GraphicWidget.h"
#include "CAD/CADOperatorMgr.h"
#include "PhysicalEngine/PhysicalEngine.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	setMouseTracking(true);
	centralWidget()->setMouseTracking(true);
	
	setWindowTitle("QMainWindow SDL Rendering GraphicWidget");
	//setBaseSize(1200, 900);
	resize(1200, 900);

	connect(ui->actionRender, &QAction::triggered, this, [this]()
	{
		auto rect = new GraphicRect();
		int x = 1 * idx;
		int y = 1 * idx;
		rect->setLeft(x);
		rect->setBottom(y);
		rect->setWidth(1);
		rect->setHeight(1);
		rect->setColor(0xFF, 0xB3, 0x44);
		++idx;
		GraphicItemManager::instance()->addItem(rect);
		render();
	});

	connect(ui->centralwidget, &GraphicWidget::signal_mousePos, this, &MainWindow::slot_printMousePos);

    CADOperatorMgr* pCADMgr = CADOperatorMgr::instance();
	pCADMgr->init(ui->centralwidget->getCoordConverter());

	auto pCADActions = pCADMgr->getAllActions();
    for (auto&& p_cad_action : pCADActions)
    {
		ui->toolBar->addAction(p_cad_action);
    }

	QAction* play = new QAction("play", this);
	play->setCheckable(true);
	ui->toolBar->addAction(play);
	connect(play, &QAction::toggled, this, [](bool tog) {PhysicalEngine::instance()->setIsRunning(tog); });
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
