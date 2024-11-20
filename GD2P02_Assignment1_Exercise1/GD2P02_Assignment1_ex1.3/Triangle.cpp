#include "Triangle.h"
#include "Collision.h"

Triangle::Triangle() : v0(), v1(), v2() {}

Triangle::Triangle(const Vector3& v0, const Vector3& v1, const Vector3& v2) : v0(v0), v1(v1), v2(v2) {}

std::vector<Triangle> Triangle::split(const Plane& plane) const {
    std::vector<Vector3> intersectionPoints;

    // Check for intersections on each edge
    Vector3 intersection1 = Collision::getIntersectionPoint(plane, v0, v1);
    if (intersection1.isValid()) intersectionPoints.push_back(intersection1);

    Vector3 intersection2 = Collision::getIntersectionPoint(plane, v1, v2);
    if (intersection2.isValid()) intersectionPoints.push_back(intersection2);

    Vector3 intersection3 = Collision::getIntersectionPoint(plane, v2, v0);
    if (intersection3.isValid()) intersectionPoints.push_back(intersection3);

    std::vector<Triangle> result;

    if (intersectionPoints.size() == 2) {
        const Vector3& p1 = intersectionPoints[0];
        const Vector3& p2 = intersectionPoints[1];

        std::vector<Vector3> positive;
        std::vector<Vector3> negative;

        auto categorize = [&plane](const Vector3& v) {
            return plane.normal.dot(v - plane.point) >= 0;
            };

        if (categorize(v0)) positive.push_back(v0); else negative.push_back(v0);
        if (categorize(v1)) positive.push_back(v1); else negative.push_back(v1);
        if (categorize(v2)) positive.push_back(v2); else negative.push_back(v2);

        if (positive.size() == 1 && negative.size() == 2) {
            result.push_back(Triangle(positive[0], p1, p2));
            result.push_back(Triangle(negative[0], p1, positive[0]));
            result.push_back(Triangle(negative[1], p2, positive[0]));
        }
        else if (positive.size() == 2 && negative.size() == 1) {
            result.push_back(Triangle(negative[0], p1, p2));
            result.push_back(Triangle(positive[0], p1, negative[0]));
            result.push_back(Triangle(positive[1], p2, negative[0]));
        }
    }

    return result;
}
