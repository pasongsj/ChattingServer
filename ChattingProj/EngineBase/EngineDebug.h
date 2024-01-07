#pragma once
#include <Windows.h>
#include <assert.h>
#include <string>

//#include <WS2tcpip.h> // inet_pton 함수를 사용하기 위한 헤더
//#include <WinSock2.h> // window.h보다 무조건 위쪽에 있어야 한다.
//#pragma comment (lib, "ws2_32") // <= 윈도우 서버 사용을 위한 라이브러리
// 설명 :
namespace EngineDebug
{
	void LeakCheck();
	void LeakPointBreak(int _Point);
	void GetLastErrorPrint();
	void OutPutString(const std::string& _Text);

};


#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);
#define MsgTextBox(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Text", MB_OK);