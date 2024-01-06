// APImain.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
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