#ifndef DISPLAY_TEST_H
#define DISPLAY_TEST_H

#include <float.h>
#include "display.h"

//#include "display/ImageDictionary.h"

#include "display/DisplayManager.h"
extern DisplayManager display;  // declare the extern DisplayManager object to use the same instance everywhere


void display_test_setup();
void display_test_loop();

#endif