#pragma once
#include "Common/MathUtils.h"
#include "Core/Window.h"
#include "Core/Graphics2D.h"
#include "Common/WidgetUtils.h"
#include "Core/Object.h"


class GUI_API Frame : public Object {

protected:
	Window* mp_parent;
	Graphics2D* mp_graphics;

	Math::Size m_minSize;
	Math::Rect m_usedRect;
	Math::Rect m_hitboxRect;
	Math::Rect m_contentRect;

	Alignment m_alignment;
	FillMode m_fillMode;

	float m_margin;
	float m_padding;

	bool m_immediateMode;
	bool m_requestRedraw;

#ifdef DEBUG_UI
private:
	GeometryResource* mp_debugResource1;
	GeometryResource* mp_debugResource2;
	GeometryResource* mp_debugResource3;
#endif

public:
	Frame(Window* p_parent);
	~Frame();

	virtual void onPaint();
	virtual void onTick(float deltaTime) = 0;

	virtual void onResize(Math::Rect availableRect);

	virtual void onMouseHover(Math::Point2D point) = 0;
	virtual void onMouseEnter() = 0;
	virtual void onMouseLeave() = 0;
	virtual void onMouseDown(bool doubleClk, Math::Point2D point) = 0;
	virtual void onMouseRelease(Math::Point2D point) = 0;

	virtual void onKeyDown(Key key) = 0;
	virtual void onKeyDown(char key) = 0;

	float getMargin();
	float getPadding();
	Math::Size getMinSize();
	Alignment getAlignment();
	FillMode getFillMode();

	void setMargin(float margin);
	void setPadding(float padding);
	void setMinSize(Math::Size size);
	void setAlignment(Alignment alignment);
	void setFillMode(FillMode fillMode);

	Math::Rect getHitbox();

	bool hasRequestedRedraw();
	bool isImmediateMode();

protected:
	void requestRedraw();
	void enableImmediateMode();
	void disableImmediateMode();
};