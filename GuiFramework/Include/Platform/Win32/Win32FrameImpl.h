#pragma once
#include "Widgets/AFrameImpl.h"

class GUI_API Win32FrameImpl : public AFrameImpl {

private:
	Math::Rect m_usedRect;
	Math::Rect m_hitboxRect;
	Math::Rect m_contentRect;

	ID2D1SolidColorBrush* mp_debug1Brush;
	ID2D1SolidColorBrush* mp_debug2Brush;
	ID2D1SolidColorBrush* mp_debug3Brush;

public:
	Win32FrameImpl(Graphics2D* p_graphics);
	~Win32FrameImpl();

public:
	void onPaint() override;
	void onResize(Math::Rect usedRect, Math::Rect hitboxRect, Math::Rect contentRect) override;

private:
	void initGraphicsResources();
};