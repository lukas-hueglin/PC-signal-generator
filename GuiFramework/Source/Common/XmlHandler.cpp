#include "Gui.h"
#include "Common/XmlHandler.h"

#include <sstream>
#include <stdexcept>


XmlHandler::XmlHandler(std::wstring path) : m_path(path), mp_root(new Element{ .tag = "root" }) {

	// read xml file
	readXml();
}

void XmlHandler::readXml() {

	// open file
	std::ifstream file(m_path);

	// return if file is empty
	if (file.peek() == EOF) { return; }

	// check header
	checkHeader(file);

	// read file
	if (file.get() == '<') {
		mp_root = readElement(file);
	}
}

void XmlHandler::writeXml() {

	// create ofstream
	std::ofstream file(m_path);

	// write header
	file << XML_HEADER << '\n';

	// write root element
	writeElement(mp_root, file, 0);
}

void XmlHandler::setElement(Element* p_parent, std::string tag, std::string name, std::string type, std::string content) {

	// find element
	Element* found = findElement(p_parent, tag, name, type);

	// if found set content else create new element
	if (found != nullptr) {

		// only set content if there is no child
		if (found->child == nullptr) {
			found->content = content;
		}
	}
	else {
		createElement(p_parent, tag, name, type, content);
	}
}

Element* XmlHandler::createElement(std::string tag, std::string name, std::string type, std::string content) {

	return createElement(mp_root, tag, name, type, content);
}

Element* XmlHandler::createElement(Element* p_parent, std::string tag, std::string name, std::string type, std::string content) {
	
	Element* first = p_parent->child;
	p_parent->child = new Element{ .tag = tag, .name = name, .type = type, .content = content, .next = first };

	return p_parent->child;
}

Element* XmlHandler::findElement(std::string tag, std::string name, std::string type) {

	return findElement(mp_root, tag, name, type);
}

Element* XmlHandler::findElement(Element* p_parent, std::string tag, std::string name, std::string type) {
	
	if (p_parent->tag == tag && p_parent->name == name && p_parent->type == type) {
		return p_parent;
	}

	// create found element pointer
	Element* found = nullptr;

	if (p_parent->child != nullptr) {
		found = findElement(p_parent->child, tag, name, type);
	}

	if (found == nullptr && p_parent->next != nullptr) {
		found = findElement(p_parent->next, tag, name, type);
	}

	return found;
}

void XmlHandler::checkHeader(std::ifstream& file) {

	// read first line
	std::string header;
	std::getline(file, header);

	if (header != XML_HEADER) {
		throw std::invalid_argument("XML header is missing!");
	}
}

Element* XmlHandler::readElement(std::ifstream& file) {

	std::string buffer;

	// create new element
	Element* p_elem = new Element();

	skipEmptyChars(file);

	// read opening tag
	std::string tag = readTag(file);

	if (tag == "root") {

	}
	else if (tag == "reflect") {

		p_elem->name = readArgument("name", file);
	}
	else if (tag == "field") {

		p_elem->name = readArgument("name", file);
		p_elem->type = readArgument("type", file);
	}
	else {
		throw std::invalid_argument("Unknown XML tag used!");
	}

	// save tag
	p_elem->tag = tag;

	// absorb '>'
	file.get();

	skipEmptyChars(file);

	// check if there is content or a new tag
	if (file.peek() == '<') {

		// absorb '<'
		file.get();

		// check that is isn't a closing tag
		if (file.peek() != '/') {
			// read child element
			p_elem->child = readElement(file);
		}
	}
	else {

		// read content
		std::getline(file, p_elem->content, '\n');
	}

	// read closing tag
	skipEmptyChars(file);

	if (file.peek() == '<') { file.get(); }

	std::string closingTag;
	std::getline(file, closingTag, '>');

	if (closingTag != "/" + tag) {
		throw std::invalid_argument("XML tag not closed!");
	}

	// check if there is an element afterwards
	skipEmptyChars(file);

	if (file.get() == '<' && file.peek() != '/') {

		p_elem->next = readElement(file);
	}

	return p_elem;
}

void XmlHandler::writeElement(Element* p_element, std::ofstream& file, int depth) {

	// write tabstops
	for (int i = 0; i < depth; ++i) { file << '\t'; }

	// write open tag
	if (p_element->tag == "root") {
		file << '<' << p_element->tag << ">\n";
	}
	else if (p_element->tag == "reflect") {
		file << '<' << p_element->tag << " name=\"" << p_element->name << "\">\n";
	}
	if (p_element->tag == "field") {
		file << '<' << p_element->tag << " name=\"" << p_element->name << "\" type=\"" << p_element->type << "\">\n";
	}

	// write content
	if (p_element->child == nullptr) {

		// write tabstops
		for (int i = 0; i < depth+1; ++i) { file << '\t'; }
		file << p_element->content << '\n';
	}
	else {
		writeElement(p_element->child, file, depth + 1);
	}

	// write closing tab
	for (int i = 0; i < depth; ++i) { file << '\t'; }
	file << "</" << p_element->tag << ">\n";

	// write next element
	if (p_element->next != nullptr) {
		writeElement(p_element->next, file, depth);
	}
}

void XmlHandler::skipEmptyChars(std::ifstream& file) {

	// skip over all tabs, new lines and spaces
	while (file.peek() == '\t' || file.peek() == '\n' || file.peek() == ' ') { file.get(); }
}

std::string XmlHandler::readTag(std::ifstream& file) {

	// create buffer
	std::string tag;

	while (file.peek() != ' ' && file.peek() != '>') {
		tag += file.get();
	}

	return tag;
}

std::string XmlHandler::readArgument(std::string arg, std::ifstream& file) {

	// create buffer
	std::string buffer;

	// skip all empty characters
	skipEmptyChars(file);

	// read name
	std::getline(file, buffer, '=');
	if (buffer != arg) {
		throw std::invalid_argument("Argument '" + arg + "' is missing!");
	}

	// '"'
	char d = file.get();

	// read value into buffer
	std::getline(file, buffer, '\"');

	return buffer;
}