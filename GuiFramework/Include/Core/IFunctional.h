#pragma once
#include "Gui.h"
#include "Common/Reflection/Internal.h"

#include <string>

#define IMPLEMENT_LOADSAVE(class_name) \
public:\
	void loadMembers(std::wstring path) {REFLECTION.load(#class_name, path);} \
	void saveMembers(std::wstring path) {REFLECTION.save(#class_name, path);} \

class GUI_API IFunctional {

	USE_REFLECTION()

public:
	virtual void loadMembers(std::wstring path) = 0;
	virtual void saveMembers(std::wstring path) = 0;

private:
	virtual void onTick(float deltaTime) = 0;
	virtual void onBegin() = 0;
	virtual void onClose() = 0;

	// make IApplication a friend
	friend class IApplication;
};