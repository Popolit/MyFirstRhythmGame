namespace Layout
{
	struct Vertex
	{
		float4 Position : POSITION;
        float2 TexCoord : TEXCOORD;
    };
	
	struct Pixel
	{
		float4 Position : SV_POSITION;		//System Value -> 반드시 처리할 중요한 값임을 의미함, 여기서 설정 시 아래 COLOR도 같이 들어감
		float2 TexCoord : TEXCOORD;
	};
	
    typedef float4 Color;
}