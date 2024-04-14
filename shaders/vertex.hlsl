float4 main(float4 pos : POSITION) : SV_Position
{
	return float4(pos.x, pos.y, pos.z, pos.w);
}
