#pragma once
#include <string>
#include <Windows.h>
#include <EngineBase/EngineMath.h>
#include <string_view>
#include <functional>


// 설명 :
class EngineWindow
{
	static LRESULT CALLBACK MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam);

	static std::function<LRESULT(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)> UserMessageFunction;

public:
	inline static void SetUserMessageFunction(std::function<LRESULT(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)> _UserMessageFunction)
	{
		UserMessageFunction = _UserMessageFunction;
	}

	static void WindowCreate(HINSTANCE _hInstance, std::string_view _TitleName, float4 _Size, float4 _Pos);

	static void SettingWindowSize(float4 _Size);
	static void SettingWindowPos(float4 _Pos);

	inline static float4 GetScreenSize()
	{
		return ScreenSize;
	}

	inline static HWND GetHWnd()
	{
		return HWnd;
	}

	inline static HDC GetWindowBackBufferHdc()
	{
		return WindowBackBufferHdc;
	}

	inline static void AppOff()
	{
		IsWindowUpdate = false;
	}

	static int WindowLoop(
		std::function<void()> _Start, 
		std::function<void()> _Loop, 
		std::function<void()> _End
	);

	static void Release();

	EngineWindow();
	~EngineWindow();

	// delete Function
	EngineWindow(const EngineWindow& _Other) = delete;
	EngineWindow(EngineWindow&& _Other) noexcept = delete;
	EngineWindow& operator=(const EngineWindow& _Other) = delete;
	EngineWindow& operator=(EngineWindow&& _Other) noexcept = delete;

	

protected:

private:
	static float4 WindowSize;
	static float4 ScreenSize;
	static float4 WindowPos;
	static HWND HWnd;
	static HDC WindowBackBufferHdc; // 윈도우에 그림을 그릴수 있는 권한.
	static bool IsWindowUpdate;
	static WNDCLASSEX wcex;
};

