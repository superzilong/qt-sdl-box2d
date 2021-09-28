﻿#include "GraphicRect.h"

#include <qtransform.h>
#include <SDL_rect.h>
#include <SDL_render.h>

uint32_t GraphicRect::s_id = 0;

void GraphicRect::render(SDL_Renderer* renderer, const QTransform& transform)
{
	QRectF qrect(x, y, width, height);
	QRectF rect = transform.mapRect(qrect);
	SDL_Rect spos;
	spos.h = rect.height();
	spos.w = rect.width();
	spos.y = rect.top();
	spos.x = rect.left();
	SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
	SDL_RenderFillRect(renderer, &spos);
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderDrawRect(renderer, &spos);
}
