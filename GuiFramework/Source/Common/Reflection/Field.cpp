#include "Gui.h"
#include "Common/Reflection/Field.h"


template<>
std::string Field<int>::valueToString() {
	return std::to_string(*value);
}

template<>
std::string Field<float>::valueToString() {
	return std::to_string(*value);
}

template<>
std::string Field<std::string>::valueToString() {
	return *value;
}

template<>
std::string Field<int>::typeToString() {
	return "int";
}

template<>
std::string Field<float>::typeToString() {
	return "float";
}

template<>
std::string Field<std::string>::typeToString() {
	return "string";
}