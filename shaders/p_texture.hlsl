Texture2D tex : register(t0);
SamplerState smpl : register(s0);

float4 main(float2 tc : TexCoord, float flat_lighting : COLOR1, float4 pos : SV_Position) : SV_Target
{
	// TODO specular highlighting

	float4 color = tex.Sample(smpl, tc);
	return color * flat_lighting;
}
