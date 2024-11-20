#include "Collision.h"

bool Collision::checkCollision(const Triangle& triangle, const Plane& plane) 
{
    // Calculate signed distances from the plane to each vertex of the triangle
    float d0 = plane.normal.dot(triangle.v0 - plane.point);
    float d1 = plane.normal.dot(triangle.v1 - plane.point);
    float d2 = plane.normal.dot(triangle.v2 - plane.point);

    // Check if all vertices are on the same side of the plane
    if ((d0 > 0 && d1 > 0 && d2 > 0) || (d0 < 0 && d1 < 0 && d2 < 0)) {
        return false;
    }

    // If one of the vertices lies exactly on the plane, treat it as an intersection
    if (d0 == 0 || d1 == 0 || d2 == 0)
    {
        return true;
    }

    // If the triangle straddles the plane (some vertices on different sides), there's an intersection
    return true;
}

Vector3 Collision::getIntersectionPoint(const Plane& plane, const Vector3& start, const Vector3& end) 
{
    Vector3 direction = end - start;
    float denominator = plane.normal.dot(direction);

    if (denominator == 0)
    {
        return Vector3();  // Parallel line, no intersection within the segment
    }

    float t = plane.normal.dot(plane.point - start) / denominator;

    if (t >= 0 && t <= 1) 
    {
        return start + direction * t;  // Intersection within the segment
    }

    return Vector3();  // No valid intersection
}
