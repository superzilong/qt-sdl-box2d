#include "GraphicItemManager.h"

#include <algorithm>


void GraphicItemManager::addItem(GraphicItem* item)
{
	m_items.push_back(item);
}

void GraphicItemManager::deleteItem(GraphicItem::Type type, uint32_t id)
{
	auto iter = std::find_if(m_items.cbegin(), m_items.cend(), [&id, &type](GraphicItem* item) {return item->getType() == type && item->getId() == id; });
	if (iter != m_items.cend())
	{
		m_items.erase(iter);
	}
}

void GraphicItemManager::deleteItem(GraphicItem* inputItem)
{
	deleteItem(inputItem->getType(), inputItem->getId());
}

std::vector<GraphicItem*> GraphicItemManager::getItems()
{
	return m_items;
}
