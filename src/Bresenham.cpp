#include "Bresenham.h"


void plotLine(std::function<void(int, int)>& plotPixelFunction, int x0, int y0, int x1, int y1) {
  int dx = abs(x1 - x0);
  int sx = x0 < x1 ? 1 : -1;
  int dy = -abs(y1 - y0);
  int sy = y0 < y1 ? 1 : -1;
  int d = dx + dy;
  int d2;

  for (;;) {
    plotPixelFunction(x0, y0);
    if (x0 == x1 && y0 == y1)
      break;
    d2 = 2 * d;
    if (d2 >= dy) {
      d += dy;
      x0 += sx;
    }
    if (d2 <= dx) {
      d += dx;
      y0 += sy;
    }
  }
}