#include "Gui.h"
#include "Application.h"

#include "Core/MainWindow.h"
#include "Widgets/Button.h"
#include "Widgets/LinearLayout.h"
#include "Widgets/GroupBox.h"
#include "Widgets/GridLayout.h"
#include "Widgets/CheckBox.h"
#include "Widgets/Slider.h"
#include "Widgets/TextBox.h"
#include "Widgets/ComboBox.h"
#include "Widgets/Plot.h"
#include "Widgets/PlotSeries1D.h"
#include "Style/Palette.h"

#include <numbers>
#include <string>

App::App(int argc, char** argv) : Application(argc, argv), mp_functional(new Functional()) {

	REGISTER_FUNCTIONAL(mp_functional)
}

void App::initUI() {

	// create new window
	std::wstring s = L"Window";
	MainWindow* window = MainWindow::create(s);
	setMainWindow(window);

	// create a horizontal layout
	LinearLayout* horizontalLayout = new LinearLayout(window, Orientation::Horizontal);
	window->setLayout(horizontalLayout);

	// create a layout
	GridLayout* gridLayout = new GridLayout(window, 5, 2);

	// create a label
	Label* l1 = new Label(window, L"Frequency");
	l1->setMargin(10);
	l1->setPadding(10);

	gridLayout->addFrame(l1, 0, 0);

	// create a Slider
	Slider<float>* s1 = new Slider<float>(window, mp_functional->getFreqIncrement(), 0, 1);
	s1->setSuffix(L" Hz");
	s1->setMargin(10);
	s1->setPadding(10);

	connect<Slider<float>, Functional, float>(mp_functional, &Functional::setFreqIncrement, s1->onValueChanged);

	gridLayout->addFrame(s1, 0, 1);

	// create a label
	Label* l2 = new Label(window, L"Action");
	l2->setMargin(10);
	l2->setPadding(10);

	gridLayout->addFrame(l2, 1, 0);

	// create a button
	Button* b1 = new Button(window, L"Button");
	b1->setMargin(10);
	b1->setPadding(10);

	gridLayout->addFrame(b1, 1, 1);

	// create a label
	Label* l3 = new Label(window, L"Write if you want");
	l3->setMargin(10);
	l3->setPadding(10);

	gridLayout->addFrame(l3, 2, 0);

	// create a textBox
	TextBox* t1 = new TextBox(window, L"Here...");
	t1->setMargin(10);
	t1->setPadding(10);

	gridLayout->addFrame(t1, 2, 1);

	// create a label
	Label* l4 = new Label(window, L"Choose a Number");
	l4->setMargin(10);
	l4->setPadding(10);

	gridLayout->addFrame(l4, 3, 0);

	// create a combobox
	ComboBox* c1 = new ComboBox(window, std::vector<std::wstring>({ L"Number 1", L"Number 2", L"Number 3", L"Number 4" }));
	c1->setMargin(10);
	c1->setPadding(10);

	gridLayout->addFrame(c1, 3, 1);

	// create a label
	Label* l5 = new Label(window, L"Enable Warp Drive");
	l5->setMargin(10);
	l5->setPadding(10);

	gridLayout->addFrame(l5, 4, 0);

	// create checkbox
	CheckBox* c2 = new CheckBox(window, L"Warp Drive", false);
	c2->setMargin(10);
	c2->setPadding(10);

	gridLayout->addFrame(c2, 4, 1);

	// create GroupBox
	GroupBox* g1 = new GroupBox(window, gridLayout, L"Parameters");
	g1->setMargin(10);
	g1->setPadding(10);

	// create a plot
	Plot* plot = new Plot(window, L"Time", L"Voltage");
	plot->setFillMode(FillMode::Expand);

	// create a plot series
	PlotSeries1D* series = new PlotSeries1D(plot, mp_functional->getPlotData(), 0, 2 * std::numbers::pi, mp_functional->getPlotSize(), Palette::Plot(0));
	plot->addPlotSeries(series);

	// add to layouts
	horizontalLayout->addFrame(plot);
	horizontalLayout->addFrame(g1);
}

std::wstring App::getApplicationName() {
	return TEXT(PROJECT_NAME);
}
