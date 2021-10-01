#pragma once
#include <string>

template <typename T>
class Observer
{
public:
	virtual void propertyChanged(T& source, const std::string& propertyName) = 0;
};
