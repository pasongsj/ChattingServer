#pragma once
#include <chrono>
#include "EngineDebug.h"

// Ό³Έν :
class EngineTime
{
public:
	static EngineTime GlobalTime;

	// constrcuter destructer
	EngineTime();
	~EngineTime();

	// delete Function
	EngineTime(const EngineTime& _Other) = delete;
	EngineTime(EngineTime&& _Other) noexcept = delete;
	EngineTime& operator=(const EngineTime& _Other) = delete;
	EngineTime& operator=(EngineTime&& _Other) noexcept = delete;

	void Reset();

	float TimeCheck();

	inline float GetDeltaTime()
	{
		return floatDeltaTime;
	}

	inline float GetTimeScaleDeltaTime()
	{
		return floatDeltaTime * GlobalTimeScale;
	}

	inline void SetGlobalTimeScale(float _TimeScale)
	{
		GlobalTimeScale = _TimeScale;
	}

	inline static std::string GetCurTime()
	{
		auto now = std::chrono::system_clock::now();
		std::time_t end_time = std::chrono::system_clock::to_time_t(now);
		return std::to_string(end_time);
	}
	
protected:

private:
	__int64 Tick = 0;
	LARGE_INTEGER Prev = LARGE_INTEGER();
	LARGE_INTEGER Current = LARGE_INTEGER();
	LARGE_INTEGER Second = LARGE_INTEGER();
	double DoubleDeltaTime = 0.0;
	float floatDeltaTime = 0.0;
	float GlobalTimeScale = 1.0f;

};

