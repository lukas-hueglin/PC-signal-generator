#pragma once
#include "Widgets/AWidgetImpl.h"

class GUI_API Win32WidgetImpl : public AWidgetImpl {

private:
	Math::Rect m_rect;

	ID2D1SolidColorBrush* mp_fillBrush;

public:
	Win32WidgetImpl(Graphics2D* p_graphics, WidgetStyle style);
	~Win32WidgetImpl();

public:
	void onPaint() override;
	void onResize(Math::Rect availableRect) override;

private:
	void initGraphicsResources();
};