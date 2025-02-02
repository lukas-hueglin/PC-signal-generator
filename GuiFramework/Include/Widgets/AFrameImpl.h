#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Core/Graphics2D.h"

class GUI_API AFrameImpl {

protected:
	Graphics2D* mp_graphics;

public:
	AFrameImpl(Graphics2D* p_graphics) : mp_graphics(p_graphics) { };

public:
	virtual void onResize(Math::Rect usedRect, Math::Rect hitboxRect, Math::Rect contentRect) = 0;
	virtual void onPaint() = 0;
};