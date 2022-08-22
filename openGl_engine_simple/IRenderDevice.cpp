#include "IRenderDevice.h"

using namespace simple_engine;

bool IRenderDevice::Initialize()
{
	CONSOLE_PRINTF("Create Render Device\n");
	return true;
}

unsigned int IRenderDevice::CreateBuffer()
{
	CONSOLE_PRINTF("Create Buffer\n");
	return 0;
}

void IRenderDevice::DeleteBuffer(unsigned int buffer_id)
{
	CONSOLE_PRINTF("Delete Buffer\n");
}