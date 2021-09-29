#pragma	once
#include <QAction>
#include <QObject>

class CoordConverter;
class QMouseEvent;
class QKeyEvent;

class CADOperator : public QObject
{
public:
	Q_OBJECT

public:
	CADOperator();
	virtual void keyPressEvent(QKeyEvent* event) = 0;
	virtual void mousePressEvent(QMouseEvent* event) = 0;
	virtual void mouseMoveEvent(QMouseEvent* event) = 0;
	virtual void mouseReleaseEvent(QMouseEvent* event) = 0;
	virtual void reset() = 0;

	QAction* getAction() { return &m_action; }
	void setCoordConverter(CoordConverter* converter) { m_converter = converter; }

protected:
	QAction m_action;
	CoordConverter* m_converter = nullptr;

	
signals:
	void signal_activate(CADOperator* op);
	void signal_exit(CADOperator* op);


};

inline CADOperator::CADOperator()
{
	m_action.setCheckable(true);
	connect(&m_action, &QAction::triggered, this, [this](bool bChecked)
	{
		if (bChecked)
		{
			emit signal_activate(this);
		}
		else
		{
			emit signal_exit(this);
		}
	});
}
