#ifndef LINE_SHAPE
#define LINE_SHAPE
#include "Shape.h"
#include "../Vec2.h"

struct LineShape : public Shape {
    Vec2 dynamicPoint;
    Vec2 anchorPoint;
    bool visable = true;
    bool dragState = false;

    LineShape(Vec2 anchorPoint, Vec2 dynamicPoint);
    void Update(Vec2 dynamicPoint);
    float GetMomentOfInertia() const override;
    ShapeType GetType() const override;
    virtual ~LineShape();
    virtual void UpdateVertices(float angle, const Vec2& position);
    Shape* Clone() const override;
};


#endif // LINE_SHAPE
