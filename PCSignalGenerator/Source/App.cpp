#include "Gui.h"
#include "App.h"

#include <numbers>
#include <string>
#include <vector>

App::App(int argc, char** argv) : Application(argc, argv), mp_functional(new Functional()) {

	REGISTER_FUNCTIONAL(mp_functional)
}

App::~App() {

	delete mp_functional;

	delete mp_window;

	delete mp_sigGenPlot;
	delete mp_oscPlot;
	delete mp_bodeMagnitude;
	delete mp_bodePhase;

	delete mp_mainLayout;
	delete mp_parameterLayout;
	delete mp_plotLayout;

	delete mp_sigGenGroup;
	delete mp_oscGroup;
	delete mp_freqResponseGroup;

	delete mp_sigGenLayout;
	delete mp_oscLayout;
	delete mp_freqResponseLayout;

	delete mp_waveformLabel;
	delete mp_waveformComboBox;

	delete mp_frequencyLabel;
	delete mp_frequencySlider;

	delete mp_amplitudeLabel;
	delete mp_amplitudeSlider;

	delete mp_dutyCycleLabel;
	delete mp_dutyCycleSlider;
}

void App::initUI() {

	// create new window
	mp_window = MainWindow::create(TEXT(PROJECT_NAME));
	setMainWindow(mp_window);

	// create signal generator plot
	mp_sigGenPlot = new Plot(mp_window, L"Time", L"Voltage");
	mp_sigGenPlot->setXUnit(Unit::Second);
	mp_sigGenPlot->setYUnit(Unit::Volts);
	mp_sigGenPlot->setFillMode(FillMode::Expand);

	// create oscilloscope plot
	mp_oscPlot = new Plot(mp_window, L"Time", L"Voltage");
	mp_oscPlot->setXUnit(Unit::Second);
	mp_oscPlot->setYUnit(Unit::Volts);
	mp_oscPlot->setFillMode(FillMode::Expand);

	// create plots for bode plot
	mp_bodeMagnitude = new Plot(mp_window, L"Frequency", L"Voltage");
	mp_bodeMagnitude->setXUnit(Unit::Hertz);
	mp_bodeMagnitude->setYUnit(Unit::Volts);
	mp_bodeMagnitude->setFillMode(FillMode::Expand);

	mp_bodePhase = new Plot(mp_window, L"Frequency", L"Phase");
	mp_bodePhase->setXUnit(Unit::Hertz);
	mp_bodePhase->setYUnit(Unit::Volts);
	mp_bodePhase->setFillMode(FillMode::Expand);

	// create parameters
	mp_waveformLabel = new Label(mp_window, L"Waveform");
	mp_waveformLabel->setMargin(10.0f);
	mp_waveformLabel->setPadding(10.0f);

	mp_waveformComboBox = new ComboBox(mp_window, std::vector<std::wstring>({ L"Sine", L"Rectangular", L"Triangle", L"Sawtooth" }));
	mp_waveformComboBox->setMargin(10.0f);
	mp_waveformComboBox->setPadding(10.0f);


	mp_frequencyLabel = new Label(mp_window, L"Frequency");
	mp_frequencyLabel->setMargin(10.0f);
	mp_frequencyLabel->setPadding(10.0f);

	mp_frequencySlider = new Slider<float>(mp_window, 1000, 0, 20000);
	mp_frequencySlider->setMargin(10.0f);
	mp_frequencySlider->setPadding(10.0f);
	mp_frequencySlider->setSuffix(L" Hz");


	mp_amplitudeLabel = new Label(mp_window, L"Amplitude");
	mp_amplitudeLabel->setMargin(10.0f);
	mp_amplitudeLabel->setPadding(10.0f);

	mp_amplitudeSlider = new Slider<float>(mp_window, 1, 0, 5);
	mp_amplitudeSlider->setMargin(10.0f);
	mp_amplitudeSlider->setPadding(10.0f);
	mp_amplitudeSlider->setSuffix(L" V");


	mp_dutyCycleLabel = new Label(mp_window, L"DutyCycle");
	mp_dutyCycleLabel->setMargin(10.0f);
	mp_dutyCycleLabel->setPadding(10.0f);

	mp_dutyCycleSlider = new Slider<int>(mp_window, 50, 0, 100);
	mp_dutyCycleSlider->setMargin(10.0f);
	mp_dutyCycleSlider->setPadding(10.0f);
	mp_dutyCycleSlider->setSuffix(L" %");


	// create parameter GridLayouts
	mp_sigGenLayout = new GridLayout(mp_window, 4, 2);
	mp_oscLayout = new GridLayout(mp_window, 4, 2);
	mp_freqResponseLayout = new GridLayout(mp_window, 4, 2);

	mp_sigGenLayout->addFrame(mp_waveformLabel, 0, 0);
	mp_sigGenLayout->addFrame(mp_waveformComboBox, 0, 1);
	mp_sigGenLayout->addFrame(mp_frequencyLabel, 1, 0);
	mp_sigGenLayout->addFrame(mp_frequencySlider, 1, 1);
	mp_sigGenLayout->addFrame(mp_amplitudeLabel, 2, 0);
	mp_sigGenLayout->addFrame(mp_amplitudeSlider, 2, 1);
	mp_sigGenLayout->addFrame(mp_dutyCycleLabel, 3, 0);
	mp_sigGenLayout->addFrame(mp_dutyCycleSlider, 3, 1);

	// create GroupBoxes
	mp_sigGenGroup = new GroupBox(mp_window, mp_sigGenLayout, L"Signal Generator");
	mp_sigGenGroup->setMargin(10.0f);
	mp_sigGenGroup->setPadding(10.0f);

	mp_oscGroup = new GroupBox(mp_window, mp_oscLayout, L"Oscilloscope");
	mp_oscGroup->setMargin(10.0f);
	mp_oscGroup->setPadding(10.0f);

	mp_freqResponseGroup = new GroupBox(mp_window, mp_freqResponseLayout, L"Frequency Response");
	mp_freqResponseGroup->setMargin(10.0f);
	mp_freqResponseGroup->setPadding(10.0f);

	// create Layouts
	mp_mainLayout = new LinearLayout(mp_window, Orientation::Horizontal);

	mp_parameterLayout = new LinearLayout(mp_window, Orientation::Vertical);
	mp_parameterLayout->setFillMode(FillMode::Shrink);

	mp_plotLayout = new GridLayout(mp_window, 2, 2);
	mp_plotLayout->setFillMode(FillMode::Expand);


	// add to Layouts
	mp_plotLayout->addFrame(mp_sigGenPlot, 0, 0);
	mp_plotLayout->addFrame(mp_oscPlot, 0, 1);
	mp_plotLayout->addFrame(mp_bodeMagnitude, 1, 0);
	mp_plotLayout->addFrame(mp_bodePhase, 1, 1);

	mp_parameterLayout->addFrame(mp_sigGenGroup);
	mp_parameterLayout->addFrame(mp_oscGroup);
	mp_parameterLayout->addFrame(mp_freqResponseGroup);

	mp_mainLayout->addFrame(mp_plotLayout);
	mp_mainLayout->addFrame(mp_parameterLayout);

	// set main layout
	mp_window->setLayout(mp_mainLayout);
}

std::wstring App::getApplicationName() {
	return TEXT(PROJECT_NAME);
}
