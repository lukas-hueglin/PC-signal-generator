#pragma once
#include "Common/Reflection/Field.h"

#include <fstream> 
#include <string>
#include <vector>


// Reflection MACROS

// define a class member called __internal it is used to store all fields
#define USE_REFLECTION() \
protected: \
	Internal __internal;

// define a macro that returns the internal mamber
#define REFLECTION __internal

// define a member that should be reflected
#define ADD_FIELD(type, name) __internal.addField<type>(Field<type>(#name, &name));

// helper macros
#define FIELD_ARRAY(type) std::vector<Field<type>> m_##type##Fields;


class GUI_API Internal {

	// rename std::string to string, for ease of use with macros
	using string = std::string;

private:
	// add vectors for all different types
	FIELD_ARRAY(int)
	FIELD_ARRAY(float)
	FIELD_ARRAY(string)

public:
	Internal() {};

public:
	template<typename T>
	void addField(Field<T> field);

	void load(std::string class_name, std::wstring path);
	void save(std::string class_name, std::wstring path);
};

// add fields implementations
template<>
inline void Internal::addField(Field<int> field) {

	m_intFields.push_back(field);
}

template<>
inline void Internal::addField(Field<float> field) {

	m_floatFields.push_back(field);
}

template<>
inline void Internal::addField(Field<std::string> field) {

	m_stringFields.push_back(field);
}