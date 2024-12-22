#include "Widgets/LinearLayout.h"
#include "Style/WidgetStyle.h"
#include "Style/Style.h"

class GUI_API DropDown : public LinearLayout {

private:
	Frame* mp_client;

public:
	DropDown(Window* p_parent, Frame* p_client, Math::Point2D origin, std::vector<std::wstring> elements, WidgetStyle style = Style::Default());

	~DropDown();
};