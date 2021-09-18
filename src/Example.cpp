#include "Example.h"

#include <SDL_render.h>

#include "graphic/GraphicItem.h"
#include "graphic/GraphicItemManager.h"
#include "graphic/GraphicRect.h"
#include "graphic/GraphicItemManager.h"
#include <QMouseEvent>
#include <QDebug>


void Example::mousePressEvent(QMouseEvent* event)
{
	if (m_createRect)
	{
		if (m_rectPoint1Created)
		{
			GraphicItemManager::instance()->deleteItem(m_previewRect->GetId());
			delete m_previewRect;
			m_previewRect = nullptr;

			QPoint previewPoint = event->pos();
			auto[startX, endX] = std::minmax(m_rectPoint1.x(), previewPoint.x());
			auto[startY, endY] = std::minmax(m_rectPoint1.y(), previewPoint.y());

			auto rect = new GraphicRect();
			rect->setX(startX);
			rect->setY(startY);
			rect->setWidth(endX - startX);
			rect->setHeight(endY - startY);
			GraphicItemManager::instance()->addItem(rect);
			m_rectPoint1Created = false;
		}
		else
		{
			m_rectPoint1 = event->pos();
			m_rectPoint1Created = true;
		}
	}
}

void Example::mouseMoveEvent(QMouseEvent* event)
{
	if (m_rectPoint1Created)
	{
		QPoint previewPoint = event->pos();
		auto [startX, endX] = std::minmax(m_rectPoint1.x(), previewPoint.x());
		auto [startY, endY] = std::minmax(m_rectPoint1.y(), previewPoint.y());

		if (!m_previewRect)
		{
			m_previewRect = new GraphicRect();
			m_previewRect->setX(startX);
			m_previewRect->setY(startY);
			m_previewRect->setWidth(endX - startX);
			m_previewRect->setHeight(endY - startY);
			GraphicItemManager::instance()->addItem(m_previewRect);
		}
		else
		{
			m_previewRect->setX(startX);
			m_previewRect->setY(startY);
			m_previewRect->setWidth(endX - startX);
			m_previewRect->setHeight(endY - startY);
		}
		SDLRepaint();
	}
	emit sigal_mousePos(event->pos());
}

void Example::mouseReleaseEvent(QMouseEvent* event)
{
	
}

void Example::Init() {}

void Example::Update() {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0x0, 0x0, 0xFF);
	auto mgr = GraphicItemManager::instance();
	auto items = mgr->getItems();
	for (GraphicItem* item : items)
	{
		if (item->GetType() == GraphicItem::Type::rect)
		{
			GraphicRect* rect = dynamic_cast<GraphicRect*>(item);
			
			SDL_Rect spos;
			spos.h = rect->getHeight();
			spos.w = rect->getWidth();
			spos.y = rect->getY();
			spos.x = rect->getX();
			SDL_RenderFillRect(renderer, &spos);
		}
	}
	
}

void Example::OnResize(int, int) {}

void Example::slot_toggleRectTool(bool tog)
{
	m_createRect = tog;
}

