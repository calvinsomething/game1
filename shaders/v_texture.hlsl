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

static const float3 light_pos = {0.0f, 0.0f, 0.0f};
static const float diffuse = 0.2f;

VSOut main(float4 pos : Position, float3 norm : Normal, float2 tc : TexCoord)
{
	pos = mul(pos, tf_world);

	norm = mul(norm, (float3x3)tf_world);

	float3 vec_to_light = light_pos - (float3)pos;
	float distance_to_light = length(vec_to_light);
	float3 light_direction = vec_to_light / distance_to_light;

	VSOut vso;
	vso.pos = mul(pos, tf_view_proj);
	vso.tc = tc;

	vso.lighting = saturate(dot(norm, light_direction) + 2/max(distance_to_light, 0.01f) + diffuse);

	return vso;
}
