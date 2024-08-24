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
	float4 pos : SV_Position;
	float lighting : COLOR1;
};

VSOut main(float4 pos : Position, float4 norm : NORMAL)
{
	matrix mvp = mul(tf_world, tf_view_proj);
	norm = float4(mul((float3)norm, (float3x3)tf_world), 1.0f);

	VSOut vso;
	vso.pos = mul(pos, mvp);
	vso.lighting = 0.6f;
	return vso;
}
