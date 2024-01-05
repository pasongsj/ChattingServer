#include "EngineWindow.h"
//#include <GameEngineBase/GameEngineThread.h>
//#include <GameEnginePlatform/GameEngineImage.h>
//#include "GameEngineInput.h"

// LRESULT(CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM)

std::function<LRESULT(HWND _hWnd, UINT _message, WPARAM _wParam, LPARAM _lParam)> EngineWindow::UserMessageFunction;
HWND EngineWindow::HWnd = nullptr;
HDC EngineWindow::WindowBackBufferHdc = nullptr;
float4 EngineWindow::WindowSize = {800, 600};
float4 EngineWindow::WindowPos = { 100, 100 };
float4 EngineWindow::ScreenSize = { 800, 600 };
//GameEngineImage* EngineWindow::BackBufferImage = nullptr;
//GameEngineImage* EngineWindow::DoubleBufferImage = nullptr;
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
        // Message�Լ��� 0�� �����ϰ� ������.
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
    // �����츦 ���� �ִ� class�� ������ ���̴�.
    // ���� �̷��̷��� �����츦 �������...

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = &EngineWindow::MessageFunction;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = _hInstance;
    // �־����� ������ ������ �⺻Icon�� �˴ϴ�.
    wcex.hIcon = nullptr;//LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_WINDOWSPROJECT1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // ��� 
    wcex.lpszMenuName = nullptr;//MAKEINTRESOURCEW(IDC_WINDOWSPROJECT1);
    wcex.lpszClassName = "EngineWindowDefault";
    wcex.hIconSm = nullptr;//LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    // �����쿡�� �̷� ������ windowŬ������ EngineWindowDefault��� �̸����� �������.
    // ���߿� ������ ���鶧 ������.
    if (0 == RegisterClassEx(&wcex))
    {
        //MsgAssert("������ Ŭ���� ��Ͽ� �����߽��ϴ�.");
        return;
    }

    // hInst = hInstance; // �ν��Ͻ� �ڵ��� ���� ������ �����մϴ�.

    // 1000�� ���α׷��� �����츦 ����޶�� ��û�ߴ�.
    // ������� �ٽ� Ư�� �����̶�� �����찡 ��������ٰ� �츮���� �˷��ִµ�.
    // Ư�� ���ڷ� �νĵǴ� �츮�� �����쿡�� ũ�⺯�� ����

    // (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX)

    HWnd = CreateWindow("EngineWindowDefault", _TitleName.data(), WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, _hInstance, nullptr);

    if (nullptr == HWnd)
    {
        //MsgAssert("������ Ŭ���� ������ �����߽��ϴ�.");
        return;
    }

    // �����찡 ��������鼭���� ������� ������ 2�����迭�� ���������� ������ ���̴�.
    WindowBackBufferHdc = GetDC(HWnd);


    ShowWindow(HWnd, SW_SHOW);
    UpdateWindow(HWnd);

    SettingWindowSize(_Size);
    SettingWindowPos(_Pos);

    // ũ�� �ٲٰ� ���´�.
    //BackBufferImage = new GameEngineImage();
    //BackBufferImage->ImageCreate(WindowBackBufferHdc);


    return;
}

void EngineWindow::DoubleBufferClear()
{
    //DoubleBufferImage->ImageClear();
}

void EngineWindow::DoubleBufferRender()
{
    //static GameEngineImage* BackBufferImage;
    //static GameEngineImage* DoubleBufferImage;
    //BackBufferImage->BitCopy(DoubleBufferImage, WindowSize.half(), WindowSize);
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

        // ����Ÿ��
        // ����Ÿ�ӿ� ������ �����ϴ°�. 
        if (nullptr != _Loop)
        {
            _Loop();
            //GameEngineInput::IsAnyKeyOff();
        }
    }

    if (nullptr != _End)
    {
        _End();
    }

    //if (nullptr != BackBufferImage)
    //{
    //    delete DoubleBufferImage;
    //    DoubleBufferImage = nullptr;

    //    delete BackBufferImage;
    //    BackBufferImage = nullptr;
    //}

    return (int)msg.wParam;
}

void EngineWindow::SettingWindowSize(float4 _Size)
{

    // �� Ÿ��Ʋ�ٿ� �����ӱ��� ����ؼ� ũ�⸦ ��������� �Ѵ�.

    //          ��ġ      ũ��
    RECT Rc = { 0, 0, _Size.ix(), _Size.iy() };

    ScreenSize = _Size;

    // ���� ���ϴ� ũ�⸦ ������ Ÿ��Ʋ�ٱ��� ����� ũ�⸦ �����ִ� �Լ�.
    AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, FALSE);

    WindowSize = { static_cast<float>(Rc.right - Rc.left), static_cast<float>(Rc.bottom - Rc.top)};
    // 0�� �־��ָ� ������ ũ�⸦ �����Ѵ�.
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);

    // ������ �Ȱ��� ũ���� �̹����Դϴ�.

    //if (nullptr != DoubleBufferImage)
    //{
    //    delete DoubleBufferImage;
    //    DoubleBufferImage = nullptr;
    //}

    //DoubleBufferImage = new GameEngineImage();
    //DoubleBufferImage->ImageCreate(ScreenSize);


}
void EngineWindow::SettingWindowPos(float4 _Pos)
{
    WindowPos = _Pos;
    SetWindowPos(HWnd, nullptr, WindowPos.ix(), WindowPos.iy(), WindowSize.ix(), WindowSize.iy(), SWP_NOZORDER);
}

//float4 EngineWindow::GetMousePosition()
//{
//    POINT MoniterPoint;
//    LPPOINT PointPtr = &MoniterPoint;
//    GetCursorPos(PointPtr);
//    ScreenToClient(HWnd, PointPtr);
//
//    return { static_cast<float>(MoniterPoint.x),static_cast<float>(MoniterPoint.y) };
//}

void EngineWindow::Release()
{
    ::UnregisterClassA(wcex.lpszClassName, wcex.hInstance);
}