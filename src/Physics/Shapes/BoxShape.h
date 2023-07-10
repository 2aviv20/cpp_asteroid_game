#ifndef BOX_SHAPE
#define BOX_SHAPE
#include "PolygonShape.h"

struct BoxShape : public PolygonShape {
    BoxShape(float width, float height);
    virtual ~BoxShape();
    ShapeType GetType() const override;
    Shape* Clone() const override;
    float GetMomentOfInertia() const override;
};

#endif