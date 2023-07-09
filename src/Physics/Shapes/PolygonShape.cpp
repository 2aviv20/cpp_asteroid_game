#include "PolygonShape.h"


PolygonShape::PolygonShape(const std::vector<Vec2> vertices) :localVertices(localVertices) {
    for (Vec2 v:vertices) {
        localVertices.push_back(v);
        worldVertices.push_back(v);
    }
}

PolygonShape::~PolygonShape() {
    // TODO: ...
}

ShapeType PolygonShape::GetType() const {
    return POLYGON;
}

Shape* PolygonShape::Clone() const {
    return new PolygonShape(localVertices);
}

float PolygonShape::GetMomentOfInertia() const {
    // TODO:
    return 0.0;
}

void PolygonShape::UpdateVertices(float angle, const Vec2& position) {
    // Loop all the vertices, transforming from local to world space
    for (int i = 0; i < localVertices.size(); i++) {
        // First rotate, then we translate
        worldVertices[i] = localVertices[i].Rotate(angle);
        worldVertices[i] += position;
    }
}
Vec2 PolygonShape::EdgeAt(int index) const {
    int currVertex = index;
    int nextVertex = (index + 1) % worldVertices.size();
    return worldVertices[nextVertex] - worldVertices[currVertex];
}

float PolygonShape::FindMinSeparation(const PolygonShape* other, Vec2& axis, Vec2& point) const {
    float separation = std::numeric_limits<float>::lowest();
    // Loop all the vertices of "this" polygon
    for (int i = 0; i < this->worldVertices.size(); i++) {
        Vec2 va = this->worldVertices[i];
        Vec2 normal = this->EdgeAt(i).Normal();
        // Loop all the vertices of the "other" polygon
        float minSep = std::numeric_limits<float>::max();
        Vec2 minVertex;
        for (int j = 0; j < other->worldVertices.size(); j++) {
            Vec2 vb = other->worldVertices[j];
            float proj = (vb - va).Dot(normal);
            if (proj < minSep) {
                minSep = proj;
                minVertex = vb;
            }
        }
        if (minSep > separation) {
            separation = minSep;
            axis = this->EdgeAt(i);
            point = minVertex;
        }
    }
    return separation;
}
