#pragma once

namespace simple_engine
{	
	enum class CullOption 
	{
		CULL_FACE_FRONT,
		CULL_FACE_BACK,
	};
	enum class DepthStencilOption 
	{
		FUNC_LESS,
		FUNC_EQUAL,
		FUNC_GREATER,
		FUNC_NOT_EQUAL,
		FUNC_ALWAYS,
		OP_STENCIL_KEEP,
		OP_STENCIL_ZERO,
		OP_STENCIL_REPLACE,
		OP_STENCIL_INCR,
		OP_STENCIL_INCR_WRAP,
		OP_STENCIL_DECR,
		OP_STENCIL_DECR_WRAP,
		OP_STENCIL_INVERT,
	};

	enum class RaterizerOption
	{
		FILL_MODE_SOLID,
		CULL_MODE_NONE,
	};
	
	struct RasterizerStateDesc
	{
		
	};

	enum class PSOType
	{
		GENERIC
	};

	class PipelineStateObject
	{
	public:
		static PipelineStateObject CreatePSO(PSOType type);
		void ConsolePrint();
		bool depth_test_enable = true;
		bool culling_enable = true;
		bool stencil_test_enable = false;
		unsigned int stencil_ref = 1;
		unsigned int stencil_mask = 0xFF;
		DepthStencilOption depth_func = DepthStencilOption::FUNC_LESS;
		DepthStencilOption stencil_func = DepthStencilOption::FUNC_EQUAL;
		DepthStencilOption stencil_op_failed = DepthStencilOption::OP_STENCIL_KEEP;
		DepthStencilOption stencil_op_only_depth_failed = DepthStencilOption::OP_STENCIL_KEEP;
		DepthStencilOption stencil_op_passed = DepthStencilOption::OP_STENCIL_KEEP;
		CullOption culling_mode = CullOption::CULL_FACE_BACK;
		RasterizerStateDesc rasterizer_desc;
	};

}


