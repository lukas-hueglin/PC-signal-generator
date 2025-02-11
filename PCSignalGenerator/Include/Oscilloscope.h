#pragma once
#include <Audioclient.h>
#include <mmdeviceapi.h>

#include "Core/IFunctional.h"
#include "Common/Signal.h"
#include "Common/MathUtils.h"

#define OSC_DATA_BUFFER_SIZE 1024

class Oscilloscope : public IFunctional {

private:
	IMMDevice* mp_audioDevice;
	IAudioClient* mp_audioClient;
	IAudioCaptureClient* mp_audioCaptureClient;

	WAVEFORMATEX* mp_format;
	unsigned int m_bufferSize;

	float ma_data[OSC_DATA_BUFFER_SIZE]; // Rolling buffer
	int m_head;
	float m_lastValue; // stores the last value

	float m_sampleRate;
	int m_nSamplesSkiped;

	bool m_enable;
	int m_aquisitionMode;
	float m_triggerLevel;

public:
	Oscilloscope();
	~Oscilloscope();

public:
	float* getPlotData();
	int getPlotDataSize();

	int getAquisitionMode();
	float getTriggerLevel();
	bool isOscEnabled();
	
	void setAquisitionMode(int mode);
	void setTriggerLevel(float level);
	void enableOscilloscope(bool enable);

	void calculateSampleRate(Math::Size plotBounds);

	Signal<> onPlotUpdate;
	Signal<int> onTrigger;
	Signal<float, float> onBoundsChange;

private:
	void onTick(float deltaTime) override;
	void onBegin() override;
	void onClose() override;


	IMPLEMENT_LOADSAVE(Oscilloscope);
};