#ifndef UTILITY_H
#define UTILITY_H

#include "Plane.h"
#include "Point.h"

enum class Position { OnPlane, InFront, Behind };

Position findRelativePosition(const Plane& plane, const Point& point);

#endif