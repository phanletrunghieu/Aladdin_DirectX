#pragma once

#include <Windows.h>

class Timer
{
private:
	LARGE_INTEGER _startTime, _endTime, _delta, _clockRate;
	static Timer* _instance;
public:
	Timer();
	~Timer();

	static Timer* GetInstance();

	void StartCounter();
	float GetCouter();
};