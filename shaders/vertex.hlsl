cbuffer GlobalData
{
	matrix tf_view_proj;
	float4 camera_pos;
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
	float specular : FLOAT;
};

static const float diffuse = 0.05f;

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
		vso.specular = 0;

		float3 vec_to_light = (float3)light_pos[0] - (float3)pos;
		float distance_to_light = length(vec_to_light);
		float3 light_direction = vec_to_light / distance_to_light;

		float norm_dot_light_dir = dot(norm, light_direction);
		float lighting = saturate(saturate(norm_dot_light_dir + (1 / distance_to_light)) + diffuse);
		vso.color = color * lighting;

		if (norm_dot_light_dir > 0)
		{
			float3 light_dir_projected_onto_normal = norm * norm_dot_light_dir;
			float3 reflect_dir = light_dir_projected_onto_normal + (light_dir_projected_onto_normal - light_direction);

			float3 vec_to_camera = (float3)camera_pos - (float3)pos;
			float3 camera_dir = vec_to_camera / length(vec_to_camera);

			vso.specular = min(1, max(0, dot(reflect_dir, camera_dir)) * 7 / distance_to_light);
		}
	}
	else
	{
		vso.color = color;
	}

	return vso;
}
