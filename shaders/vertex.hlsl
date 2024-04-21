cbuffer CBuffer
{
	matrix transform;
};

float4 main(float4 pos : Position) : SV_Position
{
	return mul(pos, transform);
}
