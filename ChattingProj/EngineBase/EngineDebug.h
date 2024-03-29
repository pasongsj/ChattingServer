#pragma once
#include <Windows.h>
#include <assert.h>
#include <string>

// 설명 : 디버깅, 릭체크, warning메세지를 위한 클래스
namespace EngineDebug
{
	void LeakCheck();
	void LeakPointBreak(int _Point);
	void GetLastErrorPrint();
	void OutPutString(const std::string& _Text);

};


#define MsgAssert(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Error", MB_OK); assert(false);
#define MsgTextBox(MsgText) std::string ErrorText = MsgText; MessageBoxA(nullptr, ErrorText.c_str(), "Text", MB_OK);