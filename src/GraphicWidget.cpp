#include "GraphicWidget.h"

#include "Graphic/GraphicItem.h"
#include "Graphic/GraphicItemManager.h"
#include "CAD/CADOperator.h"

#include <QMouseEvent>
#include <SDL_render.h>


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

void GraphicWidget::Init() {}

void GraphicWidget::Update() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
	auto mgr = GraphicItemManager::instance();
	auto items = mgr->getItems();
	for (GraphicItem* item : items)
	{
		item->render(renderer);
	}
}

void GraphicWidget::OnResize(int, int) {}
