#include "ReadFromFileClass.h"

std::vector<std::string> ReadFromFileClass::dataFromFile(std::string& path)
{
	std::string line = "";
	int index = 0;
	int dataSize = 0;

	std::ifstream checkLines(path);
	if (checkLines.is_open())
	{
		while (getline(checkLines, line))
			dataSize++;
	}
	else
		std::cout << "Cant open file\n";	
	line = "";
	std::vector<std::string> data(dataSize);

	std::ifstream in(path);
	if (in.is_open())
	{
		while (getline(in, line))
		{
			data[index] = line;
			index++;
		}
	}
	in.close();
	return data;
}
