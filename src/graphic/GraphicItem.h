#pragma once
#include <string>

class GraphicItem
{
public:	
	enum class Type
	{
		none,
		rect
	};

	GraphicItem() = default;

	virtual ~GraphicItem() {}

	uint32_t GetId() const
	{
		return id;
	}

	void SetId(uint32_t id)
	{
		this->id = id;
	}

	std::string GetName() const
	{
		return name;
	}

	void SetName(const std::string& name)
	{
		this->name = name;
	}

	Type GetType() const
	{
		return type;
	}

	void SetType(Type type)
	{
		this->type = type;
	}

protected:
	uint32_t id;
	std::string name;
	Type type = Type::rect;
};
