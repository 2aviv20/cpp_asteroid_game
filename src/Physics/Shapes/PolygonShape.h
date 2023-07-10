#ifndef POLYGON_SHAPE_H
#define POLYGON_SHAPE_H

#include "../Vec2.h"
#include "Shape.h"
#include <vector>

struct PolygonShape : public Shape {
    float width;
    float height;

    std::vector<Vec2> localVertices;
    std::vector<Vec2> worldVertices;

    PolygonShape() = default;
    PolygonShape(const std::vector<Vec2> vertices);
    virtual ~PolygonShape();
    ShapeType GetType() const override;
    Shape* Clone() const override;
    Vec2 EdgeAt(int index) const;
    float FindMinSeparation(const PolygonShape* other, int& indexReferenceEdge, Vec2& supportPoint) const;
    int FindIncidentEdge(const Vec2& normal) const;
    int ClipSegmentToLine(const std::vector<Vec2>& contactsIn, std::vector<Vec2>& contactsOut, const Vec2& c0, const Vec2& c1) const;
    float PolygonArea() const;
    Vec2 PolygonCentroid() const;
    float GetMomentOfInertia() const override;
    void UpdateVertices(float angle, const Vec2& position) override;
};
#endif