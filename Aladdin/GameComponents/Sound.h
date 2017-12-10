#pragma once

#include "dsound.h"
#include "windows.h"
#include <map>
#include <string>
#include <iostream>
#include <mmsystem.h>
#pragma comment(lib, "dsound.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

class Sound
{
public:
	struct WaveHeaderStruct
	{
		char chunkId[4];
		unsigned long chunkSize;
		char format[4];
		char subChunkId[4];
		unsigned long subChunkSize;
		unsigned short audioFormat;
		unsigned short numChannels;
		unsigned long sampleRate;
		unsigned long bytesPerSecond;
		unsigned short blockAlign;
		unsigned short bitsPerSample;
		char dataChunkId[4];
		unsigned long dataSize;
	};

	float _volume;

	static Sound* GetInstance();
	Sound(HWND hWnd);
	~Sound();

	float GetVolume();
	void SetVolume(float percentage, std::string name = "");
	void LoadSound(char* fileName, std::string name);
	void Play(std::string name, bool infiniteLoop, int times);
	void Stop(std::string name = "");
private:
	static Sound * _instance;
	IDirectSound8* _device;
	IDirectSoundBuffer* _primaryBuffer;
	std::map<std::string, IDirectSoundBuffer8*> _soundBufferMap;
};

