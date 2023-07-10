#include "LineShape.h"
#include <iostream>

LineShape::LineShape(Vec2 anchorPoint, Vec2 dynamicPoint) {
    this->anchorPoint = anchorPoint;
    this->dynamicPoint = dynamicPoint;
    this->visable = true;
    this->dragState = false;
}

void LineShape::Update(Vec2 dynamicPoint) {
    this->dynamicPoint = dynamicPoint;
}

float LineShape::GetMomentOfInertia() const
{
    return 0.0f;
}

LineShape::~LineShape() {
    std::cout << "LineShape destructor called!" << std::endl;
}

ShapeType LineShape::GetType() const {
    return Line;
}

void LineShape::UpdateVertices(float angle, const Vec2& position) {
    dynamicPoint = dynamicPoint.Rotate(angle);
    dynamicPoint += position;

    anchorPoint = anchorPoint.Rotate(angle);
    anchorPoint += position;
}

Shape* LineShape::Clone() const {
    return new LineShape(anchorPoint, dynamicPoint);
}