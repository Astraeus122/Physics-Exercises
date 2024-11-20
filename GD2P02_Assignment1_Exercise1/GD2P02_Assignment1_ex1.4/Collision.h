#ifndef COLLISION_H
#define COLLISION_H

#include "Plane.h"
#include "Triangle.h"
#include <vector>

class Collision 
{
public:
    static std::vector<Vector3> getIntersectionPoints(const Plane& plane, const Triangle& triangle);
};

#endif // COLLISION_H
