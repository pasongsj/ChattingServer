#pragma once
#include <functional>
#include <Windows.h>
#include "EngineThread.h"

// ���� : ������ ����� �����ϴ� Ŭ����

enum ThreadWorkType
{
	// �����϶��� �������� ���ƿ� ����Ʈũ�Ⱑ ���ƿ��� ������
	// ������
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

	// ������� �ڵ鷯�� ����� ť�� �ִ� �۾�
	void Initialize(std::string_view _ThreadName, int _ThreadCount = 0);

	// ���� task�� ��� ť�� ����Ʈ�ϴ�
	// PostQueuedCompletionStatus ����
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

