#include "MyPoint.h"

// MyPoint::MyPoint(int x, int y) {
//   X = x;
//   Y = y;
// }


MyPoint::MyPoint() : X(0), Y(0) {
    // Default constructor sets X and Y to 0
}

MyPoint::MyPoint(int x, int y) : X(x), Y(y) {
    // Parameterized constructor
}