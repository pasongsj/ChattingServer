#include "PrecompiledHeader.h"
#include "TaskQueue.h"

#include "EngineDebug.h"
std::atomic_int TaskQueue::RunningThreadCount = 0;

TaskQueue::TaskQueue() 
{
}

TaskQueue::~TaskQueue() 
{

	IsRun = false;

	while (RunningThreadCount)
	{
		// 쓰레드 깨우는 함수
		if (
			FALSE ==
			PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(ThreadWorkType::Destroy), 0, nullptr)
			)
		{
			MsgAssert("쓰레드에게 디스트로이 명령을 내리는데 실패했습니다.");
		}

		Sleep(0);
	}
}

void TaskQueue::Initialize(std::string_view _ThreadName, int _ThreadCount)
{
	ThreadCount = _ThreadCount;

	if (0 == ThreadCount)
	{
		SYSTEM_INFO Info;
		GetSystemInfo(&Info);
		// Cpu 개수만큼 쓰레드를 만든다.
		ThreadCount = Info.dwNumberOfProcessors;
	}

	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, ThreadCount);

	if (nullptr == IOCPHandle)
	{
		MsgAssert("IOCP핸들 생성에 실패했습니다.");
	}

	RunningThreadCount = ThreadCount;
	AllThread.resize(ThreadCount);


	std::string thread_name_string = _ThreadName.data();
	for (size_t i = 0; i < ThreadCount; i++)
	{
		AllThread[i] = std::make_shared<EngineThread>();

		AllThread[i]->Start(thread_name_string + " " + std::to_string(i), std::bind(ThreadPoolFunction, this, AllThread[i].get(), IOCPHandle));
	}
}


void TaskQueue::ThreadPoolFunction(TaskQueue* _ThreadPool, EngineThread* _Thread, HANDLE _IOCPHandle)
{

	DWORD Byte;
	ULONG_PTR PtrKey;
	LPOVERLAPPED OverLapped = nullptr;

	// 일을 할 수 있는 상태라면
	while (true == _ThreadPool->IsRun)
	{
		GetQueuedCompletionStatus(_IOCPHandle, &Byte, &PtrKey, &OverLapped, INFINITE);

		ThreadWorkType WorkType = static_cast<ThreadWorkType>(Byte);
		switch (WorkType)
		{
		case UserWork:
		{
			Task* JobPtr = reinterpret_cast<Task*>(PtrKey);

			if (nullptr != JobPtr->task_function)
			{
				JobPtr->task_function();
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


void TaskQueue::Work(std::function<void()> _Work)
{
	Task* NewTask = new Task();
	NewTask->task_function = _Work;
	PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(ThreadWorkType::UserWork), reinterpret_cast<unsigned __int64>(NewTask), nullptr);

}