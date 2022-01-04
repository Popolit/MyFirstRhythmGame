#include "Layout.hlsli"

namespace Shader
{
    //T0 = PSSetShaderResource에서 설정한 0번째 텍스쳐를 가져오겠다
    const Texture2D Resource : register(T0);
    
    Layout::Color Pixel(const Layout::Pixel input) : SV_Target
    {
        Layout::Color Output =
        {
            Resource.Load(int3(input.TexCoord.x, input.TexCoord.y, 0))
        };
        
        
        return Output;
    }

}