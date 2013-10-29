cbuffer ModelViewProjectionConstantBuffer : register(b0)
{
	matrix model;
	matrix view;
	matrix projection;
};

struct VertexShaderInput
{
	float3 pos : POSITION;
	float3 color : COLOR0;
};

struct VertexShaderOutput
{
	float4 pos : SV_POSITION;
	float3 color : COLOR0;
};

VertexShaderOutput main(VertexShaderInput input)
{
	VertexShaderOutput output;
	float4 pos = float4(input.pos, 1.0f);

	// 将顶点位置转换为投影空间。
	pos = mul(pos, model);
	pos = mul(pos, view);
	pos = mul(pos, projection);
	output.pos = pos;

	// 不加修改地通过颜色。
	output.color = input.color;

	return output;
}
