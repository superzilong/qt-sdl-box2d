#include "RectOperator.h"

#include "../Graphic/GraphicItemManager.h"
#include "../Graphic/GraphicRect.h"

#include <QMouseEvent>

void RectOperator::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape)
	{
		if (m_rectPoint1Created)
		{
			m_rectPoint1Created = false;
			GraphicItemManager::instance()->deleteItem(m_previewRect->getId());
			delete m_previewRect;
			m_previewRect = nullptr;
		}
		else
		{
			emit signal_exit();
	 	}
	}
}

void RectOperator::mousePressEvent(QMouseEvent* event)
{
	if (m_rectPoint1Created)
	{
		GraphicItemManager::instance()->deleteItem(m_previewRect->getId());
		delete m_previewRect;
		m_previewRect = nullptr;

		QPoint previewPoint = event->pos();
		auto [startX, endX] = std::minmax(m_rectPoint1.x(), previewPoint.x());
		auto [startY, endY] = std::minmax(m_rectPoint1.y(), previewPoint.y());

		auto rect = new GraphicRect();
		rect->setX(startX);
		rect->setY(startY);
		rect->setWidth(endX - startX);
		rect->setHeight(endY - startY);
		GraphicItemManager::instance()->addItem(rect);
		m_rectPoint1Created = false;
	}
	else
	{
		m_rectPoint1 = event->pos();
		m_rectPoint1Created = true;
	}
}

void RectOperator::mouseMoveEvent(QMouseEvent* event)
{
	if (m_rectPoint1Created)
	{
		QPoint previewPoint = event->pos();
		auto [startX, endX] = std::minmax(m_rectPoint1.x(), previewPoint.x());
		auto [startY, endY] = std::minmax(m_rectPoint1.y(), previewPoint.y());

		if (!m_previewRect)
		{
			m_previewRect = new GraphicRect();
			m_previewRect->setX(startX);
			m_previewRect->setY(startY);
			m_previewRect->setWidth(endX - startX);
			m_previewRect->setHeight(endY - startY);
			GraphicItemManager::instance()->addItem(m_previewRect);
		}
		else
		{
			m_previewRect->setX(startX);
			m_previewRect->setY(startY);
			m_previewRect->setWidth(endX - startX);
			m_previewRect->setHeight(endY - startY);
		}
	}
}

void RectOperator::mouseReleaseEvent(QMouseEvent* event)
{
}
