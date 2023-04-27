#include <CircleClass.h>

float CircleClass::GetXcoord() { return xCoord; }
float CircleClass::GetYcoord() { return yCoord; }
float CircleClass::GetRadios() { return radious; }

void CircleClass::SetXcoord(float x) { xCoord = x; }
void CircleClass::SetYcoord(float y) { yCoord = y; }
void CircleClass::SetRadious(float rad) { radious = rad; }

double CircleClass::CalculatePerimeter(float r) { return  2 * r * M_PI; }
double CircleClass::CalculateArea(float r) { return r * r * M_PI; }


