#include "PipelineStateObject.h"
#include "deviceCommon.h"

using namespace simple_engine;

PipelineStateObject PipelineStateObject::CreatePSO(PSOType type)
{	
	CONSOLE_PRINTF("Create Pipeline State Object");
	switch (type)
	{
	case simple_engine::PSOType::GENERIC:
	default:
		auto obj = std::move(PipelineStateObject());
		obj.ConsolePrint();
		return obj;
	}
}

void PipelineStateObject::ConsolePrint()
{

}
