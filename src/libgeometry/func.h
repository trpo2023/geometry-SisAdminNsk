#pragma once
#include <vector>
#include "CircleClass.h"
#include <math.h> 

// math group of func's
float CalculateCenterDistance(float x2, float x1, float y2, float y1);
float CalculatePerimeter(float r);
float CalculateArea(float r);
void WriteCircleIntersections(std::vector <CircleClass>& allCircles);
// parsing group of func's
bool CheckOpenBracket(std::string& line);
bool CheckCloseBracket(std::string& line);
bool CheckRubbishInBrackets(std::string& line);
bool CheckRubbishOutOfBrackets(std::string& line);