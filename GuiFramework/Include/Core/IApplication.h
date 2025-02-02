#pragma once
#include "Gui.h"
#include "Core/MainWindow.h"
#include "Core/Graphics2D.h"
#include "Core/IFunctional.h"

#include <vector>

#define REGISTER_FUNCTIONAL(p_functional) mp_functionals.push_back(p_functional);

class GUI_API IApplication {

private:
	MainWindow* mp_mainWindow;

protected:
	std::vector<IFunctional*> mp_functionals;

public:
	IApplication(int argc, char** argv);

public:
	virtual int exec() = 0;

	void setMainWindow(MainWindow* p_mainWindow);

protected:
	void onTick(float deltaTime);

	virtual void onBegin();
	virtual void onClose();

	virtual void loadFunctional() {};
	virtual void saveFunctional() {};

	virtual void initUI() = 0;

	virtual std::wstring getApplicationName() = 0;
	virtual std::wstring getIniPath() = 0;
};