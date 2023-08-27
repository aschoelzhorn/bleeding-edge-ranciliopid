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

int Viewport::getHeight() {
    return width;
}

int Viewport::getWidth() {
    return height;
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
