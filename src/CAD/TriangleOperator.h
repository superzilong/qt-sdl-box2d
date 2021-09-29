#pragma	once
#include <qpoint.h>
#include "CADOperator.h"

class GraphicRect;

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

	QPointF m_rectPoint1;
	bool m_rectPoint1Created = false;
	GraphicRect* m_previewRect = nullptr;
};
