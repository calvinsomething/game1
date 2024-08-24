Texture2D tex : register(t0);
SamplerState smpl : register(s0);

float4 main(float2 tc : TexCoord, float lighting : COLOR1, float4 pos : SV_Position) : SV_Target
{
	float4 color = tex.Sample(smpl, tc);
	return color * lighting;
}
