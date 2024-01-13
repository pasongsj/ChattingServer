#pragma once
#include <functional>
#include <Windows.h>
#include "EngineThread.h"

// 설명 : 쓰레드 사용을 관리하는 클래스

enum ThreadWorkType
{
	// 서버일때는 서버에서 날아온 바이트크기가 날아오기 때문에
	// 무조건
	UserWork = -1,
	Destroy = -2
};


class TaskQueue
{
private:
	class Task
	{
	public:
		std::function<void()> task_function;
	};
public:
	// constrcuter destructer
	TaskQueue();
	~TaskQueue();

	// delete Function
	TaskQueue(const TaskQueue& _Other) = delete;
	TaskQueue(TaskQueue&& _Other) noexcept = delete;
	TaskQueue& operator=(const TaskQueue& _Other) = delete;
	TaskQueue& operator=(TaskQueue&& _Other) noexcept = delete;

	// 쓰레드와 핸들러를 만들고 큐에 넣는 작업
	void Initialize(std::string_view _ThreadName, int _ThreadCount = 0);

	// 할일 task를 담아 큐에 포스트하는
	// PostQueuedCompletionStatus 과정
	void Work(std::function<void()> _Work);


protected:

private:
	HANDLE IOCPHandle = nullptr;
	int ThreadCount;

	static std::atomic_int RunningThreadCount;
	std::atomic_bool IsRun = true;
	std::vector<std::shared_ptr<EngineThread>> AllThread;

	static void ThreadPoolFunction(TaskQueue* _ThreadPool, EngineThread* _Thread, HANDLE _IOCPHandle);
};

