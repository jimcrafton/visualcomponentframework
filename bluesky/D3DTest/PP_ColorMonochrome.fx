//-----------------------------------------------------------------------------
// File: PP_ColorMonochrome.fx
//
// Desc: Effect file for image post-processing sample.  This effect contains
//       a single technique with a pixel shader that converts colored image to
//       black & white by performing post-processing on a texture.
//
// Copyright (c) Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------




texture g_txSrcColor;
texture g_txSrcNormal;
texture g_txSrcPosition;
texture g_txSrcVelocity;

texture g_txSceneColor;
texture g_txSceneNormal;
texture g_txScenePosition;
texture g_txSceneVelocity;

sampler2D g_samSrcColor =
sampler_state
{
    Texture = <g_txSrcColor>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSrcNormal =
sampler_state
{
    Texture = <g_txSrcNormal>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSrcPosition =
sampler_state
{
    Texture = <g_txSrcPosition>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSrcVelocity =
sampler_state
{
    Texture = <g_txSrcVelocity>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};

sampler2D g_samSceneColor = sampler_state
{
    Texture = <g_txSceneColor>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSceneNormal = sampler_state
{
    Texture = <g_txSceneNormal>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samScenePosition = sampler_state
{
    Texture = <g_txScenePosition>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};
sampler2D g_samSceneVelocity = sampler_state
{
    Texture = <g_txSceneVelocity>;
    AddressU = Clamp;
    AddressV = Clamp;
    MinFilter = Point;
    MagFilter = Linear;
    MipFilter = Linear;
};




//-----------------------------------------------------------------------------
// Pixel Shader: PostProcessPS
// Desc: Performs post-processing effect that converts a colored image to
//       black and white.
//-----------------------------------------------------------------------------
//float3 LuminanceConv = { 0.2125f, 0.7154f, 0.0721f };
float3 LuminanceConv = { 0.0125f, 0.7154f, 0.9721f };


float timer;
float amt;


float4 PostProcessPS( float2 Tex : TEXCOORD0 ) : COLOR0
{
    //return 1.0f - dot( (float3)tex2D( g_samSrcColor, Tex ), LuminanceConv );

	//Tex.x*=0.5f;

//float temp=Tex.x;
//Tex.x=Tex.y;
//Tex.y=temp;


float2 wave;

wave.y = Tex.y + (sin((Tex.x*15)+timer)*amt);
wave.x = Tex.x + (sin((Tex.y*5)+timer)*amt);


	float4 c=tex2D(g_samSrcColor,Tex);

	//c.r = 1.0f - c.r;
	//c.g = 1.0f - c.g;
	//c.b = 1.0f - c.b;

//c.r *= 0.5f+sin(Tex.y*50)*2;
//c.g *= 0.5f+cos(Tex.y*2)*2;
//c.b *= 0.5f+sin(Tex.x*15)*2;

//c.r+=0.3f;

//c.b+=0.7f;
//c.r-=0.25f;



return c;
}




//-----------------------------------------------------------------------------
// Technique: PostProcess
// Desc: Performs post-processing effect that converts a colored image to
//       black and white.
//-----------------------------------------------------------------------------
technique PostProcess
{
    pass p0
    {
        VertexShader = null;
        PixelShader = compile ps_2_0 PostProcessPS();
        ZEnable = false;
    }
}
