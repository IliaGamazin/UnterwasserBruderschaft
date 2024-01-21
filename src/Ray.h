#ifndef RAY_H
#define RAY_H

#include "./Vector.h"

// Ray

typedef struct Ray Ray;
struct Ray {
    Vector2 origin;
    Vector2 direction;
};

Ray Ray_new(Vector2 origin, Vector2 direction);

#endif

