texture map;

float4 vColor;
sampler samp
{
	Texture = map;
};

float4 main(float2 uv : TEXCOORD0) : SV_TARGET
{
	float4 result = tex2D(samp, uv);
	result *= vColor;
	return result;
}

technique Pixel
{
	pass p0
	{
		PixelShader = compile ps_2_0 main();
	}

}