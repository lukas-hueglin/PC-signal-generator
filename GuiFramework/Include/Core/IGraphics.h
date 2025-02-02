#pragma once
#include "Gui.h"

class GUI_API IGraphics {

public:
	virtual void createGraphicsAssets() = 0;
	virtual void discardGraphicsAssets() = 0;

	virtual void resizeCanvas() = 0;
};