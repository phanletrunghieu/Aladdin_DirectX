#include "Sound.h"
#include "Graphics.h"

Sound* Sound::_instance = NULL;

Sound * Sound::GetInstance()
{
	if (_instance == NULL)
		_instance = new Sound(Graphics::GetInstance()->GetHWND());

	return _instance;
}

Sound::Sound(HWND hWnd)
{
	_primaryBuffer = 0;
	HRESULT result;

	DSBUFFERDESC bufferDesc; //describe the buffer

	result = DirectSoundCreate8(NULL, &_device, NULL);

	if (FAILED(result))
	{
		MessageBox(NULL, L"Can not sound create device", L"Error", MB_OK);
	}

	result = _device->SetCooperativeLevel(hWnd, DSSCL_PRIORITY); // set the cooperative level.

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_PRIMARYBUFFER | DSBCAPS_CTRLVOLUME;
	bufferDesc.dwBufferBytes = 0;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = NULL;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	result = _device->CreateSoundBuffer(&bufferDesc, &_primaryBuffer, NULL);

	if (FAILED(result))
	{
		MessageBox(NULL, L"Can not create sound primaryBuffer", L"Error", MB_OK);
	}
	_volume = 100.0f;
}

Sound::~Sound()
{
	for (auto it = _soundBufferMap.begin(); it != _soundBufferMap.end(); it++)
	{
		if (it->second)
		{
			it->second->Release();
			it->second = NULL;
		}

	}
	if (_primaryBuffer)
		_primaryBuffer->Release();
	if (_device)
		_device->Release();
	_device = NULL;

	_primaryBuffer = NULL;
}

float Sound::GetVolume()
{
	return _volume;
}

void Sound::SetVolume(float percentage, std::string name)
{
	_volume = percentage;
	if (name == "")
	{
		long volumne = (percentage) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
		for (std::map< std::string, IDirectSoundBuffer8*> ::iterator it = _soundBufferMap.begin(); it != _soundBufferMap.end(); it++)
		{
			it->second->SetVolume(volumne);
		}
	}
	else
	{
		std::map< std::string, IDirectSoundBuffer8*> ::iterator it;
		it = _soundBufferMap.find(name);
		if (it == _soundBufferMap.end())
			return;
		long volumne = (percentage) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
		it->second->SetVolume(volumne);
	}
}

void Sound::LoadSound(char * fileName, std::string name)
{
	if (_soundBufferMap.find(name) != _soundBufferMap.end())
		return;
	FILE* filePtr;
	WaveHeaderStruct waveHeaderStruct;
	IDirectSoundBuffer* tempBuffer;
	DSBUFFERDESC bufferDesc;
	WAVEFORMATEX waveFormat;
	unsigned char* wavData;
	unsigned char* bufferPtr;
	unsigned long bufferSize;

	int error = fopen_s(&filePtr, fileName, "rb");
	if (error != 0)
	{
		MessageBox(NULL, L"Can not load sound file", L"Error", MB_OK);
		return;
	}

	fread(&waveHeaderStruct, sizeof(WaveHeaderStruct), 1, filePtr);

	if ((waveHeaderStruct.format[0] != 'W') || (waveHeaderStruct.format[1] != 'A') ||
		(waveHeaderStruct.format[2] != 'V') || (waveHeaderStruct.format[3] != 'E'))
	{
		MessageBox(NULL, L"File format does not support", L"Error", MB_OK);
		return;
	}

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	waveFormat.nSamplesPerSec = waveHeaderStruct.sampleRate;
	waveFormat.wBitsPerSample = waveHeaderStruct.bitsPerSample;
	waveFormat.nChannels = waveHeaderStruct.numChannels;
	waveFormat.nBlockAlign = (waveFormat.wBitsPerSample / 8) * waveFormat.nChannels;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = 0;

	bufferDesc.dwSize = sizeof(DSBUFFERDESC);
	bufferDesc.dwFlags = DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	bufferDesc.dwBufferBytes = waveHeaderStruct.dataSize;
	bufferDesc.dwReserved = 0;
	bufferDesc.lpwfxFormat = &waveFormat;
	bufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer8* secondaryBuffer = 0;
	IDirectSoundBuffer8** pSecondaryBuffer = &secondaryBuffer;

	_device->CreateSoundBuffer(&bufferDesc, &tempBuffer, NULL);

	long result = tempBuffer->QueryInterface(IID_IDirectSoundBuffer8, (void**)&(*pSecondaryBuffer));

	tempBuffer->Release();
	tempBuffer = 0;

	if (FAILED(result))
	{
		MessageBox(NULL, L"Can not create secondaryBuffer", L"Error", MB_OK);
		return;
	}

	fseek(filePtr, sizeof(WaveHeaderStruct), SEEK_SET);

	wavData = new unsigned char[waveHeaderStruct.dataSize];

	fread(wavData, waveHeaderStruct.dataSize, 1, filePtr);

	error = fclose(filePtr);
	if (error != 0)
	{
		MessageBox(NULL, L"Can not close file", L"Error", MB_OK);
	}

	result = (*pSecondaryBuffer)->Lock(0, waveHeaderStruct.dataSize, (void**)&bufferPtr, (DWORD*)&bufferSize, NULL, 0, 0);

	if (FAILED(result))
	{
		return;
	}

	memcpy(bufferPtr, wavData, waveHeaderStruct.dataSize);

	(*pSecondaryBuffer)->Unlock((void*)bufferPtr, bufferSize, NULL, 0);

	if (wavData != NULL)
		delete wavData;
	wavData = 0;
	long tempVolume = (_volume) / 100 * (-DSBVOLUME_MIN) + DSBVOLUME_MIN;
	(*pSecondaryBuffer)->SetVolume(tempVolume);

	_soundBufferMap[name] = secondaryBuffer;
}

void Sound::Play(std::string name, bool infiniteLoop, int times)
{
	std::map< std::string, IDirectSoundBuffer8*> ::iterator it;
	it = _soundBufferMap.find(name);
	if (it == _soundBufferMap.end())
		return;
	if (infiniteLoop)
	{
		it->second->Play(0, 0, DSBPLAY_LOOPING);
	}
	else
	{
		it->second->Stop();
		it->second->SetCurrentPosition(0);
		it->second->Play(0, 0, times - 1);
	}
}

void Sound::Stop(std::string name)
{
	if (name == "")
	{
		for (std::map< std::string, IDirectSoundBuffer8*> ::iterator it = _soundBufferMap.begin(); it != _soundBufferMap.end(); it++)
		{
			it->second->Stop();
			it->second->SetCurrentPosition(0);
		}
	}
	else
	{
		std::map< std::string, IDirectSoundBuffer8*> ::iterator it;
		it = _soundBufferMap.find(name);
		if (it == _soundBufferMap.end())
			return;
		else it->second->Stop();
	}
}
