#include "CADOperator.h"

class CADOperatorMgr: public QObject
{
public:
	Q_OBJECT

public:
	static CADOperatorMgr* instance()
	{
		static CADOperatorMgr s_mgr;
		return &s_mgr;
	}
	std::vector<QAction*> getAllActions();
	void init(CoordConverter* converter);
	CADOperator* getCurrentOp() { return m_currentOp; };

protected:
	CADOperatorMgr();
	~CADOperatorMgr();

private:
	std::vector<CADOperator*> m_operators;
	CADOperator* m_currentOp = nullptr;

private slots:
	void slot_activateOperator(CADOperator* op);
	void slot_exitOperator(CADOperator* op);
};
