#pragma once
#include <map>
#include <string>
#include <memory>
#include <Windows.h>
#include <functional>
#include <string_view>
#include <typeinfo>

#include <EngineBase/EngineMath.h>



// Ό³Έν :
class EngineCore
{
	friend class GameEngineTexture;
	friend class GameEngineSprite;

public:
	// constrcuter destructer
	EngineCore();
	~EngineCore();

	// delete Function
	EngineCore(const EngineCore& _Other) = delete;
	EngineCore(EngineCore&& _Other) noexcept = delete;
	EngineCore& operator=(const EngineCore& _Other) = delete;
	EngineCore& operator=(EngineCore&& _Other) noexcept = delete;

	static void Start(HINSTANCE _instance, std::function<void()> _Start, std::function<void()> _End, float4 _Pos = {0, 0}, float4 _Size = { 1280, 720 });

protected:

private:

	static void EngineStart(std::function<void()> __ContentsStart);
	static void EngineUpdate();
	static void EngineEnd(std::function<void()> __ContentsEnd);
	static void Release();

	static float UpdateTime;

};

