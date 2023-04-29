#pragma once
#include <map>
#include <ReadFromFileClass.h>
#include <func.h>
class AnalyseDataClass : public ReadFromFileClass
{
public:
	std::map <std::string, std::vector<std::string>> TakeWktDataForCircle(std::string path);

private:
	std::vector <std::string> ParseString(std::string line);
};
