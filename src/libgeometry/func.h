#pragma once
#include <vector>
#include "CircleClass.h"
#include <math.h> 

float CalculateCenterDistance(float x2, float x1, float y2, float y1);
float CalculatePerimeter(float r);
float CalculateArea(float r);
void WriteCircleIntersections(std::vector <CircleClass>& allCircles);
