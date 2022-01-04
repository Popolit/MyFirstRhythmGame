#include "Layout.hlsli"

namespace Shader
{
    //T0 = PSSetShaderResource���� ������ 0��° �ؽ��ĸ� �������ڴ�
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