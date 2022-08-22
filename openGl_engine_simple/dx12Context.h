#pragma once
#include "dx12Helper.h"
#include <vector>

using namespace Microsoft::WRL;

namespace simple_engine
{
	class DX12Context
	{
	public:
		static DX12Context* Instance();
		DX12Context();
		void init();
		void Destory();
	private:
		static DX12Context* s_dx12Context;
		void loadPipeline();

		static const UINT FrameCount = 2;

		// Pipeline objects.
		D3D12_VIEWPORT m_viewport;
		D3D12_RECT m_scissorRect;
		ComPtr<IDXGISwapChain3> m_swapChain;
		ComPtr<ID3D12Device> m_device;
		std::vector<ComPtr<ID3D12Resource>> m_renderTargets;
		ComPtr<ID3D12CommandAllocator> m_commandAllocator;
		ComPtr<ID3D12CommandQueue> m_commandQueue;
		ComPtr<ID3D12RootSignature> m_rootSignature;
		ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
		ComPtr<ID3D12PipelineState> m_pipelineState;
		ComPtr<ID3D12GraphicsCommandList> m_commandList;
		UINT m_rtvDescriptorSize;

		// App resources.
		ComPtr<ID3D12Resource> m_vertexBuffer;
		D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;

		// Synchronization objects.
		UINT m_frameIndex;
		HANDLE m_fenceEvent;
		ComPtr<ID3D12Fence> m_fence;
		UINT64 m_fenceValue;
	};
}


