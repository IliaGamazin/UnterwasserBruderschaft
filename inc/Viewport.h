#ifndef VIEWPORT_H
#define VIEWPORT_H

#include "./Libs.h"

// Viewport

typedef SDL_Rect Viewport;

Viewport Viewport_new(int x, int y, int width, int height);
void Viewport_centralize(Viewport *viewport, int cx, int cy);
Viewport Viewport_centralized(int cx, int xy, int width, int height);

#endif

