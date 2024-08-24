cbuffer CB1
{
	matrix tf_world;
};

cbuffer CB2
{
	matrix tf_view_proj;
};

struct VSOut
{
	float2 tc : TexCoord;
	float lighting : COLOR1;
	float4 pos : SV_Position;
};

VSOut main(float4 pos : Position, float4 norm : Normal, float2 tc : TexCoord)
{
	matrix mvp = mul(tf_world, tf_view_proj);
	norm = float4(mul((float3)norm, (float3x3)tf_world), 1.0f);

	VSOut vso;
	vso.pos = mul(pos, mvp);
	vso.tc = tc;
	vso.lighting = 0.6f;
	return vso;
}
