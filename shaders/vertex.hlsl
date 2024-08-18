cbuffer CB1
{
	matrix tf_model;
};

cbuffer CB2
{
	matrix tf_view_proj;
};

float4 main(float4 pos : Position) : SV_Position
{
	matrix mvp = mul(tf_model, tf_view_proj);
	return mul(pos, mvp);
}
