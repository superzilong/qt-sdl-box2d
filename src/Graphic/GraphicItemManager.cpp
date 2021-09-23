#include "GraphicItemManager.h"

#include <algorithm>

#include "GraphicItem.h"

void GraphicItemManager::addItem(GraphicItem* item)
{
	m_items.push_back(item);
}

void GraphicItemManager::deleteItem(uint32_t id)
{
	auto iter = std::find_if(m_items.cbegin(), m_items.cend(), [&id](GraphicItem* item) {return item->getId() == id; });
	if (iter != m_items.cend())
	{
		m_items.erase(iter);
	}
}

std::vector<GraphicItem*> GraphicItemManager::getItems()
{
	return m_items;
}
