// APImain.cpp : �� ���Ͽ��� 'main' �Լ��� ���Ե˴ϴ�. �ű⼭ ���α׷� ������ ���۵ǰ� ����˴ϴ�.
//
#include "PrecompiledHeader.h"
#include <EngineCore/EngineCore.h>
#include <Contents/ContentsCore.h>

#pragma comment (lib, "ws2_32") // <= ������ ���� ����� ���� ���̺귯��


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