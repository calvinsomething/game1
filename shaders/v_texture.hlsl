cbuffer CBuffer
{
	matrix transform;
};

struct VSOut
{
	float2 tc : TexCoord;
	float4 pos : SV_Position;
};

VSOut main(float4 pos : Position, float2 tc : TexCoord)
{
	VSOut output;
	output.pos = mul(pos, transform);
	output.tc = tc;
	return output;
}
