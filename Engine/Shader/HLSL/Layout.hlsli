namespace Layout
{
	struct Vertex
	{
		float4 Position : POSITION;
        float2 TexCoord : TEXCOORD;
    };
	
	struct Pixel
	{
		float4 Position : SV_POSITION;		//System Value -> �ݵ�� ó���� �߿��� ������ �ǹ���, ���⼭ ���� �� �Ʒ� COLOR�� ���� ��
		float2 TexCoord : TEXCOORD;
	};
	
    typedef float4 Color;
}