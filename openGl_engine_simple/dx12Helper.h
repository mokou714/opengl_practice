#pragma once
#include "d3dx12.h"
#include <dxgi1_6.h>
#include <d3d12sdklayers.h>
#include <Windows.h>
#include <D3DCompiler.h>
#include <wrl/client.h>
#include <exception>
#include "DirectXHelpers.h"

namespace simple_engine
{
    //source: https://github.com/Microsoft/DirectXTK/wiki/ThrowIfFailed
    // Helper class for COM exceptions
    class com_exception : public std::exception
    {
    public:
        com_exception(HRESULT hr) : result(hr) {}

        const char* what() const override
        {
            static char s_str[64] = {};
            sprintf_s(s_str, "Failure with HRESULT of %08X",
                static_cast<unsigned int>(result));
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
            throw com_exception(hr);
        }
    }
    
}




