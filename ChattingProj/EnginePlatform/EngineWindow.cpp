#include "PrecompiledHeader.h"
#include "EngineWindow.h"


std::function<LRESULT(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)> EngineWindow::UserMessageFunction;
HWND EngineWindow::HWnd = nullptr;
HDC EngineWindow::WindowBackBufferHdc = nullptr;
float4 EngineWindow::WindowSize = {800, 600};
float4 EngineWindow::WindowPos = { 100, 100 };
float4 EngineWindow::ScreenSize = { 800, 600 };
bool EngineWindow::IsWindowUpdate = true;
WNDCLASSEX EngineWindow::wcex;


LRESULT CALLBACK EngineWindow::MessageFunction(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)
{
    if (nullptr != UserMessageFunction)
    {
        if (0 != UserMessageFunction(_hWnd, _message, _wParam, _lParam))
        {
            return true;
        }
    }

    switch (_message)
    {
    case WM_SETFOCUS:
    {
        //GameEngineInput::IsFocusOn();
        break;
    }
    case WM_KILLFOCUS:
    {
        //GameEngineInput::IsFocusOff();
        break;
    }
    case WM_KEYDOWN:
    {
        //GameEngineInput::IsAnyKeyOn();
        break;
    }
    case WM_DESTROY:
    {
        //GameEngineThread::ThreadEnd();
        // Message함수가 0을 리턴하게 만들어라.
        // PostQuitMessage(0);
        IsWindowUpdate = false;
        break;
    }
    default:
        return DefWindowProc(_hWnd, _message, _wParam, _lParam);
    }

    return 0;
}

EngineWindow::EngineWindow() 
{
}

EngineWindow::~EngineWindow() 
{
}

void EngineWindow::WindowCreate(HINSTANCE _hInstance, std::string_view _TitleName, float4 _Size, float4 _Pos)
{
    // 윈도우를 찍어낼수 있는 class를 만들어내는 것이다.
    // 나는 이러이러한 윈도우를 만들어줘...

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &EngineWindow::MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    wcex.hIcon = nullptr;//LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // 흰색 
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = "EngineWindowDefault";
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // 윈도우에게 이런 내용을 window클래스를 EngineWindowDefault라는 이름으로 등록.
    if (0 == RegisterClassEx(&wcex))
    {
        MsgAssert("윈도우 클래스 등록에 실패했습니다.");
        return;
    }

    // hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

    HWnd = CreateWindow("EngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (nullptr == HWnd)
    {
        MsgAssert("윈도우 클래스 생성에 실패했습니다.");
        return;
    }

    // 윈도우가 만들어지면서부터 만들어진 색깔의 2차원배열의 수정권한을 얻어오는 것이다.
    WindowBackBufferHdc = GetDC(HWnd);


    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    return;
}


int EngineWindow::WindowLoop(
    std::function<void()> _Start,
    std::function<void()> _Loop,
    std::function<void()> _End
)
{
    if (nullptr != _Start)
    {
        _Start();
    }

    MSG msg = {};

    while (IsWindowUpdate)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {

            //if (nullptr != _Loop)
            //{
            //    _Loop();
            //    //GameEngineInput::IsAnyKeyOff();
            //}

            TranslateMessage(&msg);
            DispatchMessage(&msg);
            continue;
        } 

        // 데드타임
        // 데드타임에 게임을 실행하는것. 
        if (nullptr != _Loop)
        {
            _Loop();
        }
    }

    if (nullptr != _End)
    {
        _End();
    }

    return (int)msg.wParam;
}

void EngineWindow::SettingWindowSize(float4 _Size)
{

    // 그 타이틀바와 프레임까지 고려해서 크기를 설정해줘야 한다.

    //          위치      크기
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    ScreenSize = _Size;

    // 내가 원하는 크기를 넣으면 타이틀바까지 고려한 크기를 리턴주는 함수.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top)};
    // 0을 넣어주면 기존의 크기를 유지한다.
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);



}

void EngineWindow::SettingWindowPos(float4 _Pos)
{
    WindowPos = _Pos;
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}

void EngineWindow::Release()
{
    ::DestroyWindow(HWnd);
    ::UnregisterClassA(wcex.lpszClassName, wcex.hInstance);
}