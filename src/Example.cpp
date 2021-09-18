#include "Example.h"

#include <SDL_render.h>

#include "graphic/GraphicItem.h"
#include "graphic/GraphicItemManager.h"
#include "graphic/GraphicRect.h"
#include "graphic/GraphicItemManager.h"
#include <QMouseEvent>
#include <QDebug>


void Example::mouseMoveEvent(QMouseEvent* event)
{
	emit sigal_mousePos(event->pos());
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

