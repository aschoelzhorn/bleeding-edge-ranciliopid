#include "Viewport.h"

Viewport::Viewport() {
    this->width = 0;
    this->height = 0;
    this->startPoint = MyPoint(0,0);
}

Viewport::Viewport(MyPoint startPoint, int width, int height) {
    this->width = width;
    this->height = height;
    this->startPoint = startPoint;
}

Viewport::Viewport(int x, int y, int width, int height) : Viewport(MyPoint(x, y), width, height) {
}

int Viewport::getHeight() {
    return height;
}

int Viewport::getWidth() {
    return width;
}

MyPoint Viewport::getUpperLeft() {
    return startPoint;
}

MyPoint Viewport::getUpperRight() {
    return MyPoint(startPoint.X + width, startPoint.Y);
}

MyPoint Viewport::getLowerLeft() {
    return MyPoint(startPoint.X, startPoint.Y + height);
}

MyPoint Viewport::getLowerRight() {
    return MyPoint(startPoint.X + width, startPoint.Y + height);
}


String Viewport::getDebugString() {
    String output = "X/Y: " + String(startPoint.X) + " / " + String(startPoint.Y) + ", w=" + String(width) + ", h=" + String(height);
    //snprintf((char*)displaymessagetextBuffer, sizeof(displaymessagetextBuffer), "%s", displaymessagetext);
    return output;
}
