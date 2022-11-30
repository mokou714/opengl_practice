#pragma once
#include "DX12Helper.h"

namespace simple_engine
{
	namespace DX12Context
	{
		bool Initialize();
		void Destroy();

		static ComPtr<ID3D12RootSignature> m_rootSignature;
		static ComPtr<ID3D12PipelineState> m_pipelineState;
		static ComPtr<ID3D12GraphicsCommandList> m_commandList;


		static HANDLE m_fenceEvent;
		static ComPtr<ID3D12Fence> m_fence;
		static UINT64 m_fenceValue;

		static ComPtr<ID3D12Resource> m_vertexBuffer;
		static D3D12_VERTEX_BUFFER_VIEW m_vertexBufferView;
	}
	
}

