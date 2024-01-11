#pragma once
#include <thread>
#include <vector>
#include <functional>


enum ThreadWorkType
{
	// �����϶��� �������� ���ƿ� ����Ʈũ�Ⱑ ���ƿ��� ������
	// ������
	UserWork = -1,
	Destroy = -2
};
// ���� : ���������� �����带 ����ϱ� ���� Ŭ����

// 1. ������ ����
// 2. �����忡 �� �Ҵ�
// 3. ���� ������ join

class EngineThread 
{
	class Job
	{
	public:
		std::function<void()> Function;
	};
public:
	static void Initialize(/*const std::string& _ThreadName, */int _ThreadCount = 0);
	static void Release();

	// constrcuter destructer
	EngineThread();
	~EngineThread();

	// delete Function
	EngineThread(const EngineThread& _Other) = delete;
	EngineThread(EngineThread&& _Other) noexcept = delete;
	EngineThread& operator=(const EngineThread& _Other) = delete;
	EngineThread& operator=(EngineThread&& _Other) noexcept = delete;

	void Work(std::function<void()> _Work);

	void Start(/*std::string _ThreadName, */std::function<void()> _CallBack);

	void Join();


protected:

private:

	static std::atomic_bool End;
	static std::vector<EngineThread *> AllThread;
	static int ThreadCount;
	static std::atomic_int RunningThreadCount;

	static HANDLE IOCPHandle;

	static void ThreadPoolFunction(EngineThread* _Thread, HANDLE _IOCPHandle);

	std::atomic_bool IsRun = true;
	std::thread Thread;
	std::function<void()> CallBack;

};

