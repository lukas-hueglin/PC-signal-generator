#pragma once
#include "Core/IGraphics2D.h"
#include "Common/MathUtils.h"

class GUI_API Win32Graphics2D : public IGraphics2D {

private:
	HWND m_hWnd;

protected:
	ID2D1Factory* mp_2DFactory;
	IDWriteFactory* mp_writeFactory;

	ID2D1HwndRenderTarget* mp_renderTarget;

	PAINTSTRUCT m_ps;

public:
	Win32Graphics2D(HWND hWnd);
	~Win32Graphics2D();

public:
	void beginPaint();
	void endPaint();

	void createGraphicsAssets();
	void discardGraphicsAssets();

	void resizeCanvas();
	
	Math::Rect getDPISize();

private:
	void initGraphicsAssets();

	ID2D1Factory* get2DFactory();
	ID2D1HwndRenderTarget* getRenderTarget();
	IDWriteFactory* getWriteFactory();

	// make widget implementations a friend
	friend class Win32FrameImpl;
	friend class Win32WidgetImpl;
	friend class Win32LayoutImpl;
	friend class Win32LabelImpl;
	friend class Win32CheckBoxImpl;
	friend class Win32ButtonImpl;
	friend class Win32TextBoxImpl;
	friend class Win32SliderImpl;
	friend class Win32PlotImpl;
	friend class Win32PlotSeries1DImpl;
	friend class Win32PlotSeries1DImpl;
};