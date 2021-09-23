#pragma once

#include "Graphic/SDLWidget.h"


class CADOperator;
class GraphicRect;

class CoordConverter
{
public:
	CoordConverter(QTransform* viewTrans, QTransform* projTrans) : m_viewTrans(viewTrans), m_projTrans(projTrans) {};
	std::pair<double, double> worldToViewport(double x, double y) { QPointF p = (*m_viewTrans * *m_projTrans).map(QPoint(x, y)); return { p.x(), p.y() }; };
	std::pair<double, double> viewportToWorld(double x, double y) { QPointF p = (*m_viewTrans * *m_projTrans).inverted().map(QPoint(x, y)); return { p.x(), p.y() }; };;

private:
	QTransform* m_viewTrans;
	QTransform* m_projTrans;
};

class GraphicWidget : public SDLWidget
{
private:
	Q_OBJECT

public:
	GraphicWidget(QWidget* parent) : SDLWidget(parent),
	m_viewTransform(),
	m_projectTransfrom(),
	m_converter(&m_viewTransform, &m_projectTransfrom)
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

	QTransform m_viewTransform;
	QTransform m_projectTransfrom;
	CoordConverter m_converter;

signals:
	void signal_mousePos(const QPoint& pos);
public slots:
	void slot_setCADTool(std::shared_ptr<CADOperator> opt) { m_CADOperator = opt; };
};
