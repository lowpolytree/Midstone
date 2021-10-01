#pragma once
#include <string_view>

class MapReader
{
public:
	static std::string ReadMapFromFile(const std::string_view filename);

private:
};

