#pragma once
#include "Widgets/Label.h"
#include "Widgets/Button.h"
#include "Common/Signal.h"

#include <vector>

class GUI_API StateButton : public Label {

private:
	int m_state;
	std::vector<std::wstring> m_texts;

protected:
	ButtonImpl m_buttonImpl;

public:
	StateButton(Window* p_parent, std::vector<std::wstring> texts, WidgetStyle style = Style::Default());

	void onPaint() override;
	void onResize(Math::Rect availableRect) override;

	void onMouseRelease(Math::Point2D point) override;

	Signal<int> onStateChanged;
};