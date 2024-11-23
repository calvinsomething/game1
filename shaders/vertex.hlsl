cbuffer GlobalData
{
	matrix tf_view_proj;
	uint light_count;
	float4 light_pos[4];
};

cbuffer ComponentData
{
	matrix tf_world;
	float4 color;
	bool do_lighting;
};

struct VSOut
{
	float4 pos : SV_Position;
	float4 color : COLOR;
};

static const float diffuse = 0.2f;

VSOut main(float3 pos_in : Position, float3 norm : Normal)
{
	float4 pos = float4(pos_in, 1);
	pos.w = 1;
	pos = mul(pos, tf_world);

	norm = mul(norm, (float3x3)tf_world);

	VSOut vso;
	vso.pos = mul(pos, tf_view_proj);

	if (do_lighting)
	{
		float3 vec_to_light = (float3)light_pos[0] - (float3)pos;
		float distance_to_light = length(vec_to_light);
		float3 light_direction = vec_to_light / distance_to_light;

		float lighting = saturate(saturate(dot(norm, light_direction) + (1 / distance_to_light)) + diffuse);
		vso.color = color * lighting;
	}
	else
	{
		vso.color = color;
	}

	return vso;
}
