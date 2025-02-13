#include "Widgets/Button.h"
#include "Common/Signal.h"
#include <vector>

class GUI_API ComboBox : public Button {

private:
	int m_state;
	std::vector<std::wstring> m_elements;

	WidgetStyle m_style;

public:
	ComboBox(Window* p_parent, std::vector<std::wstring> elements, WidgetStyle style = Style::Default());

public:
	void setState(int state);
	int getState();

	Signal<int> onStateChanged;

private:
	void createDropDown();
	void closeDropDown(int id);

	// make DropDown a friend class
	friend class DropDown;
};