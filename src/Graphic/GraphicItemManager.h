#pragma once
#include <vector>

class GraphicItem;

class GraphicItemManager
{
public:
	static GraphicItemManager* instance()
	{
		static GraphicItemManager mgr;
		return &mgr;
	}

	void addItem(GraphicItem* item);
	void deleteItem(uint32_t id);
	std::vector<GraphicItem*> getItems();

protected:
	GraphicItemManager() = default;
	GraphicItemManager(const GraphicItemManager& other) = default;
	GraphicItemManager(GraphicItemManager&& other) noexcept = default;
	GraphicItemManager& operator=(const GraphicItemManager& other) = default;
	GraphicItemManager& operator=(GraphicItemManager&& other) noexcept = default;

private:
	std::vector<GraphicItem*> m_items;
};
