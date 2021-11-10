#include "GraphicTriangle.h"

#include <qtransform.h>
#include <SDL_render.h>
#include <SDL2_gfxPrimitives.h>

uint32_t GraphicTriangle::s_id = 0;

void GraphicTriangle::render(SDL_Renderer* renderer, const QTransform& transform)
{
	auto mP1 = m_modelTrans.map(p1);
	auto mP2 = m_modelTrans.map(p2);
	auto mP3 = m_modelTrans.map(p3);
	QPointF nP1 = transform.map(mP1);
	QPointF nP2 = transform.map(mP2);
	QPointF nP3 = transform.map(mP3);
	Sint16 array_x[3] = { (Sint16)nP1.x(), (Sint16)nP2.x(), (Sint16)nP3.x() };
	Sint16 array_y[3] = { (Sint16)nP1.y(), (Sint16)nP2.y(), (Sint16)nP3.y() };
	filledPolygonRGBA(renderer, array_x, array_y, 3, r, g, b, 255);
	polygonRGBA(renderer, array_x, array_y, 3, 0, 0, 0, 255);
}
