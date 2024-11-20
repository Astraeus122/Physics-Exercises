#include "Triangle.h"
#include "Collision.h"
#include <iostream>

Triangle::Triangle() : v0(), v1(), v2() {}

Triangle::Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2) : v0(v0), v1(v1), v2(v2) {}

std::vector<Triangle> Triangle::split(const Plane& plane) const 
{
    std::vector<Vector3> intersectionPoints = Collision::getIntersectionPoints(plane, *this);

    std::vector<Triangle> result;

    if (intersectionPoints.size() == 2)
    {
        const Vector3& p1 = intersectionPoints[0];
        const Vector3& p2 = intersectionPoints[1];

        std::vector<Vector3> positive;
        std::vector<Vector3> negative;

        auto categorize = [&plane](const Vector3& v) 
            {
            return plane.normal.dot(v - plane.point) >= 0;
            };

        if (categorize(v0)) positive.push_back(v0); else negative.push_back(v0);
        if (categorize(v1)) positive.push_back(v1); else negative.push_back(v1);
        if (categorize(v2)) positive.push_back(v2); else negative.push_back(v2);

        if (positive.size() == 1 && negative.size() == 2) 
        {
            result.push_back(Triangle(positive[0], p1, p2));
            result.push_back(Triangle(negative[0], p1, positive[0]));
            result.push_back(Triangle(negative[1], p2, positive[0]));
        }
        else if (positive.size() == 2 && negative.size() == 1) 
        {
            result.push_back(Triangle(negative[0], p1, p2));
            result.push_back(Triangle(positive[0], p1, negative[0]));
            result.push_back(Triangle(positive[1], p2, negative[0]));
        }

        std::cout << "Triangle split into 3 smaller triangles" << std::endl;
    }
    else 
    {
        std::cout << "No intersection or incorrect number of intersection points" << std::endl;
    }

    return result;
}
