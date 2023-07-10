#include "../Vec2.h"
#ifndef SHAPE_H
#define SHAPE_H

//#include "./BoxShape.h"
//#include "./CircleShape.h"
//#include "./PolygonShape.h"
//#include "./LineShape.h"

enum ShapeType {
    CIRCLE,
    POLYGON,
    BOX,
    Line
};

struct Shape {
    virtual ~Shape() = default;
    virtual ShapeType GetType() const = 0;
    virtual Shape* Clone() const = 0;
    virtual void UpdateVertices(float angle, const Vec2& position) = 0;
    virtual float GetMomentOfInertia() const = 0;
};


#endif
