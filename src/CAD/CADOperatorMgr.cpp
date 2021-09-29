#include "CADOperatorMgr.h"

#include "CircleOperator.h"
#include "RectOperator.h"
#include "TriangleOperator.h"

CADOperatorMgr::CADOperatorMgr()
{
	RectOperator* rectOp = new RectOperator();
	CircleOperator* circleOp = new CircleOperator();
	TriangleOperator* triOp = new TriangleOperator();
	m_operators.push_back(rectOp);
	m_operators.push_back(circleOp);
	m_operators.push_back(triOp);
	for (auto&& op : m_operators)
	{
		connect(op, &CADOperator::signal_activate, this, &CADOperatorMgr::slot_activateOperator);
		connect(op, &CADOperator::signal_exit, this, &CADOperatorMgr::slot_exitOperator);
	}
}

CADOperatorMgr::~CADOperatorMgr()
{
	for (auto&& op : m_operators)
	{
		delete op;
	}
	m_currentOp = nullptr;
}

std::vector<QAction*> CADOperatorMgr::getAllActions()
{
	std::vector<QAction*> actions;
	actions.reserve(m_operators.size());
	std::transform(m_operators.begin(), m_operators.end(), std::back_inserter(actions), [](CADOperator* op) { return op->getAction(); });
	return actions;
}

void CADOperatorMgr::init(CoordConverter* converter)
{
	for (auto&& op : m_operators)
	{
		op->setCoordConverter(converter);
	}
}

void CADOperatorMgr::slot_activateOperator(CADOperator* op)
{
	if (m_currentOp && m_currentOp != op)
	{
		emit m_currentOp->signal_exit(m_currentOp);
	}
	m_currentOp = op;
}

void CADOperatorMgr::slot_exitOperator(CADOperator* op)
{
	auto pAction = op->getAction();
	op->reset();
	if (pAction->isChecked())
	{
		pAction->blockSignals(true);
		pAction->setChecked(false);
		pAction->blockSignals(false);
	}
	m_currentOp = nullptr;
}
