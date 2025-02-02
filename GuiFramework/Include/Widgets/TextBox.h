#pragma once
#include "Widgets/Widget.h"
#include "Common/Signal.h"

#ifdef WIN32
	#include "Platform/Win32/Win32TextBoxImpl.h"
	using TextBoxImpl = Win32TextBoxImpl;
#endif

class GUI_API TextBox : public Widget {

protected:
	std::wstring m_text;
	std::wstring m_backupText;

	int m_firstCursor;
	int m_lastCursor;
	float m_animCycle;

	bool m_dragFirstCursor;

	bool m_edit;
	bool m_requireDoubleClk;

	std::wstring m_prefix;
	std::wstring m_suffix;

	TextBoxImpl m_textBoxImpl;

public:
	TextBox(Window* p_parent, std::wstring, WidgetStyle style = Style::Default());

	void onTick(float deltaTime) override;
	void onPaint() override;

	void onResize(Math::Rect availableRect) override;

	void onMouseLeave() override;

	void onMouseHover(Math::Point2D point) override;
	void onMouseDown(bool doubleClk, Math::Point2D point) override;
	void onKeyDown(Key key) override;
	void onKeyDown(char key) override;

	void setRequireDoubleClick(bool requireDoubleClk);
	void setPrefix(std::wstring prefix);
	void setSuffix(std::wstring suffix);

	Signal<std::wstring> onTextChanged;

protected:
	virtual bool filterInput(char key);

	virtual void enableEditMode();
	virtual void disableEditMode(bool backup);

	void updateText();

};