#include "Plane.h"

Plane::Plane() : point(), normal(0, 1, 0) {}

Plane::Plane(const Vector3& point, const Vector3& normal) : point(point), normal(normal.normalize()) {}
