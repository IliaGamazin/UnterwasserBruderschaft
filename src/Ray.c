#include "./Ray.h"

// Ray

Ray Ray_new(Vector2 origin, Vector2 direction) {
    return (Ray) {
        origin,
        direction,
    };
}

