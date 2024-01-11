#include "PrecompiledHeader.h"
#include "EngineThread.h"
#include "EngineDebug.h"

std::atomic_bool EngineThread::End;
std::vector<EngineThread*> EngineThread::AllThread;
int EngineThread::ThreadCount;
std::atomic_int EngineThread::RunningThreadCount;

HANDLE IOCPHandle;


EngineThread::EngineThread() 
{
}

EngineThread::~EngineThread() 
{
}
void EngineThread::Initialize(/*const std::string& _ThreadName, */int _ThreadCount)
{
	RunningThreadCount = ThreadCount = _ThreadCount;
	if (0 == ThreadCount)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);
		// Cpu 개수
		RunningThreadCount = ThreadCount = Info.dwNumberOfProcessors;
	}

	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, ThreadCount);
	if (nullptr == IOCPHandle)
	{
		MsgAssert("IOCP핸들 생성에 실패했습니다.");
	}

	AllThread.resize(ThreadCount);

	for (size_t i = 0; i < ThreadCount; i++)
	{
		AllThread[i] = new EngineThread();
		AllThread[i]->Start(std::bind(ThreadPoolFunction, AllThread[i], IOCPHandle));
	}
}

void EngineThread::Release()
{
	for (int i = 0; i < ThreadCount; ++i)
	{
		AllThread[i]->Join();
		delete AllThread[i];
	}
}


void EngineThread::ThreadPoolFunction(EngineThread* _Thread, HANDLE _IOCPHandle)
{
	DWORD Byte;
	ULONG_PTR PtrKey;
	LPOVERLAPPED OverLapped = nullptr;

	while (true == _Thread->IsRun)
	{
		GetQueuedCompletionStatus(_IOCPHandle, &Byte, &PtrKey, &OverLapped, INFINITE);

		ThreadWorkType WorkType = static_cast<ThreadWorkType>(Byte);
		switch (WorkType)
		{
		case UserWork:
		{
			Job* JobPtr = reinterpret_cast<Job*>(PtrKey);

			if (nullptr != JobPtr->Function)
			{
				JobPtr->Function();
			}
			delete JobPtr;
			break;
		}
		case Destroy:
			--RunningThreadCount;
			return;
		default:
			break;
		}
	}
}


void EngineThread::Work(std::function<void()> _Work)
{
	Job* NewJob = new Job();
	NewJob->Function = _Work;
	PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(ThreadWorkType::UserWork), reinterpret_cast<unsigned __int64>(NewJob), nullptr);

}



void EngineThread::Start(/*std::string _ThreadName, */std::function<void()> _CallBack)
{
	CallBack = _CallBack;

	Thread = std::thread(CallBack);

	//SetThreadDescription(GetCurrentThread());

	//Thread = std::thread(ThreadBaseFunction, this, _ThreadName);
}


void EngineThread::Join()
{
	if (nullptr != CallBack)
	{
		Thread.join();
		CallBack = nullptr;
	}
}
