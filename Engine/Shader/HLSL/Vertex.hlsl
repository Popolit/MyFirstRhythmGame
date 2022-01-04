#include "Layout.hlsli"
	
namespace Shader
{
    namespace Resource
    {
        //�ܽ�źƮ ���� = cbuffer, B = Buffer ����, matrix = 4 * 4�� ����� Ű����
        cbuffer Transform : register(B0) { matrix Former;}           //���� ��ǥ
        cbuffer Transform : register(B1) { matrix Latter;}            //ī�޶� ����ִ� ��ǥ
    }
    
	//RS�� ������ Output
    Layout::Pixel Vertex(const Layout::Vertex Input)
    {
        Layout::Pixel Output =
        {
            Input.Position,
			Input.TexCoord
        };
		
        //mul() = 4*4 matrix�� ������ ����
        Output.Position = mul(Output.Position, Resource::Former);
        Output.Position = mul(Output.Position, Resource::Latter);
        return Output;
    }
}
