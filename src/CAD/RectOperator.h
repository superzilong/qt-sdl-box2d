#pragma	once
#include <qpoint.h>
#include "CADOperator.h"

class GraphicRect;

class RectOperator : public CADOperator
{
public:
	Q_OBJECT;
public:
	RectOperator() = default;
	virtual ~RectOperator() = default;

	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;

private:

	QPoint m_rectPoint1;
	bool m_rectPoint1Created = false;
	GraphicRect* m_previewRect = nullptr;
};
