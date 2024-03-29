// APImain.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include "PrecompiledHeader.h"
#include <EngineCore/EngineCore.h>
#include <Contents/ContentsCore.h>

#pragma comment (lib, "ws2_32") // <= 윈도우 서버 사용을 위한 라이브러리


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	EngineCore::Start(hInstance,
		ContentsCore::ContentsStart,
		ContentsCore::ContentsEnd,
		{ 100, 100 },
		{ 600,900 }
	);
	return 1;
}