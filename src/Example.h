#pragma once

// example.h
#pragma once

#include "graphic/SDLWidget.h"

class GraphicRect;

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
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	void Init();
	void Update();
	void OnResize(int w, int h);

	bool m_createRect = false;
	QPoint m_rectPoint1;
	bool m_rectPoint1Created = false;
	GraphicRect* m_previewRect = nullptr;
signals:
	void sigal_mousePos(const QPoint& pos);
public:
	void slot_toggleRectTool(bool tog);
};
