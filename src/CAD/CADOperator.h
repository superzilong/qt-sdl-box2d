#pragma	once
#include <QObject>

class QMouseEvent;
class QKeyEvent;

class CADOperator : public QObject
{
public:
	Q_OBJECT

public:
	virtual void keyPressEvent(QKeyEvent* event) = 0;
	virtual void mousePressEvent(QMouseEvent* event) = 0;
	virtual void mouseMoveEvent(QMouseEvent* event) = 0;
	virtual void mouseReleaseEvent(QMouseEvent* event) = 0;

signals:
	void signal_exit();
};
