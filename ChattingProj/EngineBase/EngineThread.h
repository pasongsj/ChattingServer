#pragma once
#include <thread>
#include <vector>
#include <functional>

// 설명 : 하나의 쓰레드를 가지는 클래스

// 1. 쓰레드 생성
// 2. 쓰레드에 일 할당
// 3. 일을 끝내면 join

class EngineThread :public std::enable_shared_from_this<EngineThread>
{
public:
	//static void Initialize(/*const std::string& _ThreadName, */int _ThreadCount = 0);
	//static void Release();

	// constrcuter destructer
	EngineThread();
	EngineThread(std::string_view _ThreadName, std::function<void()> _CallBack)
	{
		Start(_ThreadName, _CallBack);
	}
	~EngineThread();

	// delete Function
	EngineThread(const EngineThread& _Other) = delete;
	EngineThread(EngineThread&& _Other) noexcept = delete;
	EngineThread& operator=(const EngineThread& _Other) = delete;
	EngineThread& operator=(EngineThread&& _Other) noexcept = delete;


	// 쓰레드가 사용될 때 실행되는 함수로 CallBack이 실행된다
	void Start(std::string_view _ThreadName, std::function<void()> _CallBack);

	// 종료 작업이다
	void Join();

	static void ThreadEnd()
	{
		End = true;
	}

	static bool IsThreadEnd()
	{
		return End;
	}


protected:

private:

	static std::atomic_bool End;
	
	// 큐에서 pop된 사용가능한 쓰레드로 task를 실행하는 역할을 한다.
	static void ThreadBaseFunction(EngineThread* _Thread, std::string_view _Name);

	std::thread Thread;
	// call back함수를 통해
	std::function<void()> CallBack;

};

