#include "Body.h"
#include <iostream>

Body::Body(const Shape& shape, float x, float y, float mass, float scale) {
    this->shape = shape.Clone();
    this->position = Vec2(x, y);
    this->mass = mass;
    this->restitution = 0;
    this->scale = scale;
    if (mass != 0.0) {
        this->invMass = 1.0 / mass;
    } else {
        this->invMass = 0.0;
    }
    std::cout << "Body constructor called!" << std::endl;
}

Body::~Body() {
    delete shape;
    std::cout << "Body destructor called!" << std::endl;
}

void Body::AddForce(const Vec2& force) {
    sumForces += force;
}

void Body::ClearForces() {
    sumForces = Vec2(0.0, 0.0);
}

void Body::Integrate(float dt) {
    // Find the acceleration based on the forces that are being applied and the mass
    acceleration = sumForces * invMass;

    // Integrate the acceleration to find the new velocity
    velocity += acceleration * dt;

    // Integrate the velocity to find the acceleration
    position += velocity * dt;

    ClearForces();
}

void Body::changeColor(std::uint32_t color) {
    this->color = color;
}

bool Body::IsStatic() const{
    const float epsilon = 0.005f;
    return fabs(invMass - 0.0) < epsilon;
}

void Body::ApplyImpulse(const Vec2& j) {
    if (IsStatic()) {
        return;
    }

    velocity += j * invMass;
}

void Body::IntegrateLinear(float dt) {
    if (IsStatic()) {
        return;
    }

    // Find the acceleration based on the forces that are being applied and the mass
    acceleration = sumForces * invMass;

    // Integrate the acceleration to find the new velocity
    velocity += acceleration * dt;

    // Integrate the velocity to find the new position
    position += velocity * dt;

    // Clear all the forces acting on the object before the next physics step
    ClearForces();
}

void Body::IntegrateAngular(float dt) {
    if (IsStatic()) {
        return;
    }

    // Find the angular acceleration based on the torque that is being applied and the moment of inertia
    angularAcceleration = sumTorque * invI;

    // Integrate the angular acceleration to find the new angular velocity
    angularVelocity += angularAcceleration * dt;

    // Integrate the angular velocity to find the new rotation angle
    rotation += angularVelocity * dt;

    // Clear all the torque acting on the object before the next physics step
    ClearTorque();
}

void Body::ClearTorque() {
    sumTorque = 0.0;
}

void Body::Update(float dt) {
    IntegrateLinear(dt);
    IntegrateAngular(dt);
    bool isPolygon = shape->GetType() == POLYGON || shape->GetType() == BOX;
    if (isPolygon) {
        PolygonShape* polygonShape = (PolygonShape*)shape;
        polygonShape->UpdateVertices(rotation, position);
    }
}
