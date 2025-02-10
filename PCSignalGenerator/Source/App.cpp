#include "Gui.h"
#include "App.h"

#include "Style/Palette.h"

#include <numbers>
#include <string>
#include <vector>

App::App(int argc, char** argv) : Application(argc, argv), mp_sigGen(new SignalGenerator()) {

	REGISTER_FUNCTIONAL(mp_sigGen)
}

App::~App() {

	delete mp_sigGen;

	delete mp_window;

	delete mp_sigGenPlot;
	delete mp_oscPlot;
	delete mp_bodeMagnitude;
	delete mp_bodePhase;

	delete mp_sigGenPlotSeries;
	delete mp_oscPlotSeries;

	delete mp_mainLayout;
	delete mp_parameterLayout;
	delete mp_plotLayout;

	delete mp_sigGenGroup;
	delete mp_oscGroup;
	delete mp_freqResponseGroup;

	delete mp_sigGenLayout;
	delete mp_oscLayout;
	delete mp_freqResponseLayout;

	delete mp_enableCheckBox;

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
	mp_sigGenPlot = new Plot(mp_window, L"Phase", L"Voltage");
	mp_sigGenPlot->setXUnit(Unit::Radians);
	mp_sigGenPlot->setYUnit(Unit::Volts);
	mp_sigGenPlot->setFillMode(FillMode::Expand);

	// create plot series
	mp_sigGenPlotSeries = new PlotSeries1D(mp_sigGenPlot, mp_sigGen->getPlotData(), 0,
		2 * std::numbers::pi,mp_sigGen->getPlotDataSize(), Palette::Plot(2));

	mp_sigGenPlot->addPlotSeries(mp_sigGenPlotSeries);

	connect<SignalGenerator, PlotSeries1D>(mp_sigGenPlotSeries, &PlotSeries1D::onUpdate, mp_sigGen->onPlotUpdate);

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

	mp_enableCheckBox = new CheckBox(mp_window, L"Enable Output", mp_sigGen->getOutput());
	mp_enableCheckBox->setMargin(10.0f);
	mp_enableCheckBox->setPadding(10.0f);
	connect<CheckBox, SignalGenerator, bool>(mp_sigGen, &SignalGenerator::enableOutput, mp_enableCheckBox->onStateChanged);


	mp_waveformLabel = new Label(mp_window, L"Waveform");
	mp_waveformLabel->setMargin(10.0f);
	mp_waveformLabel->setPadding(10.0f);

	mp_waveformComboBox = new ComboBox(mp_window, std::vector<std::wstring>({ L"Sine", L"Rectangular", L"Triangle", L"Sawtooth" }));
	mp_waveformComboBox->setMargin(10.0f);
	mp_waveformComboBox->setPadding(10.0f);

	// connect ComboBox!!
	//connect<ComboBox, SignalGenerator, int>(mp_sigGen, &SignalGenerator::setWaveformType, mp_waveformComboBox->)


	mp_frequencyLabel = new Label(mp_window, L"Frequency");
	mp_frequencyLabel->setMargin(10.0f);
	mp_frequencyLabel->setPadding(10.0f);

	mp_frequencySlider = new Slider<float>(mp_window, mp_sigGen->getFrequency(), 0, 20000);
	mp_frequencySlider->setMargin(10.0f);
	mp_frequencySlider->setPadding(10.0f);
	mp_frequencySlider->setSuffix(L" Hz");
	connect<Slider<float>, SignalGenerator, float>(mp_sigGen, &SignalGenerator::setFrequency, mp_frequencySlider->onValueChanged);


	mp_amplitudeLabel = new Label(mp_window, L"Amplitude");
	mp_amplitudeLabel->setMargin(10.0f);
	mp_amplitudeLabel->setPadding(10.0f);

	mp_amplitudeSlider = new Slider<float>(mp_window, mp_sigGen->getAmplitude(), 0, 5);
	mp_amplitudeSlider->setMargin(10.0f);
	mp_amplitudeSlider->setPadding(10.0f);
	mp_amplitudeSlider->setSuffix(L" V");
	connect<Slider<float>, SignalGenerator, float>(mp_sigGen, &SignalGenerator::setAmplitude, mp_amplitudeSlider->onValueChanged);


	mp_dutyCycleLabel = new Label(mp_window, L"DutyCycle");
	mp_dutyCycleLabel->setMargin(10.0f);
	mp_dutyCycleLabel->setPadding(10.0f);

	mp_dutyCycleSlider = new Slider<int>(mp_window, mp_sigGen->getDutyCycle(), 0, 100);
	mp_dutyCycleSlider->setMargin(10.0f);
	mp_dutyCycleSlider->setPadding(10.0f);
	mp_dutyCycleSlider->setSuffix(L" %");
	connect<Slider<int>, SignalGenerator, int>(mp_sigGen, &SignalGenerator::setDutyCycle, mp_dutyCycleSlider->onValueChanged);


	// create parameter GridLayouts
	mp_sigGenLayout = new GridLayout(mp_window, 5, 2);
	mp_oscLayout = new GridLayout(mp_window, 4, 2);
	mp_freqResponseLayout = new GridLayout(mp_window, 4, 2);

	mp_sigGenLayout->addFrame(mp_enableCheckBox, 0, 0);
	mp_sigGenLayout->addFrame(mp_waveformLabel, 1, 0);
	mp_sigGenLayout->addFrame(mp_waveformComboBox, 1, 1);
	mp_sigGenLayout->addFrame(mp_frequencyLabel, 2, 0);
	mp_sigGenLayout->addFrame(mp_frequencySlider, 2, 1);
	mp_sigGenLayout->addFrame(mp_amplitudeLabel, 3, 0);
	mp_sigGenLayout->addFrame(mp_amplitudeSlider, 3, 1);
	mp_sigGenLayout->addFrame(mp_dutyCycleLabel, 4, 0);
	mp_sigGenLayout->addFrame(mp_dutyCycleSlider, 4, 1);

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
