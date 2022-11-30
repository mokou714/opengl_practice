#pragma once
#include "d3dx12.h"
#include <dxgi1_6.h>
#include <d3d12sdklayers.h>
#include <wrl/client.h>
#include <d3dcompiler.h>

#define DEBUG_PRINTF(...) {char cad[512]; sprintf_s(cad, __VA_ARGS__);  OutputDebugStringA(cad);}
#define CONSOLE_PRINTF(...) printf(__VA_ARGS__);

using Microsoft::WRL::ComPtr;

//source: https://github.com/Microsoft/DirectXTK/wiki/ThrowIfFailed
// Helper class for COM exceptions
class com_exception : public std::exception
{
public:
    com_exception(HRESULT hr) : result(hr) {}

    const char* what() const override
    {
        static char s_str[64] = {};
        DEBUG_PRINTF("Failure with HRESULT of %08X\n", static_cast<unsigned int>(result));
        //sprintf_s(s_str, "Failure with HRESULT of %08X", static_cast<unsigned int>(result));
        return s_str;
    }

private:
    HRESULT result;
};

// Helper utility converts D3D API failures into exceptions.
inline void ThrowIfFailed(HRESULT hr)
{
    if (FAILED(hr))
    {
        auto exception = com_exception(hr);
        exception.what();
        throw exception;
    }
}
