#pragma once
#include <QTransform>
#include <string>

struct SDL_Renderer;

class GraphicItem
{
public:	
	enum class Type
	{
		none,
		rect,
		circle,
		line,
		triangle
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

	QTransform getTrans() const
	{
		return m_modelTrans;
	}

	void setModelTrans(const QTransform& trans)
	{
		m_modelTrans = trans;
	}

	virtual void render(SDL_Renderer* renderer, const QTransform& transform) = 0;

protected:
	uint32_t id;
	std::string name;
	Type type = Type::none;
	QTransform m_modelTrans;
};
