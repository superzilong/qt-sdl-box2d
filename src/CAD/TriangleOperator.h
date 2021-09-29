#pragma	once
#include <qpoint.h>
#include "CADOperator.h"

class GraphicLine;
class GraphicTriangle;

class TriangleOperator : public CADOperator
{
public:
	Q_OBJECT;
public:
	TriangleOperator();
	~TriangleOperator() override = default;

	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

	void reset() override;
private:

	QPointF m_point1;
	QPointF m_point2;
	bool m_point1Created = false;
	bool m_point2Created = false;
	GraphicLine* m_previewLine = nullptr;
	GraphicTriangle* m_previewTri = nullptr;
};
