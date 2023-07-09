#ifndef POLYGON_SHAPE_H
#define POLYGON_SHAPE_H

#include "../Vec2.h"
#include "Shape.h"
#include <vector>

struct PolygonShape : public Shape {
    std::vector<Vec2> localVertices;
    std::vector<Vec2> worldVertices;

    PolygonShape() = default;
    PolygonShape(const std::vector<Vec2> vertices);
    virtual ~PolygonShape();
    ShapeType GetType() const override;
    Shape* Clone() const override;
    float GetMomentOfInertia() const override;
    Vec2 EdgeAt(int index) const;
    float FindMinSeparation(const PolygonShape* other, Vec2& axis, Vec2& point) const;
    // Function to rotate and translate the polygon vertices from "local space" to "world space."
    void UpdateVertices(float angle, const Vec2& position);
};

#endif