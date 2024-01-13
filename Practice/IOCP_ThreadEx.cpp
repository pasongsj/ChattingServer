#include <iostream>
#include <string>
#include <Windows.h>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <conio.h>
#include <functional>


void TextureLoading(std::string _Path)
{
	// aaa.png
	// bbb.png
	// ccc.png
	std::cout << _Path << std::endl;
}

void SoundLoading()
{
	std::cout << "사운드를 로딩합니다" << std::endl;
}


// 왜 iocp ?? window에서 지원해주니까!!
// 
// 
// 이건 쓰레드마다 생기는 전역 변수가 됩니다.
// 17부터 사용이 가능하다.


thread_local int Value = 0;
int ResultValue = 0;
std::atomic_int ThreadIndex = 0;
std::mutex Lock;

HANDLE IOCPHandle = 0;


class Job
{
public:
	std::function<void()> Function;
};


enum class ThreadWork
{
	Job,
	Destroy,
};


void Test() 
{
	std::wstring Text = L"IOCP_Work_Thread ";

	Text += std::to_wstring(++ThreadIndex);

	// 쓰레드이름 설정
	SetThreadDescription(GetCurrentThread(), Text.c_str());

	DWORD Byte;

	// I/O 작업이 완료된 파일 핸들과 연결된 완료 키 값을 받는 변수에 대한 포인터입니다.
	ULONG_PTR PtrKey;

	// 완료된 I/O 작업이 시작될 때 지정된 OVERLAPPED 구조체의 주소를 수신하는 변수에 대한 포인터
	LPOVERLAPPED OverLapped = nullptr;


	while (true)
	{
		// 윈도우가 강제로 이 쓰레드를 정지시켜준것.
		

		// I/O 완료 패킷을 지정된 I/O 완료 포트의 큐에서 제거하려고 시도합니다. 
		// 대기 중인 완료 패킷이 없으면 함수는 완료 포트와 연결된 보류 중인 I / O 작업이 완료될 때까지 기다립니다.
		GetQueuedCompletionStatus(IOCPHandle, &Byte, &PtrKey, &OverLapped, INFINITE);
		
		// GetQueuedCompletionStatusEx <= 이것은 좀더 상위개념으로 여러 완료 포트 항목을 동시에 검색합니다.
		// 지정된 완료 포트와 연결된 보류 중인 I/O 작업이 완료될 때까지 기다립니다.

		ThreadWork WorkType = static_cast<ThreadWork>(Byte);

		if (WorkType == ThreadWork::Destroy)
		{
			break;
		}

		// 쓰레드가 해당 일을 할 수 있도록 한다. - 일처리
		if (WorkType == ThreadWork::Job)
		{
			 Job* JobPtr = reinterpret_cast<Job*>(PtrKey);

			 if (nullptr != JobPtr->Function)
			 {
				 JobPtr->Function();
			 }

			 delete JobPtr;
		}

		// 진짜 일이 있으면 깨어나게 만드는 것이다.
		// 윈도우는 이걸 하기위해서 Iocp라고 하는 쓰레드 핸들링 인터페이스를 지원합니다.
		
		// 일이 없는거야.
		// 멈춘다 => 일이 생길때까지

	}
}


int main()
{
	// CreateIoCompletionPort는 2가지 용도로 사용되는데 윈도우에게 IOCP기능을 이용하겠다고 하고
	// IOCP핸드를 받는 용도가 첫번째.
	// 그 개수만큼의 쓰레드 관리를 하겠다고 하는것.
	// 2번째 용도는 특정 통신회전을 담당하는 핸들을 관리해달라? => 서버할때
	// 2번째 용도는 우리에게 의미가 없다.

	IOCPHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 30);

	if (nullptr == IOCPHandle)
	{
		int a = 0;
		return 1;
	}


	std::vector<std::thread> AllThread;
	for (size_t i = 0; i < 30; i++)
	{
		AllThread.push_back(std::thread(Test));
	}


	
	while (true)
	{
		// 서버로부터 패킷을 받았을 때(input을 받았을 때)
		int Select = _getch();

		Job* NewJob = new Job();

		// input이 어떤것인지 확인하고
		switch (Select)
		{
		case 'a':
		case 'A':
		{
			std::string Path = "aaaaaaaaaaaaaaaaaaaaaaa";
			NewJob->Function = std::bind(TextureLoading, Path);
			break;
		}
		case 's':
		case 'S':
			NewJob->Function = SoundLoading;
			break;
		default:
			break;
		}

		// I / O 완료 패킷을 I / O 완료 포트에 게시
		PostQueuedCompletionStatus(IOCPHandle, static_cast<DWORD>(ThreadWork::Job), reinterpret_cast<unsigned __int64>(NewJob), nullptr);

	}

	// 쓰레드 풀링 방식
	// 왜???
	// 쓰레드를 만드는것 자체가 비용이 크기 때문에
	// 필요할때마다 만드는 방법보다는
	// 미리 많이 만들어 놓고 필요할때 깨우는 방법을 선호하기 때문이다.


	for (size_t i = 0; i < AllThread.size(); i++)
	{
		AllThread[i].join();
	}
}
