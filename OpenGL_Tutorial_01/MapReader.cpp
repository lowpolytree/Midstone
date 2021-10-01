#include "MapReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

std::string MapReader::ReadMapFromFile(const std::string_view filename)
{
	std::ifstream in(filename.data());
	std::stringstream buffer;
	buffer << in.rdbuf();

	//Removing whitespace and newlines using remove/erase idiom
	auto mapString = std::string(buffer.str());
	mapString.erase(std::remove(mapString.begin(), mapString.end(), ' '), mapString.end());
	mapString.erase(std::remove(mapString.begin(), mapString.end(), '\n'), mapString.end());
	
	return mapString;
}
