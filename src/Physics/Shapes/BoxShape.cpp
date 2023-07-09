#include "BoxShape.h"
#include <iostream>

BoxShape::BoxShape(float width, float height) {
    this->width = width;
    this->height = height;

    // Load the vertices of the box polygon
    localVertices.push_back(Vec2(-width / 2.0, -height / 2.0));
    localVertices.push_back(Vec2(+width / 2.0, -height / 2.0));
    localVertices.push_back(Vec2(+width / 2.0, +height / 2.0));
    localVertices.push_back(Vec2(-width / 2.0, +height / 2.0));

    worldVertices.push_back(Vec2(-width / 2.0, -height / 2.0));
    worldVertices.push_back(Vec2(+width / 2.0, -height / 2.0));
    worldVertices.push_back(Vec2(+width / 2.0, +height / 2.0));
    worldVertices.push_back(Vec2(-width / 2.0, +height / 2.0));
}


BoxShape::~BoxShape() {
    std::cout << "BoxShape destructor called!" << std::endl;
}

ShapeType BoxShape::GetType() const {
    return BOX;
}

Shape* BoxShape::Clone() const {
    return new BoxShape(width, height);
}