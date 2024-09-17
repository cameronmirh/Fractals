/*
 * File: fractals.cpp
 * --------------------------
 * Name: Cameron Mirhossaini
 * Section leader: Norah Borus
 * This file contains fractal problems for CS106B. There are three different main fuctions: A Sierpinski triangle, a recursive tree,
 * and the Mandelbrot pattern.
 */


#include "fractals.h"
#include <cmath>

using namespace std;

void drawTriangle(GWindow &, double, double, double);

void drawRecursiveTree(GWindow &, double, double , double, int, int, int);

const int LEAF_COLOR = 0x2e8b57;   /* Color of all leaves of recursive tree (level 1) */
const int BRANCH_COLOR = 0x8b7765; /* Color of all branches of recursive tree (level >=2) */

/**
 * Draws a Sierpinski triangle of the specified size and order, placing its
 * top-left corner at position (x, y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the Sierpinski triangle.
 * @param x - The x coordinate of the top-left corner of the triangle.
 * @param y - The y coordinate of the top-left corner of the triangle.
 * @param size - The length of one side of the triangle.
 * @param order - The order of the fractal.
 */




void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order) {
    if(order == 1) {
        drawTriangle(gw,x,y,size);
    } else {
        drawSierpinskiTriangle(gw, x, y, size / 2, order - 1);
        drawSierpinskiTriangle(gw, x + size/2, y, size / 2, order - 1);
        drawSierpinskiTriangle(gw, x + size/4, size/4 * sqrt(3) + y, size / 2, order - 1);
    }

}
//draws an equalatoral triangle with a point downwards.
void drawTriangle(GWindow & gw, double x, double y, double size) {
    gw.drawLine(x,y, x + size/2, y + size / 2 *sqrt(3.0));
    gw.drawLine(x,y, x + size, y);
    gw.drawLine( x + size, y, x + size/2, y + size / 2 *sqrt(3.0));

}






/**
 * Draws a recursive tree fractal image of the specified size and order,
 * placing the bounding box's top-left corner at position (x,y).
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the recursive tree.
 * @param x - The x coordinate of the top-left corner of the bounding box.
 * @param y - The y coordinate of the top-left corner of the bounding box.
 * @param size - The length of one side of the bounding box.
 * @param order - The order of the fractal.
 */



//readjusts x and y to take center of window and passes that point on to helper functions
//sets current angle at 90 and will adjust each successive angle by 15 degrees
//uses order from bottom up, so from lowest number to max order
void drawTree(GWindow& gw, double x, double y, double size, int order) {
    double dx = x + size*.5;
    double dy = y + size;
    int angle = 90;
    int currentOrder = 1;
    drawRecursiveTree(gw, dx, dy, size, currentOrder, order, angle);
}





void drawRecursiveTree(GWindow& gw, double x, double y, double size, int currentOrder, int order, int angle) {
    //sets correct color based on order
    if(currentOrder == order) gw.setColor(LEAF_COLOR);
    else gw.setColor(BRANCH_COLOR);
    //uses last point that was drawn
    GPoint point = gw.drawPolarLine(x, y, size / 2, angle);

    if (order == currentOrder) {
    } else {
        //changes degree angle by 45
        //gets half trunk size and changes angle by 15 degrees each iteration
        currentOrder += 1;
        angle += 45;
        for(int i = 0; i < 7; i++) {
            drawRecursiveTree(gw, point.getX(), point.getY(), size/2, currentOrder, order, angle - (15*i));
        }



    }
}






/**
 * Draws a Mandelbrot Set in the graphical window give, with maxIterations
 * (size in GUI) and in a given color (zero for palette)
 *
 * This will be called by fractalgui.cpp.
 *
 * @param gw - The window in which to draw the Mandelbrot set.
 * @param minX - left-most column of grid
 * @param incX - increment value of columns of grid
 * @param minY - top-most row of grid
 * @param incY - increment value of rows of grid
 * @param maxIterations - The maximum number of iterations to run recursive step
 * @param color - The color of the fractal; zero if palette is to be used
 */
void mandelbrotSet(GWindow& gw, double minX, double incX,
                   double minY, double incY, int maxIterations, int color) {

    // Creates palette of colors
    // To use palette:
    // pixels[r][c] = palette[numIterations % palette.size()];
    Vector<int> palette = setPalette();

    int width = gw.getCanvasWidth();
    int height = gw.getCanvasHeight();
    GBufferedImage image(width,height,0xffffff);
    gw.add(&image);
    Grid<int> pixels = image.toGrid(); // Convert image to grid

    //checks every pixel in grid to check if its in the  mandelbrot set.
    //if iit is, it will be colored
    for(int r = 0; r < pixels.numRows(); r++) {
        for (int c = 0; c < pixels.numCols(); c++) {
            Complex point = Complex(minX + c * incX, minY + r * incY);
            int check = mandelbrotSetIterations(point, maxIterations);
            if (check == maxIterations) {
                pixels[r][c] = color;
            } else {
                if (color == 0) pixels[r][c] = palette[check % palette.size()];
            }
        }
    }

    image.fromGrid(pixels); // Converts and puts the grid back into the image
}

/**
 * Runs the Mandelbrot Set recursive formula on complex number c a maximum
 * of maxIterations times.
 *
 * This will be called by you. Think about how this fits with the other two functions.
 *
 * @param c - Complex number to use for recursive formula.
 * @param maxIterations - The maximum number of iterations to run recursive step
 * @return number of iterations needed to determine if c is unbounded
 */

//keeps track of remaining iterations, no real recursion
int mandelbrotSetIterations(Complex c, int maxIterations) {
    Complex z = Complex(0,0);
    int remainingIterations =  maxIterations;
    int x = mandelbrotSetIterations(z, c, remainingIterations);
    return maxIterations - x;

}







/**
 * An iteration of the Mandelbrot Set recursive formula with given values z and c, to
 * run for a maximum of maxIterations.
 *
 * This will be called by you. Think about how this fits with the other two functions.
 *
 * @param z - Complex number for a given number of iterations
 * @param c - Complex number to use for recursive formula.
 * @param remainingIterations - The remaining number of iterations to run recursive step
 * @return number of iterations needed to determine if c is unbounded
 */



//recursion
//using mandelbrot definition, if reach all iterations or if z is greater than 4, it will be painted
// if not, we will recurse the functions by using the formula
int mandelbrotSetIterations(Complex z, Complex c, int remainingIterations) {

    if (remainingIterations == 0 || z.abs() > 4) {
        return remainingIterations;

    } else {

        z = z * z + c;
        remainingIterations--;
        return mandelbrotSetIterations(z, c, remainingIterations);

    }
}

// Helper function to set the palette
Vector<int> setPalette() {
    Vector<int> colors;

    // Feel free to replace with any palette.
    // You can find palettes at:
    // http://www.colourlovers.com/palettes

    // Example palettes:
    // http://www.colourlovers.com/palette/4480793/in_the_middle
    // string colorSt = "#A0B965,#908F84,#BF3C43,#9D8E70,#C9BE91,#A0B965,#908F84,#BF3C43";

    // http://www.colourlovers.com/palette/4480786/Classy_Glass
    // string colorSt = "#9AB0E9,#C47624,#25269A,#B72202,#00002E,#9AB0E9,#C47624,#25269A";

    // The following is the "Hope" palette:
    // http://www.colourlovers.com/palette/524048/Hope
    string colorSt =  "#04182B,#5A8C8C,#F2D99D,#738585,#AB1111,#04182B,#5A8C8C,#F2D99D";
    Vector<string>colorsStrVec = stringSplit(colorSt,",");
    for (string color : colorsStrVec) {
        colors.add(convertColorToRGB(trim(color)));
    }
    return colors;
}
