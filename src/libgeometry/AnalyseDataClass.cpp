#include "AnalyseDataClass.h"

std::map<std::string, std::vector<std::string>> AnalyseDataClass::TakeWktDataForCircle(std::string path)
{
	int circleWordLenght = 6; // ожидаема€ длина слова "circle"
	std::vector <std::string > lowercaseData(dataFromFile(path).size());// ќбъ€вл€ем массив строк чтобы привести все в нижний регистр

	lowercaseData = dataFromFile(path);// кладем сюда всю информацию с файла WKT

	std::map <std::string, std::vector<std::string>> parsedData;// объ€вл€ем словарик 
	std::vector <std::string> coordArray(parsedData.size());// объ€вл€ем массив координат дл€ круга 

	for (int i = 0; i < lowercaseData.size(); i++)// приводим весь текст в нижний регистр и записываем его в новый массив строк 
		for (int j = 0; j < lowercaseData[i].size(); j++)// идем по всей строке
			lowercaseData[i][j] = tolower(lowercaseData[i][j]); // приводим символы в нижний регистр 

	int expectedErrorLine = 0;
	int circleIndex = 0;
	for (auto line : lowercaseData)// перебираем все строки в полученном массиве
	{
		if (line.substr(0, circleWordLenght) == "circle")// провер€ем правильность ввода и наличи€ ключевого слова "circle"
		{
			parsedData[line.substr(0, circleWordLenght) + '_' + std::to_string(circleIndex)] = ParseString(line);// кладем массив координат;
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
	std::vector<std::string> coordArray(3);//объ€вл€ем массив координат и радиусов
	std::string numbers = "0123456789. ";
	std::string parsedString = ""; // сюда будем классать исключительно координаты и радиус круга

	int countOfOpenBracets = 0, countOfCloseBracets = 0;
	for (int i = 0; i < line.length(); i++)// находим кол-во открываюющихс€ и закрывающихс€ скобок в строке
	{
		if (line[i] == '(')
			countOfOpenBracets++;

		else if (line[i] == ')')
			countOfCloseBracets++;
	}

	if (countOfOpenBracets > 1 || countOfCloseBracets > 1) // провер€м кол-во открывающих и закрываюих скобок
	{
		std::cout << "Bracket's format error! Check the spelling of bracket's in the file.";
		std::cout << "\nClosing the process...";
		exit(EXIT_SUCCESS);
	}

	// circle(1 2, 3.1( Error at column 15: expected ')
	if (line[6] != '(')// проверка открывающей скобки
	{
		std::cout << "Error at column 6: expected '('";
		std::cout << "\nClosing the process...";
		exit(EXIT_SUCCESS);
	}

	if (line[line.length() - 1] != ')')// проверка закрывающей скобки
	{
		std::cout << "Error at column " << (line.length() - 1) << ": expected '('";
		std::cout << "\nClosing the process...";
		exit(EXIT_SUCCESS);
	}

	int indexOfOpenBracket = 0, indexOfCloseBracket = 0;// запоминаем индекс открывающией и закрывающей скобки
	for (int i = 0; i < line.length(); i++)
	{
		if (line[i] == '(')
			indexOfOpenBracket = i;

		else if (line[i] == ')')
			indexOfCloseBracket = i;
	}
	// circle(x1 2, 3.0) Error at column 7: expected '<double>'
	std::string forbiddenBracketsSymbols = "qwertyuiop[]asdfghjkl;'zxcvbnm/`-=QWERTYUIOPASDFGHJKLZXCVBNM";
	for (int i = indexOfOpenBracket + 1; i < indexOfCloseBracket - 1; i++)// проверка правильности написани€ внутри скобок 
		for (int j = 0; j < forbiddenBracketsSymbols.length(); j++)
			if (line[i] == forbiddenBracketsSymbols[j])
			{
				std::cout << "Erorr at column " << i << ": expected '<double>'";
				std::cout << "\nClosing the process...";
				exit(EXIT_SUCCESS);
			}

	for (int i = 0; i < line.length(); i++) 
	{
		for (int j = 0; j < numbers.length(); j++)
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
	for (int i = 0; i < parsedString.length(); i++)
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
	//circle(1.0 2.1, 3) 123 Error at column 19: unexpected token
	if (indexOfCloseBracket != line.length() - 1)//ловим unexpected token если он есть 
	{
		std::cout << "Error at column " << indexOfCloseBracket + 1 << ": unexpected token";
		std::cout << "\nClosing the process...";
		exit(EXIT_SUCCESS);
	}
	return coordArray;// возвращает неотсортированный массив координат , index[0] - xCoord, index[1] - yCoord, index[2] - radious
}
