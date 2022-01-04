#include "Layout.hlsli"
	
namespace Shader
{
    namespace Resource
    {
        //콘스탄트 버퍼 = cbuffer, B = Buffer 형식, matrix = 4 * 4를 만드는 키워드
        cbuffer Transform : register(B0) { matrix Former;}           //월드 좌표
        cbuffer Transform : register(B1) { matrix Latter;}            //카메라가 찍어주는 좌표
    }
    
	//RS에 전달할 Output
    Layout::Pixel Vertex(const Layout::Vertex Input)
    {
        Layout::Pixel Output =
        {
            Input.Position,
			Input.TexCoord
        };
		
        //mul() = 4*4 matrix의 곱셈을 수행
        Output.Position = mul(Output.Position, Resource::Former);
        Output.Position = mul(Output.Position, Resource::Latter);
        return Output;
    }
}
