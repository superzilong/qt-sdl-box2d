#pragma once

// example.h
#pragma once

#include "graphic/SDLWidget.h"

class Example : public SDLWidget
{
private:
	Q_OBJECT

public:
	Example(QWidget* parent) : SDLWidget(parent)
	{
		setMouseTracking(true);
	}

protected:
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	void Init();
	void Update();
	void OnResize(int w, int h);
signals:
	void sigal_mousePos(const QPoint& pos);
};
