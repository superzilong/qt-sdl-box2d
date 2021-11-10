#pragma once
#include <map>
#include <vector>
#include <box2d/box2d.h>

class GraphicTriangle;
class GraphicCircle;
class GraphicItem;
class GraphicRect;

class PhysicalEngine
{
public:
	static PhysicalEngine* instance()
	{
		static PhysicalEngine s_physicalEngine;
		return &s_physicalEngine;
	}

	b2Body* createGroundBox(GraphicRect* box);
	b2Body* createDynamicBox(GraphicRect* box, float density = 1.0f, float friction = 0.3f);
	b2Body* createDynamicCircle(GraphicCircle* circle, float density = 1.0f, float friction = 0.3f);
	b2Body* createDynamicTriangle(GraphicTriangle* tri, float density = 1.0f, float friction = 0.3f);
	void step(float timeStep = 1.f / 60.f, int velocityIterations = 6, int positionIterations = 2);

	void start() { m_isRunning = true; }
	void stop() { m_isRunning = false; }
	bool isRunning() { return m_isRunning; }
	void setIsRunning(bool isRunning) { m_isRunning = isRunning; }

protected:
	PhysicalEngine();

private:
	b2World* m_world = nullptr;
	bool m_isRunning = false;

	std::vector<b2Body*> m_staticBodies;
	std::map<b2Body*, GraphicItem*> m_dynamicBodies2Graphic;

};
