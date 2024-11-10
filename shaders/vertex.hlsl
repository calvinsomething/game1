cbuffer CB1
{
	matrix tf_world;
	float4 color;
};

cbuffer CB2
{
	matrix tf_view_proj;
};

struct VSOut
{
	float4 pos : SV_Position;
	float4 color : COLOR;
};

static const float3 light_pos = {0.0f, 0.0f, 0.0f};
static const float diffuse = 0.2f;

VSOut main(float3 pos_in : Position, float3 norm : Normal)
{
	float4 pos = float4(pos_in, 1);
	pos.w = 1;
	pos = mul(pos, tf_world);

	norm = mul(norm, (float3x3)tf_world);

	float3 vec_to_light = light_pos - (float3)pos;
	float distance_to_light = length(vec_to_light);
	float3 light_direction = vec_to_light / distance_to_light;

	VSOut vso;
	vso.pos = mul(pos, tf_view_proj);

	float lighting = saturate(saturate(dot(norm, light_direction) + (1 / distance_to_light)) + diffuse);
	vso.color = color * lighting;

	return vso;
}
