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
};

struct VSOut
{
	float2 tc : TexCoord;
	float lighting : COLOR1;
	float4 pos : SV_Position;
	float specular : FLOAT;
};

static const float diffuse = 0.05f;

VSOut main(float4 pos : Position, float3 norm : Normal, float2 tc : TexCoord)
{
	pos = mul(pos, tf_world);

	norm = mul(norm, (float3x3)tf_world);

	float3 vec_to_light = (float3)light_pos[0] - (float3)pos;
	float distance_to_light = length(vec_to_light);
	float3 light_direction = vec_to_light / distance_to_light;

	VSOut vso;
	vso.pos = mul(pos, tf_view_proj);
	vso.tc = tc;
	vso.specular = 0;

	float norm_dot_light_dir = dot(norm, light_direction);
	vso.lighting = saturate(saturate(norm_dot_light_dir + (1 / distance_to_light)) + diffuse);
	//vso.lighting = saturate(dot(norm, light_direction) + 2/max(distance_to_light, 0.01f) + diffuse);

	if (norm_dot_light_dir > 0)
	{
		float3 light_dir_projected_onto_normal = norm * norm_dot_light_dir;
		float3 reflect_dir = light_dir_projected_onto_normal + (light_dir_projected_onto_normal - light_direction);

		float3 vec_to_camera = (float3)camera_pos - (float3)pos;
		float3 camera_dir = vec_to_camera / length(vec_to_camera);

		vso.specular = min(1, max(0, dot(reflect_dir, camera_dir)) * 7 / distance_to_light);
	}

	return vso;
}
