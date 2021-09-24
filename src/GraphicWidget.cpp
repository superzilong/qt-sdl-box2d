#include "GraphicWidget.h"

#include "Graphic/GraphicItem.h"
#include "Graphic/GraphicItemManager.h"
#include "CAD/CADOperator.h"

#include <QMouseEvent>
#include <SDL_render.h>

#include "Graphic/GraphicRect.h"


void GraphicWidget::keyPressEvent(QKeyEvent* event)
{
	if (m_CADOperator)
	{
		m_CADOperator->keyPressEvent(event);
	}
}

void GraphicWidget::mousePressEvent(QMouseEvent* event)
{
	if (m_CADOperator)
	{
		m_CADOperator->mousePressEvent(event);
	}
}

void GraphicWidget::mouseMoveEvent(QMouseEvent* event)
{
	if (m_CADOperator)
	{
		m_CADOperator->mouseMoveEvent(event);
	}
	emit signal_mousePos(event->pos());
}

void GraphicWidget::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_CADOperator)
	{
		m_CADOperator->mouseReleaseEvent(event);
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

	auto rect1 = new GraphicRect();
	rect1->setX(-1);
	rect1->setY(-0.05);
	rect1->setWidth(2);
	rect1->setHeight(0.1);
	GraphicItemManager::instance()->addItem(rect1);

	auto rect2 = new GraphicRect();
	rect2->setX(-0.05);
	rect2->setY(-1);
	rect2->setWidth(0.1);
	rect2->setHeight(2);
	GraphicItemManager::instance()->addItem(rect2);
}

void GraphicWidget::Update() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
	auto mgr = GraphicItemManager::instance();
	auto items = mgr->getItems();
	for (GraphicItem* item : items)
	{
		item->render(renderer,  m_viewTransform * m_projectTransfrom);
	}
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
