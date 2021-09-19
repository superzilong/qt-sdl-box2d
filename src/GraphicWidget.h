#pragma once

#include "Graphic/SDLWidget.h"


class CADOperator;
class GraphicRect;

class GraphicWidget : public SDLWidget
{
private:
	Q_OBJECT

public:
	GraphicWidget(QWidget* parent) : SDLWidget(parent)
	{
		setMouseTracking(true);
	}

protected:
	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:
	void Init();
	void Update();
	void OnResize(int w, int h);

	std::shared_ptr<CADOperator> m_CADOperator;

signals:
	void signal_mousePos(const QPoint& pos);
public slots:
	void slot_setCADTool(std::shared_ptr<CADOperator> opt) { m_CADOperator = opt; };
};
