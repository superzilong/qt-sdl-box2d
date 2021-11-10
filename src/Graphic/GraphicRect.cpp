#include "GraphicRect.h"

#include <qtransform.h>
#include <SDL_rect.h>
#include <SDL_render.h>

#include "SDL2_gfxPrimitives.h"

uint32_t GraphicRect::s_id = 0;

void GraphicRect::render(SDL_Renderer* renderer, const QTransform& transform)
{
	QRectF qrect(m_left, m_bottom, m_width, m_height);
	QPolygonF modelRect = m_modelTrans.map(qrect);
	QPolygonF rectPolygon = transform.map(modelRect);
	//SDL_Rect spos;
	//spos.h = rect.height();
	//spos.w = rect.width();
	//spos.y = rect.top();
	//spos.x = rect.left();
	//SDL_SetRenderDrawColor(renderer, m_r, m_g, m_b, 0xFF);
	//SDL_RenderFillRect(renderer, &spos);
	//SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	//SDL_RenderDrawRect(renderer, &spos);
	Sint16 array_x[4] = { (Sint16)rectPolygon[0].x(), (Sint16)rectPolygon[1].x(), (Sint16)rectPolygon[2].x(), (Sint16)rectPolygon[3].x() };
	Sint16 array_y[4] = { (Sint16)rectPolygon[0].y(), (Sint16)rectPolygon[1].y(), (Sint16)rectPolygon[2].y(), (Sint16)rectPolygon[3].y() };
	filledPolygonRGBA(renderer, array_x, array_y, 4, m_r, m_g, m_b, 255);
	polygonRGBA(renderer, array_x, array_y, 4, 0, 0, 0, 255);
}
