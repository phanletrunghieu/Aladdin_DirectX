#include "Timer.h"

Timer* Timer::_instance = NULL;

Timer::Timer()
{
}


Timer::~Timer()
{
}

Timer * Timer::GetInstance()
{
	if (!_instance)
		_instance = new Timer();

	return _instance;
}

void Timer::StartCounter()
{
	if (!QueryPerformanceFrequency(&_clockRate))
	{
		return;
	}

	QueryPerformanceCounter(&_startTime);
}

float Timer::GetCouter()
{
	QueryPerformanceCounter(&_endTime);
	_delta.QuadPart = _endTime.QuadPart - _startTime.QuadPart;

	return ((float)_delta.QuadPart / _clockRate.QuadPart);
}
