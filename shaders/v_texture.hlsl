cbuffer CB1
{
	matrix tf_model;
};

cbuffer CB2
{
	matrix tf_view_proj;
};

struct VSOut
{
	float2 tc : TexCoord;
	float4 pos : SV_Position;
};

VSOut main(float4 pos : Position, float2 tc : TexCoord)
{
	matrix mvp = mul(tf_model, tf_view_proj);

	VSOut output;
	output.pos = mul(pos, mvp);
	output.tc = tc;
	return output;
}
