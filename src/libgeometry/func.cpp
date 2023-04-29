#include <func.h>

float CalculateCenterDistance(float x2, float x1, float y2, float y1) 
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

float CalculatePerimeter_test(float r) { return  2 * r * M_PI; }

float CalculateArea_test(float r) { return r * r * M_PI; }

bool CheckBracketsCount(std::string& line)
{
	int countOfOpenBracets = 0, countOfCloseBracets = 0;
	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] == '(')
			countOfOpenBracets++;

		else if (line[i] == ')')
			countOfCloseBracets++;
	}

	if (countOfOpenBracets > 1 || countOfCloseBracets > 1)
		return false;

	return true;
}

bool CheckOpenBracket(std::string& line)
{
	if (line[6] != '(')
		return false;

	return true;
}

bool CheckCloseBracket(std::string& line)
{
	if (line[line.length() - 1] != ')')
		return false;
	
	return true;
}

bool CheckRubbishInBrackets(std::string& line)// circle(x1 2, 3.0) Error at column 7: expected '<double>'
{
	unsigned int indexOfOpenBracket = 0, indexOfCloseBracket = 0;
	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] == '(')
			indexOfOpenBracket = i;

		else if (line[i] == ')')
			indexOfCloseBracket = i;
	}
	std::string forbiddenBracketsSymbols = "qwertyuiop[]asdfghjkl;'zxcvbnm/`-=QWERTYUIOPASDFGHJKLZXCVBNM";
	for (unsigned int i = indexOfOpenBracket + 1; i < indexOfCloseBracket - 1; i++)
		for (unsigned int j = 0; j < forbiddenBracketsSymbols.length(); j++)
			if (line[i] == forbiddenBracketsSymbols[j])
				return false;

	return true;
}

bool CheckRubbishOutOfBrackets(std::string& line)//circle(1.0 2.1, 3) 123 Error at column 19: unexpected token
{	
	[[maybe_unused]] unsigned int indexOfOpenBracket = 0;
	unsigned int indexOfCloseBracket = 0;

	for (unsigned int i = 0; i < line.length(); i++)
	{
		if (line[i] == '(')
			indexOfOpenBracket = i;

		else if (line[i] == ')')
			indexOfCloseBracket = i;
	}

	if (indexOfCloseBracket != line.length() - 1)//unexpected token
		return false;
	
	return true;
}

void WriteCircleIntersections(std::vector <CircleClass>& allCircles) 
{
	int index = 0;
	for (unsigned int i = 0; i < allCircles.size(); i++)
	{
		for (unsigned int j = 0; j < allCircles.size(); j++)
		{
			if (j != i)
			{
				if (CalculateCenterDistance(allCircles[j].GetXcoord(), allCircles[i].GetXcoord(), allCircles[j].GetYcoord(), allCircles[i].GetYcoord()) <= (allCircles[j].GetRadios() + allCircles[i].GetRadios()))
				{
					allCircles[i].intersections[index] = allCircles[j].name;
					index++;
				}
			}
		}
		index = 0;
	}
}
