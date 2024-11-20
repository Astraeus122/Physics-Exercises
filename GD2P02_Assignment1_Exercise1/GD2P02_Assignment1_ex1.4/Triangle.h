#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Vector3.h"
#include "Plane.h"
#include <vector>

class Triangle 
{
public:
    Vector3 v0, v1, v2;

    Triangle();
    Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2);
    std::vector<Triangle> split(const Plane& plane) const;
};

#endif // TRIANGLE_H
