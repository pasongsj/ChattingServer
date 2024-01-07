#include "PrecompiledHeader.h"
#include "EngineDevice.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineWindow.h>


ID3D11Device* EngineDevice::Device = nullptr;
ID3D11DeviceContext* EngineDevice::Context = nullptr;
IDXGISwapChain* EngineDevice::SwapChain = nullptr;
ID3D11Texture2D* EngineDevice::BackBuffer = nullptr;
ID3D11RenderTargetView* EngineDevice::MainRTV = nullptr;

EngineDevice::EngineDevice()
{
}

EngineDevice::~EngineDevice()
{
}

IDXGIAdapter* EngineDevice::GetHighPerformanceAdapter()
{
	// GDI+ DXGI <=

	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	// c++���� �����ϴ� Ŭ������ �����ϱ� ���� GUI�� ������ 
	// 
	// MIDL_INTERFACE("7b7166ec-21c7-44ae-b21a-c9ae321ae369")
	HRESULT HR = CreateDXGIFactory(__uuidof(IDXGIFactory), (void**)&Factory);

	if (nullptr == Factory)
	{
		MsgAssert("�׷���ī�忡�� ���丮 �������̽��� �������� ���߽��ϴ�.");
		return nullptr;
	}

	size_t prevAdapterVideoMemory = 0;

	for (UINT Adapterindex = 0; ; Adapterindex++)
	{
		IDXGIAdapter* CurAdapter = nullptr;

		Factory->EnumAdapters(Adapterindex, &CurAdapter);
		if (nullptr == CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc;
		CurAdapter->GetDesc(&Desc);

		if (prevAdapterVideoMemory <= Desc.DedicatedVideoMemory)
		{
			prevAdapterVideoMemory = Desc.DedicatedVideoMemory;

			if (nullptr != Adapter)
			{
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	Factory->Release();

	return Adapter;

}

void EngineDevice::CreateSwapChain()
{
	float4 ScreenSize = EngineWindow::GetScreenSize();

	DXGI_SWAP_CHAIN_DESC SwapChainDesc = { 0, };

	// �⺻����
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.BufferDesc.Width = static_cast<UINT>(ScreenSize.ix());
	SwapChainDesc.BufferDesc.Height = static_cast<UINT>(ScreenSize.iy());
	SwapChainDesc.OutputWindow = EngineWindow::GetHWnd();

	// ȭ�� ���ŷ�
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;

	// �׷����̹��� ����
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;

	// ��Ƽ����̾�� ����Ƽ 1¥���� 
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	// false�� ��üȭ��
	SwapChainDesc.Windowed = true;

	IDXGIDevice* SwapDevice = nullptr;
	IDXGIAdapter* SwapAdapter = nullptr;
	IDXGIFactory* SwapFactory = nullptr;

	Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&SwapDevice));
	if (nullptr == SwapDevice)
	{
		MsgAssert("DXGI ����̽��� DirectX����̽����� ������ ���߽��ϴ�.");
		return;
	}

	SwapDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&SwapAdapter));
	if (nullptr == SwapAdapter)
	{
		MsgAssert("DXGI ����̽��� DirectX����̽����� ������ ���߽��ϴ�.");
		return;
	}

	SwapAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&SwapFactory));

	if (S_OK != SwapFactory->CreateSwapChain(Device, &SwapChainDesc, &SwapChain))
	{
		MsgAssert("����ü�� ������ �����߽��ϴ�.");
		return;
	}

	SwapDevice->Release();
	SwapAdapter->Release();
	SwapFactory->Release();

	// ����Ÿ���� DC�� ��� ���ø� �˴ϴ�.


	HRESULT Result = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&BackBuffer));
	if (S_OK != Result)
	{
		MsgAssert("����ü�� ������ �����߽��ϴ�.");
		return;
	}

	Device->CreateRenderTargetView(BackBuffer, nullptr, &MainRTV);
	BackBuffer->Release();
	BackBuffer = nullptr;


}

void EngineDevice::RenderStart()
{
	const float4 clear_color = { 0.45f, 0.55f, 0.60f, 1.00f };
	EngineDevice::GetContext()->ClearRenderTargetView(EngineDevice::GetRTV(), clear_color.Arr1D);

	EngineDevice::GetContext()->OMSetRenderTargets(1, EngineDevice::GetRTVRef(), nullptr);
}

void EngineDevice::RenderEnd()
{
	HRESULT Result = SwapChain->Present(0, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		// ����̽� �ٽø����
		MsgAssert("����Ÿ�� ������ �����߽��ϴ�.");
		return;
	}

}



void EngineDevice::Initialize()
{

	if (nullptr == EngineWindow::GetHWnd())
	{
		MsgAssert("�����찡 ��������� �ʾҴµ� ����̽��� �ʰ�ȭ �Ҽ��� �����ϴ�.");
		return;
	}

	int iFlag = 0;

#ifdef _DEBUG
	// ���̷�Ʈx�� ����� ����� �����ϴµ�
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;

	// �� ��ʹ� �׷���ī��� ���� ����Ǵ� �������̽�
	IDXGIAdapter* Adapter = GetHighPerformanceAdapter();

	if (nullptr == Adapter)
	{
		MsgAssert("�׷���ī�� ��ġ ��� �������̽��� �����µ� �����߽��ϴ�.");
		return;
	}



	HRESULT Result = D3D11CreateDevice(
		Adapter,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		iFlag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&Device,
		&Level,
		&Context
	);

	if (S_OK != Result)
	{
		//MsgAssert("����̽� ������ �����߽��ϴ�.");
		return;
	}

	if (nullptr != Adapter)
	{
		Adapter->Release();
		Adapter = nullptr;
	}

	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		//MsgAssert("���̷�Ʈ 11�� �������� �ʴ� �׷���ī�� �Դϴ�");
		return;
	}

	// ��Ƽ������ ����ϰڴٴ� ������ �س���.
	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

	CreateSwapChain();
}

void EngineDevice::Release()
{
	if (nullptr != BackBuffer)
	{
		BackBuffer->Release();
		BackBuffer = nullptr;
	}
	//BackBufferTarget = nullptr;
	if (nullptr != MainRTV)
	{
		MainRTV->Release();
		MainRTV = nullptr;
	}
	if (nullptr != SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}

	if (nullptr != Context)
	{
		Context->Release();
		Context = nullptr;
	}

	if (nullptr != Device)
	{
		Device->Release();
		Device = nullptr;
	}
}