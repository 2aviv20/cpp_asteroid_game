#ifndef BODY_H
#define BODY_H

#include "Vec2.h"
#include "./Shapes/Shape.h"
#include "./Shapes/PolygonShape.h"
#include "./Shapes/BoxShape.h"

struct Body {
    Vec2 position;
    Vec2 velocity;
    Vec2 acceleration;

    // Angular motion
    float rotation;
    float angularVelocity;
    float angularAcceleration;

    // Forces and torque
    Vec2 sumForces;
    float sumTorque;

    // Mass and Moment of Inertia
    float mass;
    float invMass;
    float I;
    float invI;
    float scale = 1;
    // Coefficient of restitution (elasticity)
    float restitution;

    std::uint32_t color = 0xFFFFFFFF;
    Shape* shape = nullptr;
    bool isCollide = false;

    Body(const Shape& shape, float x, float y, float mass, float scale);
    ~Body();
    void changeColor(std::uint32_t color);
    void AddForce(const Vec2& force);
    void ClearForces();
    void ClearTorque();

    void Integrate(float dt);
    void ApplyImpulse(const Vec2& j);
    bool IsStatic() const;

    void IntegrateLinear(float dt);
    void IntegrateAngular(float dt);

    void Update(float dt);
};

#endif
