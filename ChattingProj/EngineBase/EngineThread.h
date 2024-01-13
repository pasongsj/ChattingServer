#pragma once
#include <thread>
#include <vector>
#include <functional>

// ���� : �ϳ��� �����带 ������ Ŭ����

// 1. ������ ����
// 2. �����忡 �� �Ҵ�
// 3. ���� ������ join

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


	// �����尡 ���� �� ����Ǵ� �Լ��� CallBack�� ����ȴ�
	void Start(std::string_view _ThreadName, std::function<void()> _CallBack);

	// ���� �۾��̴�
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
	
	// ť���� pop�� ��밡���� ������� task�� �����ϴ� ������ �Ѵ�.
	static void ThreadBaseFunction(EngineThread* _Thread, std::string_view _Name);

	std::thread Thread;
	// call back�Լ��� ����
	std::function<void()> CallBack;

};

