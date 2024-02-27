#include "../inc/Viewport.h"

Viewport Viewport_new(int x, int y, int width, int height) {
    return Rect_new(x, y, width, height);
}

void Viewport_centralize(Viewport *viewport, int cx, int cy) {
    viewport->x = cx - viewport->w / 2;
    viewport->y = cy - viewport->h / 2;
}

Viewport Viewport_centralized(int cx, int cy, int width, int height) {
    Viewport viewport = Viewport_new(0, 0, width, height);

    Viewport_centralize(&viewport, cx, cy);

    return viewport;
}

