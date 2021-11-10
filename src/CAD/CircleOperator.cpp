#include "CircleOperator.h"

#include "../Graphic/GraphicItemManager.h"
#include "../Graphic/GraphicCircle.h"

#include <QMouseEvent>

#include "CoordConverter.h"
#include "PhysicalEngine/PhysicalEngine.h"

CircleOperator::CircleOperator()
{
	m_action.setText("create circle");
}

void CircleOperator::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape)
	{
		if (m_centerPoint1Created)
		{
			m_centerPoint1Created = false;
			GraphicItemManager::instance()->deleteItem(m_previewCircle);
			delete m_previewCircle;
			m_previewCircle = nullptr;
			m_centerPoint1 = QPointF();
		}
		else
		{
			emit signal_exit(this);
	 	}
	}
}

void CircleOperator::mousePressEvent(QMouseEvent* event)
{
	if (m_centerPoint1Created)
	{
		GraphicItemManager::instance()->deleteItem(m_previewCircle);
		delete m_previewCircle;
		m_previewCircle = nullptr;

		QPoint mousePoint = event->pos();
		auto[x, y] = m_converter->viewportToWorld(mousePoint.x(), mousePoint.y());

		auto circle = new GraphicCircle();
		circle->setColor(0xFF, 0xB3, 0x44);
		circle->setCenter(m_centerPoint1.x(), m_centerPoint1.y());
		circle->setPointInCircle(x, y);
		GraphicItemManager::instance()->addItem(circle);
		m_centerPoint1Created = false;

		// Create circle physical model.
		auto pe = PhysicalEngine::instance();
		b2Body* body = pe->createDynamicCircle(circle);
	}
	else
	{
		auto[x, y] = m_converter->viewportToWorld(event->pos().x(), event->pos().y());
		m_centerPoint1.setX(x);
		m_centerPoint1.setY(y);
		m_centerPoint1Created = true;
	}
}

void CircleOperator::mouseMoveEvent(QMouseEvent* event)
{
	if (m_centerPoint1Created)
	{
		QPoint mousePoint = event->pos();
		auto[x, y] = m_converter->viewportToWorld(mousePoint.x(), mousePoint.y());

		if (!m_previewCircle)
		{
			m_previewCircle = new GraphicCircle();
			m_previewCircle->setColor(0xFF, 0xB3, 0x44);
			m_previewCircle->setCenter(m_centerPoint1.x(), m_centerPoint1.y());
			m_previewCircle->setPointInCircle(x, y);
			GraphicItemManager::instance()->addItem(m_previewCircle);
		}
		else
		{
			m_previewCircle->setPointInCircle(x, y);
		}
	}
}

void CircleOperator::mouseReleaseEvent(QMouseEvent* event)
{
}

void CircleOperator::reset()
{
	if (m_previewCircle)
	{
		GraphicItemManager::instance()->deleteItem(m_previewCircle);
		delete m_previewCircle;
		m_previewCircle = nullptr;
	}
	m_centerPoint1 = QPointF();
	m_centerPoint1Created = false;
}
