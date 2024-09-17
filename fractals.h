
#ifndef _recursionproblems_h
#define _recursionproblems_h

#include <iostream>
#include <string>
#include "gbufferedimage.h"
#include "gwindow.h"
#include "vector.h"
#include "complex.h"

// function prototype declarations
void drawSierpinskiTriangle(GWindow& window, double x, double y, double size, int order);
void drawTree(GWindow& window, double x, double y, double size, int order);
void mandelbrotSet(GWindow& window, double minX, double incX,
                   double minY, double incY, int maxIterations, int inColor);
int mandelbrotSetIterations(Complex c, int maxIterations);
int mandelbrotSetIterations(Complex z, Complex c, int remainingIterations);
//int floodFill(GWindow& window, int x, int y, int color);
Vector<int> setPalette();

#endif
