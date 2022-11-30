#include "OIT.h"

using namespace simple_engine;

void Tech_OIT::Draw(GameObject* obj)
{
	for (auto mesh : obj->getSubMeshes())
	{
		IRenderContext* context = Graphics::Instance()->FetchRenderContext();
		Material& mat = obj->getMaterial();
		//只draw深度
		PipelineStateObject& pso = mat.getPipelineState();
		mat.getPipelineState().depth_func = DepthStencilOption::FUNC_LESS;
		pso.color_mask_r = pso.color_mask_g = pso.color_mask_b = pso.color_mask_a = false;
		pso.depth_write_enable = true;
		context->SetMaterial(mat);
		context->DrawCommand(mesh);
		context->DrawIndexed(mesh.getIndices().size(), 0);

		////draw greater 深度的颜色
		//pso.color_mask_r = pso.color_mask_g = pso.color_mask_b = pso.color_mask_a = true;
		//pso.depth_func = DepthStencilOption::FUNC_GREATER;
		//pso.depth_write_enable = false;
		//context->SetMaterial(mat);
		//context->DrawCommand(mesh.getVertices(), mesh.getCoords(), mesh.getNormals(), mesh.getIndices());
		//context->DrawIndexed(mesh.getIndices().size(), 0);
		
		//draw equal 深度的颜色
		pso.color_mask_r = pso.color_mask_g = pso.color_mask_b = pso.color_mask_a = true;
		pso.depth_func = DepthStencilOption::FUNC_EQUAL;
		pso.depth_write_enable = false;
		context->SetMaterial(mat);
		context->DrawCommand(mesh);
		context->DrawIndexed(mesh.getIndices().size(), 0);
	}
}