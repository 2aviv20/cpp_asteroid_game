#ifndef COLLISION_DETECTION_H
#define COLLISION_DETECTION_H
#include "Body.h"
#include "Contact.h"
#include "./Shapes/CircleShape.h"
class CollisionDetection {
public:
    static bool IsColliding(Body* a, Body* b, std::vector<Contact>& contacts);
    static bool IsCollidingCircleCircle(Body* a, Body* b, std::vector<Contact>& contacts);
    static bool IsCollidingPolygonPolygon(Body* a, Body* b, std::vector<Contact>& contacts);
    static bool IsCollidingPolygonCircle(Body* polygon, Body* circle, std::vector<Contact>& contacts);
};
#endif