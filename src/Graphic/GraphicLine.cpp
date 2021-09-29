﻿#include "GraphicLine.h"

#include <qtransform.h>
#include <SDL_render.h>

uint32_t GraphicLine::s_id = 0;

void GraphicLine::render(SDL_Renderer* renderer, const QTransform& transform)
{
	QPointF nP1 = transform.map(p1);
	QPointF nP2 = transform.map(p2);
	SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
	SDL_RenderDrawLineF(renderer, nP1.x(), nP1.y(), nP2.x(), nP2.y());
}
