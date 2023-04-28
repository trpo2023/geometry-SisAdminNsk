#include "AnalyseDataClass.h"

std::map<std::string, std::vector<std::string>> AnalyseDataClass::TakeWktDataForCircle(std::string path)
{
	int circleWordLenght = 6;//"circle"
	std::vector <std::string > lowercaseData(dataFromFile(path).size());

	lowercaseData = dataFromFile(path);//WKT

	std::map <std::string, std::vector<std::string>> parsedData;
	std::vector <std::string> coordArray(parsedData.size());

	for (unsigned int i = 0; i < lowercaseData.size(); i++)
		for (unsigned int j = 0; j < lowercaseData[i].size(); j++)
			lowercaseData[i][j] = tolower(lowercaseData[i][j]); 

	int expectedErrorLine = 0;
	int circleIndex = 0;
	for (auto line : lowercaseData)
	{
		if (line.substr(0, circleWordLenght) == "circle")
		{
			parsedData[line.substr(0, circleWordLenght) + '_' + std::to_string(circleIndex)] = ParseString(line);
			circleIndex++;
		}

		else
			std::cout << "Error at column 0" << " at line " << expectedErrorLine << ": expected 'circle'.\n"
			<< "This cricle does not go at total list...";

		expectedErrorLine++;
	}
	return parsedData;
}

std::vector<std::string> AnalyseDataClass::ParseString(std::string line)
{
	std::vector<std::string> coordArray(3);
	std::string numbers = "0123456789. ";
	std::string parsedString = "";

	if(!CheckBracketsCount(line))// circle(1 2, 3.1))) - error! / circle(((1 2, 3.1) - error!
	{
		std::cout << "Bracket's format error! Check the spelling of bracket's in the file.";
		std::cout << "\nClosing the process...";
		exit(EXIT_SUCCESS);
	}

	// circle(1 2, 3.1( Error at column 15: expected ')
	if(!CheckOpenBracket(line))
	{
		std::cout << "Error at column 6: expected '('";
		std::cout << "\nClosing the process...";
		exit(EXIT_SUCCESS);
	}

	if(!CheckCloseBracket(line))// checking close bracket
	{
		std::cout << "Error at column " << (line.length() - 1) << ": expected '('";
		std::cout << "\nClosing the process...";
		exit(EXIT_SUCCESS);
	}
 	[[maybe_unused]] unsigned int indexOfOpenBracket = 0;
	unsigned int indexOfCloseBracket = 0;
	for(unsigned int i = 0; i < line.length(); i++)
	{
		indexOfOpenBracket = 1;

		if(line[i] == '(')
			indexOfOpenBracket = i;
		if(line[i] == ')')
			indexOfCloseBracket = i;
	}

	if(!CheckRubbishInBrackets(line))// checing rubbish into bracket's
	{
		std::cout << "Erorr in bracket's " << ": expected '<double>'";
		std::cout << "\nClosing the process...";
		exit(EXIT_SUCCESS);
	}

	for (unsigned int i = 0; i < line.length(); i++) 
	{
		for (unsigned int j = 0; j < numbers.length(); j++)
		{
			if (line[i] == numbers[j])
			{
				parsedString += line[i];
				break;
			}
		}
	}
		
	std::string coordString = "";
	int index = 0;
	for (unsigned int i = 0; i < parsedString.length(); i++)
	{
		if (parsedString[i] != ' ' && parsedString[i] != ',')
			coordString += parsedString[i];

		else
		{
			coordArray[index] = coordString;
			index++;
			coordString = "";
		}

		if (i == parsedString.length() - 1)
			coordArray[index] = coordString;
	}

	if(!CheckRubbishOutOfBrackets(line))//circle(1.0 2.1, 3) 123 Error at column 19: unexpected token
	{
		std::cout << "Error at column " << indexOfCloseBracket + 1 << ": unexpected token";
		std::cout << "\nClosing the process...";
		exit(EXIT_SUCCESS);	
	}

	return coordArray;//index[0] - xCoord, index[1] - yCoord, index[2] - radious
}