#pragma once
#include <map>
#include "ReadFromFileClass.h"
class AnalyseDataClass : public ReadFromFileClass
{
public:
	std::map <std::string, std::vector<std::string>> TakeWktDataForCircle(std::string path);

private:
	std::vector <std::string> ParseString(std::string line);// получает строку из массива строк , возвращает массив координат  
};
