#include "Gui.h"
#include "SignalGenerator.h"
#include "Common/Reflection/Internal.h"

#include <numbers>
#include <assert.h>

const CLSID CLSID_MMDeviceEnumerator = __uuidof(MMDeviceEnumerator);
const IID IID_IMMDeviceEnumerator = __uuidof(IMMDeviceEnumerator);
const IID IID_IAudioClient = __uuidof(IAudioClient);
const IID IID_IAudioRenderClient = __uuidof(IAudioRenderClient);

SignalGenerator::SignalGenerator() : m_output(false), m_phase(0.0f) {

	// add members to reflection
	ADD_FIELD(int, m_waveformType);
	ADD_FIELD(float, m_frequency);
	ADD_FIELD(float, m_amplitude);
	ADD_FIELD(int, m_dutyCycle);

	// initialize audio devices
	HRESULT hr;

	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	assert(SUCCEEDED(hr));

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
	hr = p_enumerator->GetDefaultAudioEndpoint(eRender, eConsole, &mp_audioDevice);
	assert(SUCCEEDED(hr));

	hr = mp_audioDevice->Activate(IID_IAudioClient, CLSCTX_ALL, NULL, (void**)&mp_audioClient);
	assert(SUCCEEDED(hr));

	// release enumerator
	hr = p_enumerator->Release();
	assert(SUCCEEDED(hr));

	// get audio format
	hr = mp_audioClient->GetMixFormat(&mp_format);
	assert(SUCCEEDED(hr));

	// initialize audio client
	hr = mp_audioClient->Initialize(AUDCLNT_SHAREMODE_SHARED, 0, REFTIMES_PER_SEC, 0, mp_format, NULL);
	assert(SUCCEEDED(hr));

	// create render client
	hr = mp_audioClient->GetService(IID_IAudioRenderClient, (void**)&mp_audioRenderClient);
	assert(SUCCEEDED(hr));

	// get buffer size
	hr = mp_audioClient->GetBufferSize(&m_bufferSize);
	assert(SUCCEEDED(hr));

	// create buffer
	byte* p_buffer;

	// get all available buffer space
	hr = mp_audioRenderClient->GetBuffer(m_bufferSize, &p_buffer);
	assert(SUCCEEDED(hr));

	// fill buffer
	fillWaveformBuffer(p_buffer, m_bufferSize);

	// write buffer
	hr = mp_audioRenderClient->ReleaseBuffer(m_bufferSize, 0);
	assert(SUCCEEDED(hr));

	// plot waveform
	calculatePlotWaveform();
}

SignalGenerator::~SignalGenerator() {

	mp_audioClient->Stop();

	mp_audioRenderClient->Release();
	mp_audioClient->Release();
	mp_audioDevice->Release();

	CoUninitialize();
}

void SignalGenerator::enableOutput(bool output) {

	m_output = output;

	// start audio
	HRESULT hr;
	if (m_output) {
		hr = mp_audioClient->Start();
		assert(SUCCEEDED(hr));
	}
	else {
		hr = mp_audioClient->Stop();
		assert(SUCCEEDED(hr));
	}
}

void SignalGenerator::setWaveformType(int waveformType) {

	m_waveformType = waveformType;
	calculatePlotWaveform();
}

void SignalGenerator::setFrequency(float frequency) {

	m_frequency = frequency;
}

void SignalGenerator::setAmplitude(float amplitude) {

	m_amplitude = amplitude;
	calculatePlotWaveform();
}

void SignalGenerator::setDutyCycle(int dutyCycle) {

	m_dutyCycle = dutyCycle;
	calculatePlotWaveform();
}

float* SignalGenerator::getPlotData() {

	return mpa_plotData;
}

int SignalGenerator::getPlotDataSize() {

	return SIGGEN_PLOT_SIZE;
}

bool SignalGenerator::getOutput() {

	return m_output;
}

int SignalGenerator::getWaveformType()
{
	return m_waveformType;
}

float SignalGenerator::getFrequency() {

	return m_frequency;
}

float SignalGenerator::getAmplitude() {

	return m_amplitude;
}

int SignalGenerator::getDutyCycle() {

	return m_dutyCycle;
}


void SignalGenerator::onTick(float deltaTime) {

	// create hresult
	HRESULT hr;

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
	hr = mp_audioRenderClient->GetBuffer(availableFrames, &p_buffer);
	assert(SUCCEEDED(hr));

	// fill buffer
	fillWaveformBuffer(p_buffer, availableFrames);

	// write buffer
	hr = mp_audioRenderClient->ReleaseBuffer(availableFrames, 0);
	assert(SUCCEEDED(hr));
}

void SignalGenerator::fillWaveformBuffer(byte* p_buffer, unsigned int nSamples) {

	// cast to float
	float* p_floatBuffer = (float*)p_buffer;

	// calculate proportion of one sample
	float proportionSample = m_frequency / mp_format->nSamplesPerSec;

	switch (m_waveformType) {
	case 0: { // sine waveform
	
		for (int i = 0; i < nSamples; ++i) {

			// calculate value
			float time = proportionSample * i + m_phase;
			float value = m_amplitude * sin(2 * std::numbers::pi * time);

			for (int c = 0; c < mp_format->nChannels; ++c) {
				p_floatBuffer[mp_format->nChannels * i + c] = value;
			}
		}

		break;
	}
	case 1: { // rectangular waveform

		for (int i = 0; i < nSamples; ++i) {

			// calculate value
			float time = proportionSample * i + m_phase;
			time -= floor(time);
			float value = time < m_dutyCycle / 100.0f ? m_amplitude : -m_amplitude;

			for (int c = 0; c < mp_format->nChannels; ++c) {
				p_floatBuffer[mp_format->nChannels * i + c] = value;
			}
		}

		break;
	}
	case 2: { // triangular waveform
	
		for (int i = 0; i < nSamples; ++i) {

			// calculate value
			float time = proportionSample * i + m_phase;
			time -= floor(time);
			float value;
			if (time < 0.25f) {

				value = time * m_amplitude / 0.25f;
			}
			else if (time < 0.75f) {

				value = m_amplitude * (2 - time / 0.25f);
			}
			else {
				
				value = m_amplitude * (time / 0.25f - 4);
			}

			for (int c = 0; c < mp_format->nChannels; ++c) {
				p_floatBuffer[mp_format->nChannels * i + c] = value;
			}
		}

		break;
	}
	case 3: { // sawtooth waveform
	
		for (int i = 0; i < nSamples; ++i) {

			// calculate value
			float time = proportionSample * i + m_phase;
			time -= floor(time);
			float value = m_amplitude * (2 * time - 1);

			for (int c = 0; c < mp_format->nChannels; ++c) {
				p_floatBuffer[mp_format->nChannels * i + c] = value;
			}
		}

		break;
	}
	}

	// calculate new phase
	m_phase += proportionSample * nSamples;
	m_phase -= floor(m_phase);
}

void SignalGenerator::calculatePlotWaveform() {

	switch (m_waveformType) {

	case 0: { // sine waveform
	
		for (int i = 0; i < SIGGEN_PLOT_SIZE; ++i) {

			float time = i / ((float)SIGGEN_PLOT_SIZE);
			mpa_plotData[i] = m_amplitude * sin(2 * std::numbers::pi * time);
		}
		break;
	}
	case 1: { // rectangular waveform

		for (int i = 0; i < SIGGEN_PLOT_SIZE; ++i) {

			float time = i / ((float)SIGGEN_PLOT_SIZE);
			mpa_plotData[i] = time < m_dutyCycle / 100.0f ? m_amplitude : -m_amplitude;
		}
		break;
	}
	case 2: { // triangular waveform

		for (int i = 0; i < SIGGEN_PLOT_SIZE; ++i) {

			float time = i / ((float)SIGGEN_PLOT_SIZE);

			if (time < 0.25f) {

				mpa_plotData[i] = time * m_amplitude / 0.25f;
			}
			else if (time < 0.75f) {

				mpa_plotData[i] = m_amplitude * (2 - time / 0.25f);
			}
			else {

				mpa_plotData[i] = m_amplitude * (time / 0.25f - 4);
			}
		}
		break;
	}
	case 3: { // sawtooth waveform

		for (int i = 0; i < SIGGEN_PLOT_SIZE; ++i) {

			float time = i / ((float)SIGGEN_PLOT_SIZE);
			mpa_plotData[i] = m_amplitude * (2 * time - 1);
		}
		break;
	}
	}

	// emit signal to update plot
	EMIT(onPlotUpdate);
}
