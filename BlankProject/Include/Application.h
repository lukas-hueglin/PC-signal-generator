#pragma once
#include "Core/Application.h"
#include "Functional.h"

class App : public Application {

private:
	Functional* mp_functional;

public:
	App(int argc, char** argv);

private:
	void initUI() override;

	std::wstring getApplicationName();
};