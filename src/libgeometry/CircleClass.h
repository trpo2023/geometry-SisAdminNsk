#pragma once
#include <string>

class CircleClass
{
private:
	float xCoord = 0;
	float yCoord = 0;
	float radious = 0;

public:
	float GetXcoord();
	float GetYcoord();
	float GetRadios();

	void SetXcoord(float x);
	void SetYcoord(float y);
	void SetRadious(float rad);

	std::string name = "";
	std::string intersections[10];

	float CalculatePerimeter(float r);
	float CalculateArea(float r);
};

