#include <libgeometry/func.h>
#include <libgeometry/CircleClass.h>
#include <libgeometry/AnalyseDataClass.h>
#include <libgeometry/ReadFromFileClass.h>
#include <string> 
int main() 
{
	std::string path = "data/WKT";
	AnalyseDataClass data;
	std::map <std::string, std::vector<std::string>> parsedCircleData = data.TakeWktDataForCircle(path);

	int circlesCount = 0;
	for (auto circle : parsedCircleData)
		circlesCount++;

	std::vector <CircleClass> circles(circlesCount);// объ€вл€ем массив окружностей 

	int circleIndex = 0;
	// построение объектов на основе полученных данных из словар€ parsedCircleData
	for (auto circle : parsedCircleData)
	{
		circles[circleIndex].SetXcoord(stof(circle.second[0]));// по индексу 0 лежит Xcoord
		circles[circleIndex].SetYcoord(stof(circle.second[1]));// по индексу 1 лежит Ycoord
		circles[circleIndex].SetRadious(stof(circle.second[2]));// по индексу 2 лежит radious
		circles[circleIndex].name = "Circle_" + std::to_string(circleIndex + 1);

		circleIndex++;
	}

	WriteCircleIntersections(circles);// заполн€ем поле intersections дл€ каждого объекта circle

	std::cout << "\n*----- Data View -----*\n\n";// вывод данных о моделировании 
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
