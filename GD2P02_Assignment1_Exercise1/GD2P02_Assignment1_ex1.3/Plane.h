#ifndef PLANE_H
#define PLANE_H

#include "Vector3.h"

class Plane 
{
public:
    Vector3 point;
    Vector3 normal;

    Plane();
    Plane(const Vector3& point, const Vector3& normal);
};

#endif
