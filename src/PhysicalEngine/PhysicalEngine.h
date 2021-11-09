#pragma once
#include <box2d/box2d.h>

class PhysicalEngine
{
public:
	static PhysicalEngine* instance()
	{
		static PhysicalEngine s_physicalEngine;
		return &s_physicalEngine;
	}
protected:
	PhysicalEngine();

private:
	b2World* m_world = nullptr;

};