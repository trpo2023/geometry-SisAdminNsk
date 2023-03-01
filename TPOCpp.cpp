#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <map>
//#include <SFML/Graphics.hpp>
#define M_PI 3.141592653589793238
using namespace std;
//using namespace sf;

class Circle 
{

private: 

	float xCoord = 0;
	float yCoord = 0;
	float radious = 0;

public:

	float GetXcoord() { return xCoord; }
	float GetYcoord() { return yCoord; }
	float GetRadios() { return radious; }

	void SetXcoord(float x) { xCoord = x; }
	void SetYcoord(float y) { yCoord = y; }
	void SetRadious(float rad) { radious = rad; }

	string name = "";
	string intersections[10];

public: 

	double CalculatePerimeter(float r) 
	{
		return  2 * r * M_PI;
	}
	
	double CalculateArea(float r) 
	{
		return r * r * M_PI;
	}
};
class ReadFromFile 
{

protected:

	vector <string> dataFromFile(string path)// записываем данные из файла в массив строк
	{
		string line = "";
		int index = 0;
		int dataSize = 0;

		ifstream checkLines(path);
		if (checkLines.is_open())
			while (getline(checkLines, line)) 
				dataSize++;
				
		line = "";
		vector<string> data(dataSize);

		ifstream in(path);
		if (in.is_open())
		{
			while (getline(in,line))
			{
				data[index] = line;
				index++;
			}
		}
		in.close();
		return data;
	}
};
class AnalyseData : ReadFromFile
{
public:

	map <string, vector<string>> TakeWktDataForCircle(string path) 
	{
		int circleWordLenght = 6; // ожидаемая длина слова "circle"
		vector <string> lowercaseData(dataFromFile(path).size());// Объявляем массив строк чтобы привести все в нижний регистр

		lowercaseData = dataFromFile(path);// кладем сюда всю информацию с файла WKT

		map <string, vector<string>> parsedData;// объявляем словарик 
		vector <string> coordArray(parsedData.size());// объявляем массив координат для круга 

		for (int i = 0; i < lowercaseData.size();i++)// приводим весь текст в нижний регистр и записываем его в новый массив строк 
			for (int j = 0; j < lowercaseData[i].size(); j++)// идем по всей строке
				lowercaseData[i][j] = tolower(lowercaseData[i][j]); // приводим символы в нижний регистр 
	
		int expectedErrorLine = 0;
		int circleIndex = 0;
		for (auto line: lowercaseData)// перебираем все строки в полученном массиве
		{	
			if (line.substr(0, circleWordLenght) == "circle")// проверяем правильность ввода и наличия ключевого слова "circle"
			{
				parsedData[line.substr(0, circleWordLenght) + '_' + to_string(circleIndex)] = ParseString(line);// кладем массив координат;
				circleIndex++;
			}

			else 
				cout << "Error at column 0" << " at line " << expectedErrorLine << ": expected 'circle'.\n"
				<<"This cricle does not go at total list...";

			expectedErrorLine++;	
		}
		return parsedData;
	}

private:

	vector <string> ParseString(string line)// получает строку из массива строк , возвращает массив координат  
	{
		vector<string> coordArray(3);//объявляем массив координат и радиусов
		string numbers = "0123456789. ";
		string parsedString = ""; // сюда будем классать исключительно координаты и радиус круга

		int countOfOpenBracets = 0, countOfCloseBracets = 0;
		for (int i = 0; i < line.length(); i++)// находим кол-во открываюющихся и закрывающихся скобок в строке
		{
			if (line[i] == '(')
				countOfOpenBracets++;

			else if (line[i] == ')')
				countOfCloseBracets++;
		}
		
		if (countOfOpenBracets > 1 || countOfCloseBracets > 1) // проверям кол-во открывающих и закрываюих скобок
		{
			cout << "Bracket's format error! Check the spelling of bracket's in the file.";
			cout << "\nClosing the process...";
			exit(EXIT_SUCCESS);
		}

		// circle(1 2, 3.1( Error at column 15: expected ')
		if (line[6] != '(')// проверка открывающей скобки
		{
			cout << "Error at column 6: expected '('";
			cout << "\nClosing the process...";
			exit(EXIT_SUCCESS);
		}

		if (line[line.length() - 1] != ')')// проверка закрывающей скобки
		{
			cout << "Error at column " << (line.length() - 1) << ": expected '('";
			cout << "\nClosing the process...";
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
		string forbiddenBracketsSymbols = "qwertyuiop[]asdfghjkl;'zxcvbnm/`-=QWERTYUIOPASDFGHJKLZXCVBNM";
		for(int i=indexOfOpenBracket+1;i<indexOfCloseBracket-1;i++)// проверка правильности написания внутри скобок 
			for (int j = 0; j < forbiddenBracketsSymbols.length(); j++)
				if (line[i] == forbiddenBracketsSymbols[j]) 
				{
					cout << "Erorr at column " << i << ": expected '<double>'";
					cout << "\nClosing the process...";
					exit(EXIT_SUCCESS);
				}
			
		for (int i = 0; i < line.length(); i++) 
			for (int j = 0; j < numbers.length(); j++) 
				if (line[i] == numbers[j]) 
				{
					parsedString += line[i];
					break;
				}

		string coordString = "";
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

			if (i == parsedString.length()-1)
				coordArray[index] = coordString;
		}
		//circle(1.0 2.1, 3) 123 Error at column 19: unexpected token
		if (indexOfCloseBracket != line.length()-1)//ловим unexpected token если он есть 
		{
			cout << "Error at column " << indexOfCloseBracket + 1 << ": unexpected token";
			cout << "\nClosing the process...";
			exit(EXIT_SUCCESS);
		}
		return coordArray;// возвращает неотсортированный массив координат , index[0] - xCoord, index[1] - yCoord, index[2] - radious
	}
};

/*class Graphics 
{

public: 

	void DrawCircles(vector <Circle> &allCircles)// рисует графики 
	{
		int width = 800, high = 600;// высота и ширина рабочего окна 
		RenderWindow window(VideoMode(width, high), "Graphics view",Style::Default);// инициализируем граф окно
		Text text;

		Font font;
		font.loadFromFile("CyrilicOld.ttf");// передаем шрифту файл шрифта 
		
		vector<CircleShape> allShapes(allCircles.size());// массив графических окружностей 
		vector<Text> shapesName(allCircles.size());// массив названия окружностей 
		vector<Color> colors(allCircles.size());// массив цветов для окружностей 

		srand(time(NULL));
		for(int i=0;i<allCircles.size();i++)
			colors[i] = Color(rand() % 255, rand() % 255, rand() % 255);
			
		int index = 0;
		for (auto shape : allCircles)// перебираем все экземпляры shape 
		{
			allShapes[index].setPosition(width/2 - shape.GetXcoord() - shape.GetRadios(), high / 2 - shape.GetYcoord() - shape.GetRadios());// масштабируем тк позиция изначально не является центром окружности
			allShapes[index].setFillColor(Color(0,0,0,0));// круг должен быть прозранчным
			allShapes[index].setOutlineThickness(2);// толщина линий обводки 2 px
			allShapes[index].setOutlineColor(colors[index]);// цвет линий обводки Green
			allShapes[index].setRadius(shape.GetRadios());// устанавливаем значения радиуса для каждой окружности

			shapesName[index].setFont(font);// устанавливаем шрифт
			shapesName[index].setPosition(width/2 - shape.GetXcoord(), high / 2 - shape.GetYcoord());// ставим позицию текста 
			shapesName[index].setFillColor(colors[index]);// текст по умолчанию красного цвета
			shapesName[index].setCharacterSize(10);// размер шрифта 10 px
			shapesName[index].setString(to_string((index+1)));// сам текст (номер окружности)
			
			index++;
		}

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
			}

			window.clear();
			for (auto shape : allShapes)// рисуем экземпляры класса CircleShape 
				window.draw(shape);

			for (auto text : shapesName)// рисуем экземпляры класса Text
				window.draw(text);
				
			window.display();
		}
	}
};*/

float CalculateCenterDistance(float x2, float x1, float y2, float y1)
{
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));// возвращаем расстояние между центрами окружностей
}

void WriteCircleIntersections(vector <Circle>& allCircles)// возвращает список фигур, с которыми пересекается выбранный экземпляр
{
	int index = 0;
	for (int i = 0; i < allCircles.size(); i++)
	{
		for (int j = 0; j < allCircles.size(); j++)
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

int main()
{
	string path = "WKT.txt";
	AnalyseData data;
	map <string, vector<string>> parsedCircleData = data.TakeWktDataForCircle(path);
	
	int circlesCount = 0;
	for (auto circle : parsedCircleData)
		circlesCount++;

	vector <Circle> circles(circlesCount);// объявляем массив окружностей 

	int circleIndex = 0;
	// построение объектов на основе полученных данных из словаря parsedCircleData
	for (auto circle : parsedCircleData) 
	{
		circles[circleIndex].SetXcoord(stof(circle.second[0]));// по индексу 0 лежит Xcoord
		circles[circleIndex].SetYcoord(stof(circle.second[1]));// по индексу 1 лежит Ycoord
		circles[circleIndex].SetRadious(stof(circle.second[2]));// по индексу 2 лежит radious
		circles[circleIndex].name = "Circle_" + to_string(circleIndex+1);
		
		circleIndex++;
	}

	WriteCircleIntersections(circles);// заполняем поле intersections для каждого объекта circle

	cout << "\n*----- Data View -----*\n\n";// вывод данных о моделировании 
	for (auto circle : circles)
	{
		cout << circle.name + "(" + to_string(circle.GetXcoord()) + " " + to_string(circle.GetYcoord()) + ","
			+ to_string(circle.GetRadios()) + ")\nPerimeter = " + to_string(circle.CalculatePerimeter(circle.GetRadios()))
			+ "\narea = " + to_string(circle.CalculateArea(circle.GetRadios())) + "\nintersects:\n";

		for (string name : circle.intersections) 
			if(name != "")
				cout << name + "\n";

		cout << "----------\n\n";
	}

	//Graphics circle;
	//circle.DrawCircles(circles);// графическое представление моделей 
}