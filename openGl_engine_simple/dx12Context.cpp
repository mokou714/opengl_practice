#include "dx12Context.h"
#include "deviceCommon.h"

using namespace simple_engine;

DX12Context* DX12Context::s_dx12Context = nullptr;

DX12Context* DX12Context::Instance()
{
	if (DX12Context::s_dx12Context == nullptr) 
	{
		DX12Context::s_dx12Context = new DX12Context();
	}
	return DX12Context::s_dx12Context;
}

void DX12Context::Destory()
{
	if (DX12Context::s_dx12Context != nullptr)
	{
		delete DX12Context::s_dx12Context;
		DX12Context::s_dx12Context = nullptr;
	}
}

DX12Context::DX12Context()
	:m_swapChain(nullptr),
	m_device(nullptr),
	m_commandAllocator(nullptr),
	m_commandQueue(nullptr),
	m_rootSignature(nullptr),
	m_rtvHeap(nullptr),
	m_pipelineState(nullptr),
	m_commandList(nullptr)
{

}

void DX12Context::init()
{
	loadPipeline();
}

void DX12Context::loadPipeline()
{
	// create device 
	ComPtr<IDXGIFactory4> factory;
	ThrowIfFailed(SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(&factory))));
	ComPtr<IDXGIAdapter1> hardwareAdapter = nullptr;
	for (UINT adapterIndex = 0; ; ++adapterIndex)
	{
		IDXGIAdapter1* pAdapter = nullptr;
		if (DXGI_ERROR_NOT_FOUND == factory->EnumAdapters1(adapterIndex, &pAdapter))
		{
			// No more adapters to enumerate.
			break;
		}

		// Check to see if the adapter supports Direct3D 12, but don't create the
		// actual device yet.
		if (SUCCEEDED(D3D12CreateDevice(pAdapter, D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
		{
			hardwareAdapter = pAdapter;
		}
		pAdapter->Release();
	}

	ThrowIfFailed(SUCCEEDED(D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_device))));

	//create command queue
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	ThrowIfFailed(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_commandQueue)));

	//create swap chain
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferCount = FrameCount;
	swapChainDesc.BufferDesc.Width = SE_WINDOW_WIDTH;
	swapChainDesc.BufferDesc.Height = SE_WINDOW_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	swapChainDesc.OutputWindow = NULL; // todo Win32Application::GetHwnd();
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.Windowed = TRUE;
	ComPtr<IDXGISwapChain> swapChain;
	ThrowIfFailed(factory->CreateSwapChain(
		m_commandQueue.Get(),        // Swap chain needs the queue so that it can force a flush on it.
		&swapChainDesc,
		&swapChain
	));
	ThrowIfFailed(swapChain.As(&m_swapChain));

	// This sample does not support fullscreen transitions.
	//ThrowIfFailed(factory->MakeWindowAssociation(Win32Application::GetHwnd(), DXGI_MWA_NO_ALT_ENTER));

	m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();

	// Create descriptor heaps.
	{
		// Describe and create a render target view (RTV) descriptor heap.
		D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
		rtvHeapDesc.NumDescriptors = FrameCount;
		rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		ThrowIfFailed(m_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvHeap)));

		m_rtvDescriptorSize = m_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
	}

	// Create frame resources.
	{
		CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_rtvHeap->GetCPUDescriptorHandleForHeapStart());

		//Create a RTV for each frame.
		for (UINT n = 0; n < FrameCount; n++)
		{
			ThrowIfFailed(m_swapChain->GetBuffer(n, IID_PPV_ARGS(&m_renderTargets[n])));
			m_device->CreateRenderTargetView(m_renderTargets[n].Get(), nullptr, rtvHandle);
			rtvHandle.Offset(1, m_rtvDescriptorSize);
		}
	}

	ThrowIfFailed(m_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_commandAllocator)));
}