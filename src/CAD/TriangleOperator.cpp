#include "TriangleOperator.h"

#include "../Graphic/GraphicItemManager.h"
#include "../Graphic/GraphicRect.h"

#include <QMouseEvent>

#include "CoordConverter.h"

void TriangleOperator::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Escape)
	{
		if (m_rectPoint1Created)
		{
			m_rectPoint1Created = false;
			GraphicItemManager::instance()->deleteItem(m_previewRect);
			delete m_previewRect;
			m_previewRect = nullptr;
		}
		else
		{
			emit signal_exit();
	 	}
	}
}

void TriangleOperator::mousePressEvent(QMouseEvent* event)
{
	if (m_rectPoint1Created)
	{
		GraphicItemManager::instance()->deleteItem(m_previewRect);
		delete m_previewRect;
		m_previewRect = nullptr;

		QPoint mousePoint = event->pos();
		auto[x, y] = m_converter->viewportToWorld(mousePoint.x(), mousePoint.y());
		auto [startX, endX] = std::minmax(m_rectPoint1.x(), x);
		auto [startY, endY] = std::minmax(m_rectPoint1.y(), y);

		auto rect = new GraphicRect();
		rect->setColor(0xFF, 0xB3, 0x44);
		rect->setX(startX);
		rect->setY(startY);
		rect->setWidth(endX - startX);
		rect->setHeight(endY - startY);
		GraphicItemManager::instance()->addItem(rect);
		m_rectPoint1Created = false;
	}
	else
	{
		auto[x, y] = m_converter->viewportToWorld(event->pos().x(), event->pos().y());
		m_rectPoint1.setX(x);
		m_rectPoint1.setY(y);
		m_rectPoint1Created = true;
	}
}

void TriangleOperator::mouseMoveEvent(QMouseEvent* event)
{
	if (m_rectPoint1Created)
	{
		QPoint mousePoint = event->pos();
		auto[x, y] = m_converter->viewportToWorld(mousePoint.x(), mousePoint.y());
		auto [startX, endX] = std::minmax(m_rectPoint1.x(), x);
		auto [startY, endY] = std::minmax(m_rectPoint1.y(), y);

		if (!m_previewRect)
		{
			m_previewRect = new GraphicRect();
			m_previewRect->setColor(0xFF, 0xB3, 0x44);
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

void TriangleOperator::mouseReleaseEvent(QMouseEvent* event)
{
}
