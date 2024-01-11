#pragma once
#include <thread>
#include <vector>
#include <functional>


enum ThreadWorkType
{
	// 서버일때는 서버에서 날아온 바이트크기가 날아오기 때문에
	// 무조건
	UserWork = -1,
	Destroy = -2
};
// 설명 : 유저레벨의 쓰레드를 사용하기 위한 클래스

// 1. 쓰레드 생성
// 2. 쓰레드에 일 할당
// 3. 일을 끝내면 join

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

