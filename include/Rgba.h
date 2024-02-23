#ifndef RGBA
#define RGBA

#include "./Libs.h"

typedef struct Rgba Rgba;
struct Rgba {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

Rgba Rgba_new(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

#endif

