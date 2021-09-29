#pragma	once
#include <qpoint.h>
#include "CADOperator.h"

class GraphicCircle;
class CoordConverter;

class CircleOperator : public CADOperator
{
public:
	Q_OBJECT;
public:
	CircleOperator();
	~CircleOperator() override = default;

	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;


	void reset() override;
private:

	QPointF m_centerPoint1;
	bool m_centerPoint1Created = false;
	GraphicCircle* m_previewCircle = nullptr;
};
