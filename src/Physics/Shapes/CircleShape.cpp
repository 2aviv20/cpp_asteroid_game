#include "CircleShape.h"
#include <iostream>
CircleShape::CircleShape(float radius) {
    this->radius = radius;
    std::cout << "CircleShape constructor called!" << std::endl;
}

CircleShape::~CircleShape() {
    std::cout << "CircleShape destructor called!" << std::endl;
}

float CircleShape::GetMomentOfInertia() const {
    // For solid circles, the moment of inertia is 1/2 * r^2
    // But this still needs to be multiplied by the rigidbody's mass
    return 0.5 * (radius * radius);
}


Shape* CircleShape::Clone() const {
    return new CircleShape(radius);
}

ShapeType CircleShape::GetType() const {
    return CIRCLE;
}

