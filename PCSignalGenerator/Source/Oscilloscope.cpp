#include "Gui.h"
#include "Oscilloscope.h"
#include "Common/Reflection/Internal.h"

#include <numbers>
#include <assert.h>

#define REFTIMES_PER_SEC 1000000

const IID IID_IAudioCaptureClient = __uuidof(IAudioCaptureClient);

Oscilloscope::Oscilloscope() : m_head(0), m_lastValue(0.0f), m_enable(false), m_nSamplesSkiped(1) {

	// add members to reflection
	ADD_FIELD(int, m_aquisitionMode);
	ADD_FIELD(float, m_triggerLevel);

	// initialize audio devices
	HRESULT hr;

	//hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	//assert(SUCCEEDED(hr));

	// create enumerator
	IMMDeviceEnumerator* p_enumerator;

	hr = CoCreateInstance(
		CLSID_MMDeviceEnumerator,
		NULL,
		CLSCTX_ALL,
		IID_IMMDeviceEnumerator,
		(void**)&p_enumerator
	);
	assert(SUCCEEDED(hr));

	// create audio device
	hr = p_enumerator->GetDefaultAudioEndpoint(eCapture, eConsole, &mp_audioDevice);
	assert(SUCCEEDED(hr));

	hr = mp_audioDevice->Activate(IID_IAudioClient, CLSCTX_ALL, NULL, (void**)&mp_audioClient);
	assert(SUCCEEDED(hr));

	// release enumerator
	hr = p_enumerator->Release();
	assert(SUCCEEDED(hr));

	// get audio format
	hr = mp_audioClient->GetMixFormat(&mp_format);
	assert(SUCCEEDED(hr));

	// set sample rate
	m_sampleRate = mp_format->nSamplesPerSec;

	// initialize audio client
	hr = mp_audioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, REFTIMES_PER_SEC, 0, mp_format, NULL);
	assert(SUCCEEDED(hr));

	// create render client
	hr = mp_audioClient->GetService(IID_IAudioCaptureClient, (void**)&mp_audioCaptureClient);
	assert(SUCCEEDED(hr));

	// get buffer size
	hr = mp_audioClient->GetBufferSize(&m_bufferSize);
	assert(SUCCEEDED(hr));

	enableOscilloscope(true);
}

Oscilloscope::~Oscilloscope() {

	mp_audioClient->Stop();

	mp_audioCaptureClient->Release();
	mp_audioClient->Release();
	mp_audioDevice->Release();

	CoUninitialize();
}

float* Oscilloscope::getPlotData() {

	return ma_data;
}

int Oscilloscope::getPlotDataSize() {

	return OSC_DATA_BUFFER_SIZE;
}

void Oscilloscope::enableOscilloscope(bool enable) {

	m_enable = enable;

	if (m_enable) {
		mp_audioClient->Start();
	}
	else {
		mp_audioClient->Stop();
	}
}

void Oscilloscope::calculateSampleRate(Math::Size plotBounds) {

	// calculate optimal sample rate (Data should span two times the width of the plot)
	float exactSampleRate = OSC_DATA_BUFFER_SIZE / plotBounds.width() / 2.0f;

	// calculate every nth sample to be chosen and real sample rate
	m_nSamplesSkiped = max(mp_format->nSamplesPerSec / exactSampleRate, 1);
	m_sampleRate = mp_format->nSamplesPerSec / ((float) m_nSamplesSkiped);

	// update plot bounds
	float bounds = OSC_DATA_BUFFER_SIZE / m_sampleRate / 2;
	EMIT(onBoundsChange, -bounds, bounds);
}

bool Oscilloscope::isOscEnabled() {

	return m_enable;
}

void Oscilloscope::setAquisitionMode(int mode) {

	m_aquisitionMode = mode;
}

void Oscilloscope::setTriggerLevel(float level) {

	m_triggerLevel = level;
}

int Oscilloscope::getAquisitionMode() {

	return m_aquisitionMode;
}

float Oscilloscope::getTriggerLevel() {

	return m_triggerLevel;
}

void Oscilloscope::onTick(float deltaTime) {

	if (m_enable) {

		// create hresult and flags
		HRESULT hr;
		DWORD flags;

		unsigned int padding;
		unsigned int availableFrames;

		// get padding size
		hr = mp_audioClient->GetCurrentPadding(&padding);
		assert(SUCCEEDED(hr));

		// calculate available space
		availableFrames = m_bufferSize - padding;

		// create buffer
		BYTE* p_buffer;

		// get all available buffer space
		hr = mp_audioCaptureClient->GetBuffer(&p_buffer, &availableFrames, &flags, NULL, NULL);
		assert(SUCCEEDED(hr));

		// convert to float
		float* p_floatBuffer = (float*)p_buffer;

		// iterate over all datapoints and copy manually, that way triggering can be implemented
		for (int i = 0; i < availableFrames; i+= m_nSamplesSkiped) {

			float value = p_floatBuffer[mp_format->nChannels * i];
			ma_data[m_head] = value;

			// check aquisition mode
			switch (m_aquisitionMode) {

			case 0: { // trigger

				// check if signal changed sign
				if (m_lastValue < m_triggerLevel && value > m_triggerLevel) {

					// calculate new head for plot data, so that the triggerd sample is in the center
					int head = (m_head + OSC_DATA_BUFFER_SIZE / 2) % OSC_DATA_BUFFER_SIZE;

					// trigger
					EMIT(onTrigger, head);
				}
				break;
			}
			case 1: { // rolling

				EMIT(onTrigger, m_head);
				break;
			}}

			// increase and possibly wrap head
			if (++m_head == OSC_DATA_BUFFER_SIZE) {
				m_head = 0;
			}

			// set last value
			m_lastValue = value;
		}

		// release buffer
		hr = mp_audioCaptureClient->ReleaseBuffer(availableFrames);
		assert(SUCCEEDED(hr));

		// emit signal onPlotUpdate
		EMIT(onPlotUpdate);
	}
}

void Oscilloscope::onBegin() {
}

void Oscilloscope::onClose() {
}
