#ifndef CIRCLE_SHAPE
#define CIRCLE_SHAPE
#include "./Shape.h"

struct CircleShape : public Shape {
    float radius;
    CircleShape(const float radius);
    virtual ~CircleShape();
    ShapeType GetType() const override;
    Shape* Clone() const override;
    float GetMomentOfInertia() const override;
};

#endif