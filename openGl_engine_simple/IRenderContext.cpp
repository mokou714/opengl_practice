#include "IRenderContext.h"

using namespace simple_engine;

bool IRenderContext::Initialize()
{
	CONSOLE_PRINTF("Initialize Render Context\n");
	return true;
}

void IRenderContext::SetPipelineState(const PipelineStateObject& pso)
{
	CONSOLE_PRINTF("Set Pipeline State Object\n");
}

void IRenderContext::ResetPipelineState()
{
	CONSOLE_PRINTF("Reset Pipeline State\n");
}

void IRenderContext::SetVertexBuffer(const VertexBuffer& buf)
{
	CONSOLE_PRINTF("Set Vertex Buffer\n");
}
void IRenderContext::SetElementBuffer(const ElementBuffer& buf)
{
	CONSOLE_PRINTF("Set Element Buffer\n");
}

void IRenderContext::SetMaterial(Material& mat)
{
	CONSOLE_PRINTF("Set Material\n");
}

void IRenderContext::Draw(unsigned int vertex_count, unsigned int offset)
{
	CONSOLE_PRINTF("Draw, vertex count:%d, offset:%d\n", vertex_count, offset);
}
void IRenderContext::DrawIndexed(unsigned int element_count, unsigned int offset)
{
	CONSOLE_PRINTF("DrawIndexed, element count:%d, offset:%d\n", element_count, offset);
}
void IRenderContext::DrawInstanced(unsigned int vertex_per_instance, unsigned int instance_count,
	unsigned int vertex_start_offset, unsigned int instance_start_offset)
{

}
void IRenderContext::DrawIndexedInstanced(unsigned int indices_per_instance, unsigned int instance_count,
	unsigned int index_start_offset, unsigned int instance_start_offset)
{

}