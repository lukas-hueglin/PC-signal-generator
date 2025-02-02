#pragma once
#include "Core/IGraphics.h"

enum Alignment;

class GUI_API IGraphics2D : public IGraphics {

public:
	virtual void beginPaint() = 0;
	virtual void endPaint() = 0;
};