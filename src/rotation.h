#ifndef _ROTATION_H_
#define _ROTATION_H_

#include "SDL/SDL.h"

int getAngle(int matrix[], int w, int h);

int* rotation(int angle, int matrix[], int w, int h);

#endif
