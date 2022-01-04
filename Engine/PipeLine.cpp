#include <cassert>
#include <d3d11.h>

#include "Pipeline.h"

#if not defined _DEBUG
#define MUST(Expression) (      (         (Expression)))
#else
#define MUST(Expression) (assert(SUCCEEDED(Expression)))
#endif

namespace Rendering::Pipeline
{
    namespace
    {
        ID3D11Device* Device;
        ID3D11DeviceContext* DeviceContext;

        IDXGISwapChain* SwapChain;

        namespace Buffer
        {
            ID3D11Buffer* Vertex;
            ID3D11Buffer* Constant[2];

            template<typename Data>
            void Update(ID3D11Buffer* const buffer, Data const& data)
            {
                D3D11_MAPPED_SUBRESOURCE Subresource = D3D11_MAPPED_SUBRESOURCE();

                MUST(DeviceContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Subresource));
                { memcpy_s(Subresource.pData, Subresource.RowPitch, data, sizeof(data)); }
                DeviceContext->Unmap(buffer, 0);
            };
        }

        ID3D11RenderTargetView* RenderTargetView;
    }

    namespace String
    {
        void Render(HFONT const hFont, LPCSTR const string, COLORREF const color, SIZE const size, POINT const center)
        {
            IDXGISurface1* Surface = nullptr;

            MUST(SwapChain->GetBuffer(0, IID_PPV_ARGS(&Surface)));
            {
                HDC hDC = HDC();

                MUST(Surface->GetDC(false, &hDC));
                {
                    if (hFont != HFONT())
                        SelectObject(hDC, hFont);

                    SetTextColor(hDC, color);

                    RECT area
                    {
                        center.x - size.cx / 2,
                        center.y - size.cy / 2,
                        center.x + size.cx / 2,
                        center.y + size.cy / 2
                    };

                    DrawText(hDC, string, ~'\0', &area, DT_TOP);
                }
                MUST(Surface->ReleaseDC(nullptr));
            }
            Surface->Release();

            DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);
        }
    }

    namespace Texture
    {
        struct Handle final
        {
            ID3D11ShaderResourceView* ShaderResourceView = nullptr;
        };

        void Create(Handle*& handle, SIZE const size, BYTE const* const data)
        {
            D3D11_TEXTURE2D_DESC const Descriptor
            {
                static_cast<UINT>(size.cx),
                static_cast<UINT>(size.cy),
                1,
                1,
                DXGI_FORMAT_B8G8R8A8_UNORM,
                1,
                0,
                D3D11_USAGE_IMMUTABLE,
                D3D11_BIND_SHADER_RESOURCE
            };

            UINT constexpr BPP = 32;

            D3D11_SUBRESOURCE_DATA const Subresource
            {
                data,
                size.cx * (BPP / 8)
            };

            ID3D11Texture2D* Texture2D = nullptr;

            MUST(Device->CreateTexture2D(&Descriptor, &Subresource, &Texture2D));
            { MUST(Device->CreateShaderResourceView(Texture2D, nullptr, &(handle = new Handle)->ShaderResourceView)); }
            Texture2D->Release();
        }

        void Render(Handle const* const& handle, RECT const area)
        {
            DeviceContext->PSSetShaderResources(0, 1, &handle->ShaderResourceView);
            {
                float const Coordinates[4][2]
                {
                    { static_cast<float>(area.left),  static_cast<float>(area.top)    },
                    { static_cast<float>(area.right), static_cast<float>(area.top)    },
                    { static_cast<float>(area.left),  static_cast<float>(area.bottom) },
                    { static_cast<float>(area.right), static_cast<float>(area.bottom) }
                };

                Buffer::Update(Buffer::Vertex, Coordinates);
            }
            DeviceContext->Draw(4, 0);
        }

        void Delete(Handle const* const& handle)
        {
            handle->ShaderResourceView->Release();

            delete handle;
        }
    }

    namespace Transform
    {
        template<Type type>
        void Update(Matrix const& Matrix)
        {
            Buffer::Update(Buffer::Constant[static_cast<UINT>(type)], Matrix);
        }

        template void Update<Type::Former>(Matrix const& Matrix);
        template void Update<Type::Latter>(Matrix const& Matrix);
    }

    void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParameter, LPARAM const lParameter)
    {
        switch (uMessage)
        {
        case WM_CREATE:
        {
            {
                DXGI_SWAP_CHAIN_DESC Descriptor = DXGI_SWAP_CHAIN_DESC();

                Descriptor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
                Descriptor.SampleDesc.Count = 1;
                Descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                Descriptor.BufferCount = 1;
                Descriptor.OutputWindow = hWindow;
                Descriptor.Windowed = true;
                Descriptor.Flags = DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE;

                MUST(D3D11CreateDeviceAndSwapChain
                (
                    nullptr,
                    D3D_DRIVER_TYPE_HARDWARE,
                    nullptr,
                    0,
                    nullptr,
                    0,
                    D3D11_SDK_VERSION,
                    &Descriptor,
                    &SwapChain,
                    &Device,
                    nullptr,
                    &DeviceContext
                ));
            }
            {
#include "Shader/ByteCode/Vertex.h"
                {
                    D3D11_INPUT_ELEMENT_DESC const Descriptor[2]
                    {
                        { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0 },
                        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1 }
                    };

                    ID3D11InputLayout* InputLayout = nullptr;

                    MUST(Device->CreateInputLayout
                    (
                        Descriptor,
                        2,
                        ByteCode,
                        sizeof(ByteCode),
                        &InputLayout
                    ));

                    DeviceContext->IASetInputLayout(InputLayout);

                    InputLayout->Release();
                }
                {
                    ID3D11VertexShader* VertexShader = nullptr;

                    MUST(Device->CreateVertexShader(ByteCode, sizeof(ByteCode), nullptr, &VertexShader));

                    DeviceContext->VSSetShader(VertexShader, nullptr, 0);

                    VertexShader->Release();
                }
            }
            {
#include "Shader/ByteCode/Pixel.h"
                {
                    ID3D11PixelShader* PixelShader = nullptr;

                    MUST(Device->CreatePixelShader(ByteCode, sizeof(ByteCode), nullptr, &PixelShader));

                    DeviceContext->PSSetShader(PixelShader, nullptr, 0);

                    PixelShader->Release();
                }
            }
            {
                DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
            }
            {
                float const Coordinates[4][2]
                {
                    { -0.5f, +0.5f },
                    { +0.5f, +0.5f },
                    { -0.5f, -0.5f },
                    { +0.5f, -0.5f }
                };

                D3D11_BUFFER_DESC const Descriptor
                {
                    sizeof(Coordinates),
                    D3D11_USAGE_IMMUTABLE,
                    D3D11_BIND_VERTEX_BUFFER,
                    0
                };

                D3D11_SUBRESOURCE_DATA const Subresource{ Coordinates };

                ID3D11Buffer* Buffer = nullptr;

                MUST(Device->CreateBuffer(&Descriptor, &Subresource, &Buffer));

                UINT const Stride = sizeof(*Coordinates);
                UINT const Offset = 0;

                DeviceContext->IASetVertexBuffers(0, 1, &Buffer, &Stride, &Offset);

                Buffer->Release();
            }
            {
                D3D11_BUFFER_DESC const Descriptor
                {
                    sizeof(float[4][2]),
                    D3D11_USAGE_DYNAMIC,
                    D3D11_BIND_VERTEX_BUFFER,
                    D3D11_CPU_ACCESS_WRITE
                };

                MUST(Device->CreateBuffer(&Descriptor, nullptr, &Buffer::Vertex));

                UINT const Stride = sizeof(float[2]);
                UINT const Offset = 0;

                DeviceContext->IASetVertexBuffers(1, 1, &Buffer::Vertex, &Stride, &Offset);
            }
            {
                D3D11_BUFFER_DESC const Descriptor
                {
                    sizeof(float[4][4]),
                    D3D11_USAGE_DYNAMIC,
                    D3D11_BIND_CONSTANT_BUFFER,
                    D3D11_CPU_ACCESS_WRITE
                };

                for (UINT u = 0; u < 2; ++u)
                    MUST(Device->CreateBuffer(&Descriptor, nullptr, &Buffer::Constant[u]));

                DeviceContext->VSSetConstantBuffers(0, 2, Buffer::Constant);
            }
            {
                D3D11_BLEND_DESC Descriptor = D3D11_BLEND_DESC();

                Descriptor.RenderTarget->BlendEnable = true;
                Descriptor.RenderTarget->SrcBlend = D3D11_BLEND_SRC_ALPHA;
                Descriptor.RenderTarget->DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
                Descriptor.RenderTarget->BlendOp = D3D11_BLEND_OP_ADD;
                Descriptor.RenderTarget->SrcBlendAlpha = D3D11_BLEND_ZERO;
                Descriptor.RenderTarget->DestBlendAlpha = D3D11_BLEND_ONE;
                Descriptor.RenderTarget->BlendOpAlpha = D3D11_BLEND_OP_ADD;
                Descriptor.RenderTarget->RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

                ID3D11BlendState* BlendState = nullptr;

                MUST(Device->CreateBlendState(&Descriptor, &BlendState));

                DeviceContext->OMSetBlendState(BlendState, nullptr, D3D11_DEFAULT_SAMPLE_MASK);

                BlendState->Release();
            }

            return;
        }
        case WM_APP:
        {
            MUST(SwapChain->Present(0, 0));

            float const Color[4]{ 0.0f, 0.0f, 0.0f, 1.0f };

            DeviceContext->ClearRenderTargetView(RenderTargetView, Color);

            return;
        }
        case WM_DESTROY:
        {
            DeviceContext->ClearState();

            RenderTargetView->Release();

            for (UINT u = 0; u < 2; ++u)
                Buffer::Constant[u]->Release();

            Buffer::Vertex->Release();

            SwapChain->Release();

            DeviceContext->Release();
            Device->Release();

            return;
        }
        case WM_SIZE:
        {
            {
                D3D11_VIEWPORT Viewport = D3D11_VIEWPORT();

                Viewport.Width = LOWORD(lParameter);
                Viewport.Height = HIWORD(lParameter);

                DeviceContext->RSSetViewports(1, &Viewport);
            }
            {
                if (RenderTargetView != nullptr)
                {
                    RenderTargetView->Release();

                    MUST(SwapChain->ResizeBuffers
                    (
                        1,
                        LOWORD(lParameter),
                        HIWORD(lParameter),
                        DXGI_FORMAT_B8G8R8A8_UNORM,
                        DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE
                    ));
                }
                {
                    ID3D11Texture2D* Texture2D = nullptr;

                    MUST(SwapChain->GetBuffer(0, IID_PPV_ARGS(&Texture2D)));
                    {
                        IDXGISurface1* Surface = nullptr;

                        MUST(Texture2D->QueryInterface(IID_PPV_ARGS(&Surface)));
                        {
                            HDC hDC = HDC();

                            MUST(Surface->GetDC(false, &hDC));
                            { SetBkMode(hDC, TRANSPARENT); }
                            MUST(Surface->ReleaseDC(nullptr));
                        }
                        Surface->Release();
                    }
                    {
                        MUST(Device->CreateRenderTargetView(Texture2D, nullptr, &RenderTargetView));

                        DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);
                    }
                    Texture2D->Release();
                }
            }

            return;
        }
        }
    }
}