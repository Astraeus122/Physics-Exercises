#include "Collision.h"
#include <iostream>

std::vector<Vector3> Collision::getIntersectionPoints(const Plane& plane, const Triangle& triangle)
{
    std::vector<Vector3> intersectionPoints;

    auto checkIntersection = [&plane, &intersectionPoints](const Vector3& v1, const Vector3& v2)
        {
        float d1 = plane.normal.dot(v1 - plane.point);
        float d2 = plane.normal.dot(v2 - plane.point);
        if (d1 * d2 < 0) 
        {
            Vector3 direction = v2 - v1;
            float t = -d1 / plane.normal.dot(direction);
            intersectionPoints.push_back(v1 + direction * t);
        }
    };

    checkIntersection(triangle.v0, triangle.v1);
    checkIntersection(triangle.v1, triangle.v2);
    checkIntersection(triangle.v2, triangle.v0);

    // Debug output for intersections
    std::cout << "Intersection Points: ";
    for (const auto& point : intersectionPoints) 
    {
        std::cout << "(" << point.x << ", " << point.y << ", " << point.z << ") ";
    }
    std::cout << std::endl;

    return intersectionPoints;
}
