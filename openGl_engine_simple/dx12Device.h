#pragma once
#include "deviceCommon.h"
#include "dx12Helper.h"

namespace simple_engine
{
	namespace DX12Device
	{
		bool Initialize();
		void Destroy();

		static const UINT FrameCount = 2;

		// Pipeline objects.
		static D3D12_VIEWPORT m_viewport;
		static D3D12_RECT m_scissorRect;
		static ComPtr<IDXGISwapChain3> m_swapChain;
		static ComPtr<ID3D12Device> m_device;
		static ComPtr<ID3D12Resource> m_renderTargets[FrameCount];
		static ComPtr<ID3D12CommandAllocator> m_commandAllocator;
		static ComPtr<ID3D12CommandQueue> m_commandQueue;

		static ComPtr<ID3D12DescriptorHeap> m_rtvHeap;
		
		static UINT m_rtvDescriptorSize;

		// Synchronization objects.
		static UINT m_frameIndex;
	}
}


