#pragma once
#include "Gui.h"
#include "Common/MathUtils.h"
#include "Common/EventUtils.h"
#include "Core/Graphics2D.h"

// forward declare layout
class Layout;
class DropDown;

class GUI_API IWindow {

protected:
	Graphics2D* mp_graphics;
	Math::Rect m_rect;

	Layout* mp_layout;
	DropDown* mp_dropDown;
	bool m_layoutMouseHover;
	bool m_dropDownMouseHover;

public:
	IWindow();
	
public:
	template<class DERIVED_TYPE>
	static DERIVED_TYPE* create(std::wstring title);

	void setLayout(Layout* p_layout);

	void registerDropDown(DropDown* p_dropDown);
	void unregisterDropDown();

	Graphics2D* getGraphics();

protected:
	void onTick(float deltaTime);

	void onBegin();
	void onPaint();
	void onDestroy();
	void onResize(Math::Rect rect);
	void onMouseMove(Math::Point2D point);
	void onMouseDown(bool doubleClk, Math::Point2D point);
	void onMouseRelease(Math::Point2D point);

	void onMouseScroll(bool up, bool shift, bool ctr);

	void onKeyDown(Key key);
	void onKeyDown(char key);

private:
	virtual void initialize(std::wstring title) = 0;


	// make IApplication a friend class
	friend class IApplication;
};