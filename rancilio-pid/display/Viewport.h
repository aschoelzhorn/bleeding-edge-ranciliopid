#ifndef VIEWPORT_H
#define VIEWPORT_H

// #DEFINE BOOTLOGO = 0
// #DEFINE BOOTMESSAGE = 1
// #DEFINE STATUSIMAGE = 2
// #DEFINE STATUSICONS = 3
// #DEFINE STATUSMESSAGE = 4

#include "MyPoint.h"

class Viewport {
public:
    Viewport();
    Viewport(MyPoint startingPoint, int width, int height);    
    int getHeight();
    int getWidth();

    MyPoint getUpperLeft();
    MyPoint getUpperRight();

    MyPoint getLowerLeft();
    MyPoint getLowerRight();

private:
    MyPoint startPoint;
    int width;
    int height;
};

#endif