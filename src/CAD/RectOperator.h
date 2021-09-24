#pragma	once
#include <qpoint.h>
#include "CADOperator.h"

class GraphicRect;
class CoordConverter;

class RectOperator : public CADOperator
{
public:
	Q_OBJECT;
public:
	RectOperator(CoordConverter* converter) { m_converter = converter; };
	virtual ~RectOperator() = default;

	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:

	QPointF m_rectPoint1;
	bool m_rectPoint1Created = false;
	GraphicRect* m_previewRect = nullptr;
	CoordConverter* m_converter = nullptr;
};
