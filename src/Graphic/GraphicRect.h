#pragma once
#include <qstring.h>

#include "GraphicItem.h"

class GraphicRect : public GraphicItem
{
public:
	static uint32_t s_id;

	GraphicRect() : GraphicItem()
	{
		id = s_id++;
		name = QString("Rect_%1").arg(id).toStdString();
		type = Type::rect;
	}

	virtual ~GraphicRect() {}

	double getX() const
	{
		return x;
	}

	void setX(double x)
	{
		this->x = x;
	}

	double getY() const
	{
		return y;
	}

	void setY(double y)
	{
		this->y = y;
	}

	double getWidth() const
	{
		return width;
	}

	void setWidth(double width)
	{
		this->width = width;
	}

	double getHeight() const
	{
		return height;
	}

	void setHeight(double height)
	{
		this->height = height;
	}

	void render(SDL_Renderer* renderer, const QTransform& transform) override;

private:
	double x = 0;
	double y = 0;
	double width = 0;
	double height = 0;

};
