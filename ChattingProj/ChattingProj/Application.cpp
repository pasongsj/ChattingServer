// APImain.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
#include <Windows.h>
//#include <GameEngineContents/ContentsGameCore.h>
//#include <GameEngineBase/GameEngineTime.h>
#include <EngineCore/EngineCore.h>
#include <Contents/ContentsCore.h>


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	EngineCore::Start(hInstance,
		ContentsCore::ContentsStart,
		ContentsCore::ContentsEnd,
		{ 100, 100 },
		{ 1600,900 }
	);
	return 1;
}