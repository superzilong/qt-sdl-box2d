#pragma once
#include <qpoint.h>
#include <qstring.h>

#include "GraphicItem.h"

class GraphicLine : public GraphicItem
{
public:
	static uint32_t s_id;

	GraphicLine() : GraphicItem()
	{
		id = s_id++;
		name = QString("Line_%1").arg(id).toStdString();
		type = Type::line;
	}

	virtual ~GraphicLine() {}

	void setEndPoint1(const QPointF& p1) { this->p1 = p1; }
	void setEndPoint2(const QPointF& p2) { this->p2 = p2; }

	void setPoints(double x1, double y1, double x2, double y2)
	{
		p1.setX(x1);
		p1.setY(y1);
		p2.setX(x2);
		p2.setY(y2);
	}
	
	QPointF getEndPoint1() { return p1; }
	QPointF getEndPoint2() { return p2; }

	void setColor(uint8_t r, uint8_t g, uint8_t b) { this->r = r; this->g = g; this->b = b; }

	std::tuple<uint8_t, uint8_t, uint8_t> getColor() { return std::make_tuple(r, g, b); }

	void render(SDL_Renderer* renderer, const QTransform& transform) override;

private:
	QPointF p1;
	QPointF p2;
	uint8_t r = 0;
	uint8_t g = 0;
	uint8_t b = 0;

};
