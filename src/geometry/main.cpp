#include "func.h"
#include "CircleClass.h"
#include "AnalyseDataClass.h"
#include "ReadFromFileClass.h"
#include <string> 
int main() 
{
	std::string path = "../WKT.txt";
	AnalyseDataClass data;
	std::map <std::string, std::vector<std::string>> parsedCircleData = data.TakeWktDataForCircle(path);

	int circlesCount = 0;
	for (auto circle : parsedCircleData)
		circlesCount++;

	std::vector <CircleClass> circles(circlesCount);

	int circleIndex = 0;
	//parsedCircleData
	for (auto circle : parsedCircleData)
	{
		circles[circleIndex].SetXcoord(stof(circle.second[0]));//Xcoord
		circles[circleIndex].SetYcoord(stof(circle.second[1]));//Ycoord
		circles[circleIndex].SetRadious(stof(circle.second[2]));//radious
		circles[circleIndex].name = "Circle_" + std::to_string(circleIndex + 1);

		circleIndex++;
	}

	WriteCircleIntersections(circles);//intersections circle

	std::cout << "\n*----- Data View -----*\n\n";
	for (auto circle : circles)
	{
		std::cout << circle.name + "(" + std::to_string(circle.GetXcoord()) + " " + std::to_string(circle.GetYcoord()) + ","
			+ std::to_string(circle.GetRadios()) + ")\nPerimeter = " +std::to_string(circle.CalculatePerimeter(circle.GetRadios()))
			+ "\narea = " + std::to_string(circle.CalculateArea(circle.GetRadios())) + "\nintersects:\n";

		for (std::string name : circle.intersections)
			if (name != "")
				std::cout << name + "\n";

		std::cout << "----------\n\n";
	}
}
