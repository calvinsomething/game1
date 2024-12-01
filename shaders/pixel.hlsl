float4 main(float4 pos : SV_Position, float4 color : COLOR, float specular : FLOAT) : SV_Target
{
	return float4(saturate((float3)color + float3(color.r + 0.7f, color.g + 0.7f, color.b + 0.7f) * (pow(specular, 2))), color.a);
}
