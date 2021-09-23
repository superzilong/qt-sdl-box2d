#include "GraphicRect.h"
#include <SDL_rect.h>
#include <SDL_render.h>

uint32_t GraphicRect::s_id = 0;

void GraphicRect::render(SDL_Renderer* renderer)
{
	SDL_Rect spos;
	spos.h = height;
	spos.w = width;
	spos.y = y;
	spos.x = x;
	SDL_RenderFillRect(renderer, &spos);
}
