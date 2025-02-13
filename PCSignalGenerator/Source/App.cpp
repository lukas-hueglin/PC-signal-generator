#include "Gui.h"
#include "App.h"

#include "Style/Palette.h"

#include <numbers>
#include <string>
#include <vector>

App::App(int argc, char** argv) : Application(argc, argv), mp_sigGen(new SignalGenerator()), mp_osc(new Oscilloscope) {

	REGISTER_FUNCTIONAL(mp_sigGen)
	REGISTER_FUNCTIONAL(mp_osc)
}

App::~App() {

	delete mp_sigGen;
	delete mp_osc;

	delete mp_window;

	delete mp_sigGenPlot;
	delete mp_oscPlot;
	delete mp_bode;

	delete mp_sigGenPlotSeries;
	delete mp_oscPlotSeries;

	delete mp_mainLayout;
	delete mp_parameterLayout;
	delete mp_vertPlotLayout;
	delete mp_horPlotLayout;


	delete mp_sigGenGroup;
	delete mp_oscGroup;
	delete mp_freqResponseGroup;

	delete mp_sigGenLayout;
	delete mp_oscLayout;
	delete mp_freqResponseLayout;

	delete mp_enableSigGenLabel;
	delete mp_enableSigGenButton;

	delete mp_waveformLabel;
	delete mp_waveformComboBox;

	delete mp_frequencyLabel;
	delete mp_frequencySlider;

	delete mp_amplitudeLabel;
	delete mp_amplitudeSlider;

	delete mp_dutyCycleLabel;
	delete mp_dutyCycleSlider;

	delete mp_enableOscLabel;
	delete mp_enableOscButton;

	delete mp_aquisitionModeLabel;
	delete mp_aquisitionModeComboBox;

	delete mp_triggerLevelLabel;
	delete mp_triggerLevelSlider;
}

void App::initUI() {

	// create new window
	mp_window = MainWindow::create(TEXT(PROJECT_NAME));
	setMainWindow(mp_window);

	// create signal generator plot
	mp_sigGenPlot = new Plot(mp_window, L"Phase", L"Voltage");
	mp_sigGenPlot->setXUnit(Unit::Radians);
	mp_sigGenPlot->setYUnit(Unit::Volts);
	mp_sigGenPlot->setLockXZoom(true);
	mp_sigGenPlot->setFillMode(FillMode::Expand);
	mp_sigGenPlot->setPlotXBounds(0, 2 * std::numbers::pi);
	//mp_sigGenPlot->setPlotYBounds(-7, 7);

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

	connect<Plot, Oscilloscope, Math::Size>(mp_osc, &Oscilloscope::calculateSampleRate, mp_oscPlot->onZoom);

	// create plot series
	mp_oscPlotSeries = new PlotSeries1D(mp_oscPlot, mp_osc->getPlotData(), -1, 1, mp_osc->getPlotDataSize(), Palette::Plot(0));
	mp_oscPlot->addPlotSeries(mp_oscPlotSeries);

	connect<Oscilloscope, PlotSeries1D>(mp_oscPlotSeries, &PlotSeries1D::onUpdate, mp_osc->onPlotUpdate);
	connect<Oscilloscope, PlotSeries1D, int>(mp_oscPlotSeries, &PlotSeries1D::setHead, mp_osc->onTrigger);
	connect<Oscilloscope, PlotSeries1D, float, float>(mp_oscPlotSeries, &PlotSeries1D::setBounds, mp_osc->onBoundsChange);

	// create bode plot
	mp_bode = new Plot(mp_window, L"Frequency", L"Voltage");
	mp_bode->setXUnit(Unit::Hertz);
	mp_bode->setYUnit(Unit::Volts);
	mp_bode->setFillMode(FillMode::Expand);

	// create parameters
	mp_enableSigGenLabel = new Label(mp_window, L"Signal Generator");
	mp_enableSigGenLabel->setMargin(10.0f);
	mp_enableSigGenLabel->setPadding(10.0f);

	mp_enableSigGenButton = new StateButton(mp_window, std::vector<std::wstring>({ L"Off", L"On"}));
	mp_enableSigGenButton->setState(mp_sigGen->isOutputEnabled());
	mp_enableSigGenButton->setMargin(10.0f);
	mp_enableSigGenButton->setPadding(10.0f);
	connect<StateButton, SignalGenerator, int>(mp_sigGen, &SignalGenerator::enableOutput, mp_enableSigGenButton->onStateChanged);


	mp_waveformLabel = new Label(mp_window, L"Waveform");
	mp_waveformLabel->setMargin(10.0f);
	mp_waveformLabel->setPadding(10.0f);

	mp_waveformComboBox = new ComboBox(mp_window, std::vector<std::wstring>({ L"Sine", L"Rectangular", L"Triangle", L"Sawtooth" }));
	mp_waveformComboBox->setState(mp_sigGen->getWaveformType());
	mp_waveformComboBox->setMargin(10.0f);
	mp_waveformComboBox->setPadding(10.0f);
	connect<ComboBox, SignalGenerator, int>(mp_sigGen, &SignalGenerator::setWaveformType, mp_waveformComboBox->onStateChanged);


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


	mp_enableOscLabel = new Label(mp_window, L"Oscilloscope");
	mp_enableOscLabel->setMargin(10.0f);
	mp_enableOscLabel->setPadding(10.0f);

	mp_enableOscButton = new StateButton(mp_window, std::vector<std::wstring>({ L"Stop", L"Run"}));
	mp_enableOscButton->setState(mp_osc->isOscEnabled());
	mp_enableOscButton->setMargin(10.0f);
	mp_enableOscButton->setPadding(10.0f);
	connect<StateButton, Oscilloscope, int>(mp_osc, &Oscilloscope::enableOscilloscope, mp_enableOscButton->onStateChanged);


	mp_aquisitionModeLabel = new Label(mp_window, L"Aquisition Mode");
	mp_aquisitionModeLabel->setMargin(10.0f);
	mp_aquisitionModeLabel->setPadding(10.0f);

	mp_aquisitionModeComboBox = new ComboBox(mp_window, std::vector<std::wstring>({ L"Trigger", L"Rolling" }));
	mp_aquisitionModeComboBox->setState(mp_osc->getAquisitionMode());
	mp_aquisitionModeComboBox->setMargin(10.0f);
	mp_aquisitionModeComboBox->setPadding(10.0f);
	connect<ComboBox, Oscilloscope, int>(mp_osc, &Oscilloscope::setAquisitionMode, mp_aquisitionModeComboBox->onStateChanged);


	mp_triggerLevelLabel = new Label(mp_window, L"Trigger Level");
	mp_triggerLevelLabel->setMargin(10.0f);
	mp_triggerLevelLabel->setPadding(10.0f);

	mp_triggerLevelSlider = new Slider<float>(mp_window, mp_osc->getTriggerLevel(), -5, 5);
	mp_triggerLevelSlider->setMargin(10.0f);
	mp_triggerLevelSlider->setPadding(10.0f);
	mp_triggerLevelSlider->setSuffix(L" V");
	connect<Slider<float>, Oscilloscope, float>(mp_osc, &Oscilloscope::setTriggerLevel, mp_triggerLevelSlider->onValueChanged);

	// create parameter GridLayouts
	mp_sigGenLayout = new GridLayout(mp_window, 5, 2);
	mp_oscLayout = new GridLayout(mp_window, 3, 2);
	mp_freqResponseLayout = new GridLayout(mp_window, 4, 2);

	mp_sigGenLayout->addFrame(mp_enableSigGenLabel, 0, 0);
	mp_sigGenLayout->addFrame(mp_enableSigGenButton, 0, 1);
	mp_sigGenLayout->addFrame(mp_waveformLabel, 1, 0);
	mp_sigGenLayout->addFrame(mp_waveformComboBox, 1, 1);
	mp_sigGenLayout->addFrame(mp_frequencyLabel, 2, 0);
	mp_sigGenLayout->addFrame(mp_frequencySlider, 2, 1);
	mp_sigGenLayout->addFrame(mp_amplitudeLabel, 3, 0);
	mp_sigGenLayout->addFrame(mp_amplitudeSlider, 3, 1);
	mp_sigGenLayout->addFrame(mp_dutyCycleLabel, 4, 0);
	mp_sigGenLayout->addFrame(mp_dutyCycleSlider, 4, 1);

	mp_oscLayout->addFrame(mp_enableOscLabel, 0, 0);
	mp_oscLayout->addFrame(mp_enableOscButton, 0, 1);
	mp_oscLayout->addFrame(mp_aquisitionModeLabel, 1, 0);
	mp_oscLayout->addFrame(mp_aquisitionModeComboBox, 1, 1);
	mp_oscLayout->addFrame(mp_triggerLevelLabel, 2, 0);
	mp_oscLayout->addFrame(mp_triggerLevelSlider, 2, 1);

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

	mp_vertPlotLayout = new LinearLayout(mp_window, Orientation::Vertical);

	mp_horPlotLayout = new LinearLayout(mp_window, Orientation::Horizontal);


	// add to Layouts
	mp_vertPlotLayout->addFrame(mp_oscPlot);
	mp_vertPlotLayout->addFrame(mp_horPlotLayout);
	mp_horPlotLayout->addFrame(mp_sigGenPlot);
	mp_horPlotLayout->addFrame(mp_bode);

	mp_parameterLayout->addFrame(mp_sigGenGroup);
	mp_parameterLayout->addFrame(mp_oscGroup);
	mp_parameterLayout->addFrame(mp_freqResponseGroup);

	mp_mainLayout->addFrame(mp_vertPlotLayout);
	mp_mainLayout->addFrame(mp_parameterLayout);

	// set main layout
	mp_window->setLayout(mp_mainLayout);
}

std::wstring App::getApplicationName() {
	return TEXT(PROJECT_NAME);
}
