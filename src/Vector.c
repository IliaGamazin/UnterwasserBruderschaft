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

double Vector2_dot(Vector2 vector1, Vector2 vector2) {
    return (vector1.x * vector2.x) + (vector1.y * vector2.y);
}

bool Vector2_is_null(Vector2 vector) {
    return !vector.x && !vector.y;
}

void Vector2_scale(Vector2 *vector, double scale_factor) {
    vector->x *= scale_factor;
    vector->y *= scale_factor;
}

void Vector2_normalize(Vector2 *vector) {
    if (!Vector2_is_null(*vector)) {
        Vector2_scale(vector, 1 / Vector2_magnitude(*vector));
    }
}

Vector2 Vector2_normalized(Vector2 vector) {
    Vector2_normalize(&vector);

    return vector;
}

void Vector2_set_magnitude(Vector2 *vector, double magnitude) {
    Vector2_normalize(vector);
    Vector2_scale(vector, magnitude);
}

Vector2 Vector2_with_magnitude(Vector2 vector, double magnitude) {
    Vector2_set_magnitude(&vector, magnitude);

    return vector;
}

void Vector2_scale_to_x(Vector2 *vector, double x) {
    if (vector->x) {
        Vector2_scale(vector, x / vector->x);
    }
}

Vector2 Vector2_scaled_to_x(Vector2 vector, double x) {
    Vector2_scale_to_x(&vector, x);

    return vector;
}

void Vector2_scale_to_y(Vector2 *vector, double y) {
    if (vector->y) {
        Vector2_scale(vector, y / vector->y);
    }
}

Vector2 Vector2_scaled_to_y(Vector2 vector, double y) {
    Vector2_scale_to_y(&vector, y);

    return vector;
}

void Vector2_rotate(Vector2 *vector, double radians) {
    *vector = Vector2_new(
        Vector2_dot(
            Vector2_new(cos(radians), -sin(radians)),
            *vector
        ),
        Vector2_dot(
            Vector2_new(sin(radians), cos(radians)),
            *vector
        )
    );
}

Vector2 Vector2_rotated(Vector2 vector, double radians) {
    Vector2_rotate(&vector, radians);

    return vector;
}

// Trigonometry

double radians_to_degrees(double radians) {
    return radians * 180 / M_PI;
}

double degrees_to_radians(double degrees) {
    return degrees * M_PI / 180;
}

