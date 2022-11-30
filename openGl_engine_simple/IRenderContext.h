#pragma once
#include "deviceCommon.h"
#include "GpuBuffer.h"
#include "PipelineStateObject.h"
#include "glFrameBufferObject.h"
#include "material.h" //todo
#include "mesh.h"

/* handle command list and apply pipeline state changes */

namespace simple_engine
{
	class IRenderContext
	{
	public:
		virtual void Destroy() = 0;
		virtual bool Initialize();
		virtual void Draw(unsigned int vertex_count, unsigned int offset);
		virtual void DrawIndexed(unsigned int element_count, unsigned int offset);
		virtual void DrawInstanced(unsigned int vertex_per_instance, unsigned int instance_count,
			unsigned int vertex_start_offset, unsigned int instance_start_offset);
		virtual void DrawIndexedInstanced(unsigned int indices_per_instance, unsigned int instance_count,
			unsigned int index_start_offset, unsigned int instance_start_offset);
		virtual void SetPipelineState(const PipelineStateObject& pso);
		virtual void SetVertexBuffer(const VertexBuffer& buf);
		virtual void SetElementBuffer(const ElementBuffer& buf);
		virtual void SetFrameBufferObject(GLFrameBufferObject& fbo) = 0;	//todo
		virtual void ResetFrameBufferObject() = 0;
		virtual void ClearFrameBufferObject(GLFrameBufferObject& fbo) = 0;	//todo
		virtual void BlitFrameBuffer(GLFrameBufferObject* fbo1, GLFrameBufferObject* fbo2) = 0;

		virtual void Present()=0; //todo
		virtual void ResetPipelineState() = 0; //todo
		virtual void SetMaterial(Material& mat) = 0; //todo
		virtual void DrawCommand(Mesh& mesh) = 0; //todo

		virtual void setCursorPos(double xpos, double ypos) = 0;
		virtual void getCursorPos(double& xpos, double& ypos) = 0;
		virtual CommonKeyState getKeyState(CommonKeyCode key) = 0;
	protected:
		bool is_initialized;
	};
}


