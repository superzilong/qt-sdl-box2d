#pragma once
#include <qpoint.h>
#include <qstring.h>

#include "GraphicItem.h"

class GraphicCircle : public GraphicItem
{
public:
	static uint32_t s_id;

	GraphicCircle() : GraphicItem()
	{
		id = s_id++;
		name = QString("Circle_%1").arg(id).toStdString();
		type = Type::circle;
	}

	virtual ~GraphicCircle() {}

	QPointF getCenter() const
	{
		return center;
	}

	void setCenter(const QPointF& center)
	{
		this->center = center;
	}

	double getRadius() const
	{
		return radius;
	}

	void setRadius(double radius)
	{
		this->radius = radius;
	}

	void setColor(uint8_t r, uint8_t g, uint8_t b) { this->r = r; this->g = g; this->b = b; }

	std::tuple<uint8_t, uint8_t, uint8_t> getColor() { return std::make_tuple(r, g, b); }

	void render(SDL_Renderer* renderer, const QTransform& transform) override;

private:

	QPointF center;
	double radius;

	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;

};
