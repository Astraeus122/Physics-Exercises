#ifndef COLLISION_H
#define COLLISION_H

#include "Vector3.h"
#include "Plane.h"
#include "Triangle.h"

class Collision 
{
public:
    static bool checkCollision(const Triangle& triangle, const Plane& plane);
    static Vector3 getIntersectionPoint(const Plane& plane, const Vector3& start, const Vector3& end);
};

#endif
