Texture2D tex : register(t0);
SamplerState smpl : register(s0);

float4 main(float2 tc : TexCoord, float lighting : COLOR1, float4 pos : SV_Position, float specular : FLOAT) : SV_Target
{
	float4 color = tex.Sample(smpl, tc) * lighting;

	return float4(saturate((float3)color + float3(color.r + 0.7f, color.g + 0.7f, color.b + 0.7f) * (pow(specular, 2))), color.a);
}
