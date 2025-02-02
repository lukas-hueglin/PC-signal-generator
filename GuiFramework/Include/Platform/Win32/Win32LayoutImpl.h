#pragma once
#include "Widgets/ALayoutImpl.h"

class GUI_API Win32LayoutImpl : public ALayoutImpl {

private:
	ID2D1SolidColorBrush* mp_brush;

public:
	Win32LayoutImpl(Graphics2D* p_graphics, WidgetStyle style);
	~Win32LayoutImpl();

public:
	void onPaint(Math::Rect usedRect) override;

private:
	void initGraphicsResources();
};