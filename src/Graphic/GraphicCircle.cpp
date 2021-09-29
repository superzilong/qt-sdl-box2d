#include "GraphicCircle.h"

#include <qtransform.h>
#include <SDL_render.h>
#include <SDL2_gfxPrimitives.h>

uint32_t GraphicCircle::s_id = 0;

void GraphicCircle::render(SDL_Renderer* renderer, const QTransform& transform)
{
	QPointF vCenter = transform.map(center);
	double vRadius = radius * transform.m11();
	//double left = vCenter.x() - vRadius;
	//double right = vCenter.x() + vRadius;
	//double top = vCenter.y() + vRadius;
	//double bottom = vCenter.y() - vRadius;
	//SDL_SetRenderDrawColor(renderer, r, g, b, 0xFF);
	//for (int i = int(std::floor(left)); i <= int(std::ceil(right)); ++i)
	//{
	//	for (int j = int(std::floor(bottom)); j <= int(std::ceil(top)); ++j)
	//	{
	//		if (pow(i-vCenter.x(), 2) + pow(j - vCenter.y(), 2) <= pow(vRadius, 2))
	//		{
	//			SDL_RenderDrawPoint(renderer, i, j);
	//		}
	//	}
	//}

	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
	//const int32_t diameter = (vRadius * 2);
	//int centreX = vCenter.x();
	//int centreY = vCenter.y();

	//int32_t x = (vRadius - 1);
	//int32_t y = 0;
	//int32_t tx = 1;
	//int32_t ty = 1;
	//int32_t error = (tx - diameter);

	//while (x >= y)
	//{
	//	//  Each of the following renders an octant of the circle
	//	SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
	//	SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
	//	SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
	//	SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
	//	SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
	//	SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
	//	SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
	//	SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

	//	if (error <= 0)
	//	{
	//		++y;
	//		error += ty;
	//		ty += 2;
	//	}

	//	if (error > 0)
	//	{
	//		--x;
	//		tx += 2;
	//		error += (tx - diameter);
	//	}
	//}
	filledCircleRGBA(renderer, int16_t(vCenter.x()), int16_t(vCenter.y()), int16_t(vRadius), r, g, b, 255);
	circleRGBA(renderer, int16_t(vCenter.x()), int16_t(vCenter.y()), int16_t(vRadius), 0, 0, 0, 255);
} 