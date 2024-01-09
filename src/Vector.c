#include <math.h>

#include "./Vector.h"

// Vector2

Vector2 Vector2_new(double x, double y) {
    return (Vector2) {
        x,
        y,
    };
}

Vector2 Vector2_add(Vector2 vector1, Vector2 vector2) {
    return (Vector2) {
        vector1.x + vector2.x,
        vector1.y + vector2.y,
    };
}

Vector2 Vector2_sub(Vector2 vector1, Vector2 vector2) {
    return (Vector2) {
        vector1.x - vector2.x,
        vector1.y - vector2.y,
    };
}

Vector2 Vector2_from_points(Vector2 point1, Vector2 point2) {
    return Vector2_sub(point2, point1);
}

double Vector2_magnitude(Vector2 vector) {
    return sqrt((vector.x * vector.x) + (vector.y * vector.y));
}

void Vector2_scale(Vector2 *vector, double scale_factor) {
    vector -> x *= scale_factor;
    vector -> y *= scale_factor;
}

void Vector2_normalize(Vector2 *vector) {
    Vector2_scale(vector, 1 / Vector2_magnitude(*vector));
}

void Vector2_set_magnitude(Vector2 *vector, double magnitude) {
    Vector2_normalize(vector);
    Vector2_scale(vector, magnitude);
}

