#include <CircleClass.h>

const float M_PI = 3.141592653589793238;

float CircleClass::GetXcoord() { return xCoord; }
float CircleClass::GetYcoord() { return yCoord; }
float CircleClass::GetRadios() { return radious; }

void CircleClass::SetXcoord(float x) { xCoord = x; }
void CircleClass::SetYcoord(float y) { yCoord = y; }
void CircleClass::SetRadious(float rad) { radious = rad; }

float CircleClass::CalculatePerimeter(float r) { return  2 * r * M_PI; }
float CircleClass::CalculateArea(float r) { return r * r * M_PI; }