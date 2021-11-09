#include "PhysicalEngine.h"

#include <qpoint.h>

#include "Core/Log.h"
#include "Graphic/GraphicRect.h"

PhysicalEngine::PhysicalEngine()
{
	b2Vec2 gravity(0.f, -10.f);
	m_world = new b2World(gravity);
}

b2Body* PhysicalEngine::createGroundBox(GraphicRect* box)
{
	QPointF center = box->getCenter();
	float centerX = static_cast<float>(center.x());
	float centerY = static_cast<float>(center.y());
	float width = static_cast<float>(box->getWidth());
	float height = static_cast<float>(box->getHeight());
	
    b2BodyDef groundBodyDef;
    //groundBodyDef.position.Set(0.f, -10.f);
    groundBodyDef.position.Set(centerX, centerY);

    b2Body* groundBody = m_world->CreateBody(&groundBodyDef);

    b2PolygonShape groundBox;
    //groundBox.SetAsBox(50.f, 10.f);
	groundBox.SetAsBox(width / 2.f, height / 2.f);

    groundBody->CreateFixture(&groundBox, 0.f);

	m_staticBodies.push_back(groundBody);

	return groundBody;
}

b2Body* PhysicalEngine::createDynamicBox(GraphicRect* box, float density, float friction)
{
	QPointF center = box->getCenter();
	float centerX = static_cast<float>(center.x());
	float centerY = static_cast<float>(center.y());
	float width = static_cast<float>(box->getWidth());
	float height = static_cast<float>(box->getHeight());
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 4.0f);
	bodyDef.position.Set(centerX, centerY);
	b2Body* body = m_world->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(width/2.f, height/2.f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = density;
	fixtureDef.friction = friction;

	body->CreateFixture(&fixtureDef);
	body->GetTransform();

	m_dynamicBodies2Graphic.emplace(body, box);

	return body;
}

void PhysicalEngine::step(float timeStep, int velocityIterations, int positionIterations)
{
	if (m_isRunning)
	{
		m_world->Step(timeStep, velocityIterations, positionIterations);
		for (auto&& item : m_dynamicBodies2Graphic)
		{
			b2Transform b2Trans = item.first->GetTransform();
			//QTransform qTrans;
			//qTrans.rotate(b2Trans.q.GetAngle());
			//item.second;
			LOG_INFO(fmt::format("Motion x: {}", b2Trans.p.x));
			LOG_INFO(fmt::format("Motion y: {}", b2Trans.p.y));
			LOG_INFO(fmt::format("Rotation: {}", b2Trans.q.GetAngle()));
		}
	}
}


//#include <iostream>
//#include <box2d/box2d.h>
//
//int main(int argc, char** argv)
//{
//    std::cout << "hello box2d" << std::endl;
//
//    // Create Box2D world.
//    b2Vec2 gravity(0.f, -10.f);
//    b2World world(gravity);
//
//    // Create static ground body.
//    b2BodyDef groundBodyDef;
//    groundBodyDef.position.Set(0.f, -10.f);
//
//    b2Body* groundBody = world.CreateBody(&groundBodyDef);
//
//    b2PolygonShape groundBox;
//    groundBox.SetAsBox(50.f, 10.f);
//
//    groundBody->CreateFixture(&groundBox, 0.f);
//
//    // Dynamic body.
//    b2BodyDef bodyDef;
//    bodyDef.type = b2_dynamicBody;
//    bodyDef.position.Set(0.f, 4.f);
//    b2Body* body = world.CreateBody(&bodyDef);
//
//    b2PolygonShape dynamicBox;
//    dynamicBox.SetAsBox(1.f, 1.f);
//
//    b2FixtureDef fixtureDef;
//    fixtureDef.shape = &dynamicBox;
//    fixtureDef.density = 1.f;
//    fixtureDef.friction = 0.3f;
//
//    body->CreateFixture(&fixtureDef);
//
//    // Simulate
//    float timeStep = 1.f / 60.f;
//    int32 velocityIterations = 8;
//    int32 positionIterations = 3;
//
//    for (int i = 0; i < 60; ++i)
//    {
//        world.Step(timeStep, velocityIterations, positionIterations);
//        b2Vec2 position = body->GetPosition();
//        float angle = body->GetAngle();
//        printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
//    }
//
//    return 0;
//}


