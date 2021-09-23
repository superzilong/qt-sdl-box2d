#pragma once
#include <string>

class QTransform;
struct SDL_Renderer;

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

	uint32_t getId() const
	{
		return id;
	}

	void setId(uint32_t id)
	{
		this->id = id;
	}

	std::string getName() const
	{
		return name;
	}

	void setName(const std::string& name)
	{
		this->name = name;
	}

	Type getType() const
	{
		return type;
	}

	void setType(Type type)
	{
		this->type = type;
	}

	virtual void render(SDL_Renderer* renderer, const QTransform& transform) = 0;

protected:
	uint32_t id;
	std::string name;
	Type type = Type::none;
};
