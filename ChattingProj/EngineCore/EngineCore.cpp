#include "PrecompiledHeader.h"
#include "EngineCore.h"

#include <EngineBase/EngineTime.h>
#include <EnginePlatform/EngineGUI.h>
#include <EnginePlatform/EngineDevice.h>



float EngineCore::UpdateTime = 0.f;
TaskQueue EngineCore::ThreadTask;



EngineCore::EngineCore() 
{
}

EngineCore::~EngineCore() 
{
}

void EngineCore::Release()
{

}

void EngineCore::EngineStart(std::function<void()> _ContentsStart)
{

	EngineDevice::Initialize();


	EngineGUI::Initialize();

	_ContentsStart();

	ThreadTask.Initialize("ThreadTaskQueue");

}

void EngineCore::EngineUpdate() 
{


	float TimeDeltaTime = EngineTime::GlobalTime.TimeCheck();

	if (TimeDeltaTime<=0.f) // PhysX는 Simulate시 시간이 0 이면 오류를 뿜어서 리턴
	{
		return;
	}


#ifdef _DEBUG

	if (TimeDeltaTime > 1 / 30.0f)
	{
		TimeDeltaTime = 1 / 30.0f;
	}
#endif // _DEBUG

	UpdateTime += TimeDeltaTime;


	TimeDeltaTime = UpdateTime;
	UpdateTime = 0.f;

	static bool GUIRender = true;



	EngineDevice::RenderStart();
	if (true == GUIRender)
	{
		EngineGUI::Render(TimeDeltaTime);
	}
	EngineDevice::RenderEnd();
}

void EngineCore::EngineEnd(std::function<void()> _ContentsEnd)
{
	if (nullptr == _ContentsEnd)
	{
		MsgAssert("끝 컨텐츠가 존재하지 않습니다.");
	}

	_ContentsEnd();
	EngineThread::ThreadEnd();

	EngineGUI::Release();
	Release();
	

	EngineDevice::Release();
	EngineWindow::Release();

}

void EngineCore::Start(HINSTANCE _instance,  std::function<void()> _Start, std::function<void()> _End, float4 _Pos, float4 _Size)
{
	EngineDebug::LeakCheck();

	EngineWindow::WindowCreate(_instance, "Chatting", _Size, _Pos);
	EngineWindow::WindowLoop(std::bind(EngineCore::EngineStart, _Start), EngineCore::EngineUpdate, std::bind(EngineCore::EngineEnd, _End));
}
