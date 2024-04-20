struct VSOut {
	float4 color : Color;
	float4 pos : SV_Position;
};

VSOut main(float4 pos : Position, float4 color : Color)
{
	VSOut vso;
	vso.color = color;
	vso.pos = pos;
	return vso;
}
