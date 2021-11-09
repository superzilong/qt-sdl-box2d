#pragma once
#include <qpoint.h>
#include <qstring.h>

#include "GraphicItem.h"
#include "CAD/RectOperator.h"

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

	double getLeft() const
	{
		return m_left;
	}

	void setLeft(double left)
	{
		m_left = left;
	}

	double getTop() const
	{
		return m_top;
	}

	void setTop(double top)
	{
		this->m_top = top;
	}

	double getWidth() const
	{
		return m_width;
	}

	void setWidth(double width)
	{
		this->m_width = width;
	}

	double getHeight() const
	{
		return m_height;
	}

	void setHeight(double height)
	{
		this->m_height = height;
	}

	QPointF getCenter() const
	{
		QRectF qrect(m_left, m_top, m_width, m_height);
		return qrect.center();
	}

	

	void setColor(uint8_t r, uint8_t g, uint8_t b) { this->m_r = r; this->m_g = g; this->m_b = b; }

	std::tuple<uint8_t, uint8_t, uint8_t> getColor() { return std::make_tuple(m_r, m_g, m_b); }

	void render(SDL_Renderer* renderer, const QTransform& transform) override;

private:
	double m_left = 0;
	double m_top = 0;
	double m_width = 0;
	double m_height = 0;
	uint8_t m_r = 0;
	uint8_t m_g = 0;
	uint8_t m_b = 0;

};
