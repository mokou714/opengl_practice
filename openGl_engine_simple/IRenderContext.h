#pragma once
#include "deviceCommon.h"
#include "GpuBuffer.h"
#include "PipelineStateObject.h"

#include "material.h" //todo

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

		virtual void Present()=0; //todo
		virtual void ResetPipelineState() = 0; //todo
		virtual void SetMaterial(Material& mat) = 0; //todo
		virtual void DrawCommand(const std::vector<glm::vec3>& vertices, const std::vector<glm::vec2>& coords,
			const std::vector<glm::vec3>& normals, const std::vector<unsigned short>& indices) = 0; //todo

		virtual void setCursorPos(double xpos, double ypos) = 0;
		virtual void getCursorPos(double& xpos, double& ypos) = 0;
		virtual CommonKeyState getKeyState(CommonKeyCode key) = 0;
	protected:
		bool is_initialized;
	};
}


