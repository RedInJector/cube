#ifndef BRESENHAMS_LINE
#define BRESENHAMS_LINE

#include <stdlib.h>
#include <functional>

/**
* Implementation of a Line plotting algorithm described in
* <https://web.archive.org/web/20080528040104/http://www.research.ibm.com/journal/sj/041/ibmsjIVRIC.pdf>
* by J.E. Bresenham in 1965
* 
* @param plotPixelFunction - void(int x, int y) function that will be called 
on for every pixel that should be drawn
* @param x0 - x coordinate of first point
* @param y0 - y coordinate of first point
* @param x1 - x coordinate of second point
* @param y1 - y coordinate of second point
* 
*/
void plotLine(std::function<void(int, int)> &plotPixelFunction, int x0, int y0, int x1, int y1);

#endif