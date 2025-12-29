#ifndef _MathGraph_h_
#define _MathGraph_h_

#include <stdbool.h>
#include <raylib.h>

#include "utils.h"

typedef void* MathGraph;

MathGraph MathGraph_Init(interpolationFunction interFunc, int numPoints, Rectangle frame, float lineThickness);

void MathGraph_Resize(MathGraph mathGraph, Rectangle frame);

void MathGraph_Points(MathGraph mathGraph, int points);

void MathGraph_Draw(MathGraph mathGraph);

#endif