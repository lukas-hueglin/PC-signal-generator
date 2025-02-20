#include "Gui.h"
#include "Core/IApplication.h"

IApplication::IApplication(int argc, char** argv) : mp_mainWindow(nullptr) { }

void IApplication::onTick(float deltaTime) {

	if (mp_mainWindow != nullptr) {
		mp_mainWindow->onTick(deltaTime);
	}

	for (IFunctional* p_functional : mp_functionals) {
		p_functional->onTick(deltaTime);
	}
}

void IApplication::onBegin() {
	
	// load all members of functional classes
	for (IFunctional* p_functional : mp_functionals) {
		p_functional->loadMembers(getIniPath());
		p_functional->onBegin();
	}

	// init widgets
	initUI();
}

void IApplication::onClose() {

	// save all members of functional classes
	for (IFunctional* p_functional : mp_functionals) {
		p_functional->saveMembers(getIniPath());
		p_functional->onClose();
	}
}

void IApplication::setMainWindow(MainWindow* p_mainWindow) {

	mp_mainWindow = p_mainWindow;
}
