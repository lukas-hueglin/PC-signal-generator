#pragma once
#include "Core/IFunctional.h"
#include "Common/Signal.h"

#include <string>

class Functional : public IFunctional {

private:

public:
	Functional();

public:

private:
	void onTick(float deltaTime);

	IMPLEMENT_LOADSAVE(Functional);

};