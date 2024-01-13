#include "PrecompiledHeader.h"
#include "EngineThread.h"
#include "EngineDebug.h"


std::atomic_bool EngineThread::End = false;



EngineThread::EngineThread() 
{
}

EngineThread::~EngineThread() 
{
	Join();
}

void EngineThread::Start(std::string_view _ThreadName, std::function<void()> _CallBack)
{
	CallBack = _CallBack;
	std::string thread_name = _ThreadName.data();
	Thread = std::thread(ThreadBaseFunction, this, thread_name);
}


void EngineThread::ThreadBaseFunction(EngineThread* _Thread, std::string_view _Name)
{
	std::string _multi_name = _Name.data();
	int Size = MultiByteToWideChar(CP_ACP, 0, _multi_name.c_str(), static_cast<int>(_multi_name.size()), nullptr, 0);

	if (0 == Size)
	{
		MsgAssert("문자열 변환에 실패했습니다");
		return;
	}

	std::wstring Result;
	Result.resize(Size);

	Size = MultiByteToWideChar(CP_ACP, 0, _multi_name.c_str(), static_cast<int>(_multi_name.size()), &Result[0], Size);


	SetThreadDescription(GetCurrentThread(), Result.c_str());
	_Thread->CallBack();
}




void EngineThread::Join()
{
	if (nullptr != CallBack)
	{
		Thread.join();
		CallBack = nullptr;
	}
}
