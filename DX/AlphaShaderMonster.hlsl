
texture map;
sampler samp
{
    TExture = map;
};

float4 main(float2 uv : TEXCOORD0) : SV_TARGET
{
    float4 result = tex2D(samp, uv);

    //if(result.a <= 0.2f)
    //{
    //    result.rgb = 1.0f;
    //}

        return result;
}

technique alphaShader
{
    pass p0
    {
        AlphaBlendEnable = false;
        PixelShader = compile ps_2_0 main();
    }
    pass p1
    {
        AlphaBlendEnable = true;
        //BlendOp = Add;
        //DestBlend = InvSrcAlpha;
        //SrcBlend = SrcAlpha;
        BlendOp = Add;
        DestBlend = SrcColor;
        SrcBlend = Zero;
        PixelShader = compile ps_2_0 main();
    }
    pass p2//ADDITIVE
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = One;
        SrcBlend = SrcAlpha;
        PixelShader = compile ps_2_0 main();
    }
    pass p3 //Á¦°öÇÕ¼º
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = InvSrcAlpha;        
        SrcBlend = SrcColor | SrcAlpha;        
        PixelShader = compile ps_2_0 main();
    }
    pass p4//°ö¼ÀÇÕ¼º
    {
        AlphaBlendEnable = true;
        BlendOp = Add;
        DestBlend = SrcColor;
        SrcBlend = Zero;
        PixelShader = compile ps_2_0 main();
    }
}