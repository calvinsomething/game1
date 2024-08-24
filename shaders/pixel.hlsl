cbuffer CBuf {
	float4 face_colors[6];
}

float4 main(float4 pos : SV_Position, float lighting : COLOR1, uint tid : SV_PrimitiveID) : SV_Target
{
	float4 color = face_colors[(tid / 2) % 6];
	if (pos.x > 0) {
		color *= lighting;
	}
	return color;
}
