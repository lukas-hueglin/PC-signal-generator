#pragma once
#include "Gui.h"

#include <string>
#include <fstream>

#define XML_HEADER "<?xml version = \"1.0\" encoding = \"utf-8\" standalone = \"yes\"?>"

struct Element {
	std::string tag;
	std::string name;
	std::string type;
	std::string content;
	
	Element* child;
	Element* next;

	~Element() {
		if (child != nullptr) {
			delete child;
		}
		if (next != nullptr) {
			delete next;
		}
	}
};

class GUI_API XmlHandler {

private:
	std::wstring m_path;
	Element* mp_root;

public:
	XmlHandler(std::wstring path);

	void readXml();
	void writeXml();

	void setElement(Element* p_parent, std::string tag, std::string name, std::string type, std::string content);

	Element* createElement(std::string tag, std::string name = "", std::string type = "", std::string content = "");
	Element* createElement(Element* p_parent, std::string tag, std::string name = "", std::string type = "", std::string content = "");

	Element* findElement(std::string tag, std::string name = "", std::string type = "");
	Element* findElement(Element* p_parent, std::string tag, std::string name = "", std::string type = "");

private:
	void checkHeader(std::ifstream& file);
	void skipEmptyChars(std::ifstream& file);

	Element* readElement(std::ifstream& file);
	void writeElement(Element* p_element, std::ofstream& file, int depth);

	std::string readTag(std::ifstream& file);
	std::string readArgument(std::string arg, std::ifstream& file);
};