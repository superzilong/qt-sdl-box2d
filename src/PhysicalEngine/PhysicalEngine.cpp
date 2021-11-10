#include "PhysicalEngine.h"

#include <qpoint.h>

#include "Core/Log.h"
#include "Graphic/GraphicCircle.h"
#include "Graphic/GraphicRect.h"
#include "Graphic/GraphicTriangle.h"

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
	m_dynamicBodies2Graphic.emplace(body, box);

	return body;
}

b2Body* PhysicalEngine::createDynamicCircle(GraphicCircle* circle, float density, float friction)
{
	QPointF center = circle->getCenter();
	float centerX = static_cast<float>(center.x());
	float centerY = static_cast<float>(center.y());
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(centerX, centerY);
	b2Body* body = m_world->CreateBody(&bodyDef);

	b2CircleShape c;
	c.m_radius = static_cast<float>(circle->getRadius());

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &c;
	fixtureDef.density = density;
	fixtureDef.friction = friction;

	body->CreateFixture(&fixtureDef);
	m_dynamicBodies2Graphic.emplace(body, circle);

	return body;
}

b2Body* PhysicalEngine::createDynamicTriangle(GraphicTriangle* tri, float density, float friction)
{
	QPointF center = tri->getCenter();
	float centerX = static_cast<float>(center.x());
	float centerY = static_cast<float>(center.y());

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	//bodyDef.position.Set(0.0f, 4.0f);
	bodyDef.position.Set(centerX, centerY);
	b2Body* body = m_world->CreateBody(&bodyDef);

	b2PolygonShape dynamicTri;
	auto p1 = tri->getEndPoint1();
	auto p2 = tri->getEndPoint2();
	auto p3 = tri->getEndPoint3();
	b2Vec2 points[3];
	points[0].Set(static_cast<float>(p1.x() - centerX), static_cast<float>(p1.y() - centerY));
	points[1].Set(static_cast<float>(p2.x() - centerX), static_cast<float>(p2.y() - centerY));
	points[2].Set(static_cast<float>(p3.x() - centerX), static_cast<float>(p3.y() - centerY));
	dynamicTri.Set(points, 3);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicTri;
	fixtureDef.density = density;
	fixtureDef.friction = friction;

	body->CreateFixture(&fixtureDef);
	m_dynamicBodies2Graphic.emplace(body, tri);

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
			LOG_INFO("Motion x: {}", b2Trans.p.x);
			LOG_INFO("Motion y: {}", b2Trans.p.y);
			LOG_INFO("Rotation: {}", b2Trans.q.GetAngle());
			if (GraphicRect* rect = dynamic_cast<GraphicRect*>(item.second))
			{
				QTransform modelTransform;
				modelTransform.translate(b2Trans.p.x, b2Trans.p.y);
				modelTransform.rotateRadians(b2Trans.q.GetAngle());
				QPointF center = rect->getCenter();
				modelTransform.translate(- center.x(), - center.y());
				rect->setModelTrans(modelTransform);
			}
			if (GraphicCircle* c = dynamic_cast<GraphicCircle*>(item.second))
			{
				QTransform modelTransform;
				modelTransform.translate(b2Trans.p.x, b2Trans.p.y);
				modelTransform.rotateRadians(b2Trans.q.GetAngle());
				QPointF center = c->getCenter();
				modelTransform.translate(-center.x(), -center.y());
				c->setModelTrans(modelTransform);
			}
			if (GraphicTriangle* tri = dynamic_cast<GraphicTriangle*>(item.second))
			{
				QTransform modelTransform;
				modelTransform.translate(b2Trans.p.x, b2Trans.p.y);
				modelTransform.rotateRadians(b2Trans.q.GetAngle());
				QPointF center = tri->getCenter();
				modelTransform.translate(-center.x(), -center.y());
				tri->setModelTrans(modelTransform);
			}
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


