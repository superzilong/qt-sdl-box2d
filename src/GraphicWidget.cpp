#include "GraphicWidget.h"

#include "Graphic/GraphicItem.h"
#include "Graphic/GraphicItemManager.h"
#include "CAD/CADOperator.h"

#include <QMouseEvent>
#include <SDL2_gfxPrimitives.h>

#include "CAD/CADOperatorMgr.h"
#include "Graphic/GraphicCircle.h"
#include "Graphic/GraphicRect.h"
#include "PhysicalEngine/PhysicalEngine.h"


void GraphicWidget::keyPressEvent(QKeyEvent* event)
{
	auto mgr = CADOperatorMgr::instance();
	auto pOp = mgr->getCurrentOp();
	if (pOp)
	{
		pOp->keyPressEvent(event);
	}
}

void GraphicWidget::mousePressEvent(QMouseEvent* event)
{
	auto mgr = CADOperatorMgr::instance();
	auto pOp = mgr->getCurrentOp();
	if (pOp)
	{
		pOp->mousePressEvent(event);
	}
}

void GraphicWidget::mouseMoveEvent(QMouseEvent* event)
{
	auto mgr = CADOperatorMgr::instance();
	auto pOp = mgr->getCurrentOp();
	if (pOp)
	{
		pOp->mouseMoveEvent(event);
	}
	emit signal_mousePos(event->pos());
}

void GraphicWidget::mouseReleaseEvent(QMouseEvent* event)
{
	auto mgr = CADOperatorMgr::instance();
	auto pOp = mgr->getCurrentOp();
	if (pOp)
	{
		pOp->mouseReleaseEvent(event);
	}
}

void GraphicWidget::Init()
{
	int w = width();
	int h = height();

	m_viewTransform.scale(50, 50);
	m_viewTransform.translate(0, -h/(50. * 4));

	m_projectTransfrom.translate(w / 2, h / 2);
	m_projectTransfrom.scale(1, -1);

	auto axis_x = new GraphicRect();
	axis_x->setLeft(-1);
	axis_x->setTop(-0.06);
	axis_x->setWidth(2.02);
	axis_x->setHeight(0.14);
	axis_x->setColor(255, 0, 0);
	GraphicItemManager::instance()->addItem(axis_x);

	auto axis_y = new GraphicRect();
	axis_y->setLeft(-0.06);
	axis_y->setTop(-1);
	axis_y->setWidth(0.14);
	axis_y->setHeight(2.02);
	axis_y->setColor(0, 255, 0);
	GraphicItemManager::instance()->addItem(axis_y);

	auto center = new GraphicCircle();
	center->setCenter({0.0, 0.0});
	center->setRadius(0.15);
	center->setColor(0, 0, 0);
	GraphicItemManager::instance()->addItem(center);
}

void GraphicWidget::Update() {
	PhysicalEngine* physicalEngine = PhysicalEngine::instance();
	if (physicalEngine->isRunning())
	{
		physicalEngine->step();// Use default 60 FPS.
	}
	
	
	auto mgr = GraphicItemManager::instance();
	auto items = mgr->getItems();
	for (GraphicItem* item : items)
	{
		item->render(renderer,  m_viewTransform * m_projectTransfrom);
	}
	//SDL_Rect r1 = { 270, 195, 101, 11 };
	//SDL_Rect r2 = { 315, 150, 11, 101 };
	//
	//SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0xFF);
	//SDL_RenderFillRect(renderer, &r1);

	//SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0xFF);
	//SDL_RenderFillRect(renderer, &r2);

	//filledCircleRGBA(renderer, 320, 200, 5, 0, 0, 0, 255);

}

void GraphicWidget::OnResize(int w, int h)
{
	m_viewTransform.reset();
	m_viewTransform.scale(50, 50);
	m_viewTransform.translate(0, -h / (50 * 4));

	m_projectTransfrom.reset();
	m_projectTransfrom.translate(w / 2, h / 2);
	m_projectTransfrom.scale(1, -1);
}
