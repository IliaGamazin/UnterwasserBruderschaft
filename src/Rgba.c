#include "../inc/Rgba.h"

// Rgba

Rgba Rgba_new(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    return (Rgba) {
        r,
        g,
        b,
        a,
    };
}

