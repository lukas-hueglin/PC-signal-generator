#include "Gui.h"
#include "Common/Reflection/Internal.h"
#include "Common/XmlHandler.h"

void Internal::load(std::string class_name, std::wstring path) {

	// create XmlHandler
	XmlHandler xml(path);

	// find reflect element for this class
	Element* reflect = xml.findElement("reflect", class_name);

	// load all fields that are present
	for (auto& field : m_intFields) {
		Element* found = xml.findElement("field", field.name, field.typeToString());

		if (found != nullptr) {
			*(field.value) = std::stoi(found->content);
		}
	}
	for (auto& field : m_floatFields) {
		Element* found = xml.findElement("field", field.name, field.typeToString());

		if (found != nullptr) {
			*(field.value) = std::stof(found->content);
		}
	}
	for (auto& field : m_stringFields) {
		Element* found = xml.findElement("field", field.name, field.typeToString());

		if (found != nullptr) {
			*(field.value) = found->content;
		}
	}
}

void Internal::save(std::string class_name, std::wstring path) {

	// create XmlHandler
	XmlHandler xml(path);

	// find reflect element for this class
	Element* reflect = xml.findElement("reflect", class_name);

	if (reflect == nullptr) {
		reflect = xml.createElement("reflect", class_name);
	}

	// load all fields that are present
	for (auto& field : m_intFields) {
		xml.setElement(reflect, "field", field.name, field.typeToString(), field.valueToString());
	}
	for (auto& field : m_floatFields) {
		xml.setElement(reflect, "field", field.name, field.typeToString(), field.valueToString());
	}
	for (auto& field : m_stringFields) {
		xml.setElement(reflect, "field", field.name, field.typeToString(), field.valueToString());
	}

	// write file
	xml.writeXml();
}