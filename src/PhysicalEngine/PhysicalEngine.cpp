#include "PhysicalEngine.h"

PhysicalEngine::PhysicalEngine()
{
	b2Vec2 gravity(0.f, -10.f);
	m_world = new b2World(gravity);
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


