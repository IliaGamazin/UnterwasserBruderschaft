#ifndef VECTOR
#define VECTOR

#include <stdbool.h>

// Vector2

typedef struct Vector2 Vector2;
struct Vector2 {
    double x;
    double y;
};

Vector2 Vector2_new(double x, double y);
Vector2 Vector2_add(Vector2 vector1, Vector2 vector2);
Vector2 Vector2_sub(Vector2 vector1, Vector2 vector2);
Vector2 Vector2_from_points(Vector2 point1, Vector2 point2);
double Vector2_magnitude(Vector2 vector);
double Vector2_dot(Vector2 vector1, Vector2 vector2);
bool Vector2_is_null(Vector2 vector);
void Vector2_scale(Vector2 *vector, double scale_factor);

void Vector2_normalize(Vector2 *vector);
Vector2 Vector2_normalized(Vector2 vector);

void Vector2_set_magnitude(Vector2 *vector, double magnitude);
Vector2 Vector2_with_magnitude(Vector2 vector, double magnitude);

void Vector2_scale_to_x(Vector2 *vector, double x);
Vector2 Vector2_scaled_to_x(Vector2 vector, double x);

void Vector2_scale_to_y(Vector2 *vector, double y);
Vector2 Vector2_scaled_to_y(Vector2 vector, double y);

void Vector2_rotate(Vector2 *vector, double radians);
Vector2 Vector2_rotated(Vector2 vector, double radians);

// Trigonometry

double radians_to_degrees(double radians);
double degrees_to_radians(double degrees);

#endif

