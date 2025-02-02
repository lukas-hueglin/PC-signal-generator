#pragma once
#include "Gui.h"
#include <string>

template<typename T>
struct Field {

	std::string name;
	T* value;

	std::string valueToString();
	std::string typeToString();

public:
	Field(std::string name, T* value) : name(name), value(value) {}
};