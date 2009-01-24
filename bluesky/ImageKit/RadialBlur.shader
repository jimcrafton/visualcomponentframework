//RadialBlur.shader

float lerp( float x, float y, float s ) 
{
	if ( s <= 0.0f ) {
		return x;
	}
	else if ( s >= 1.0f ) {
		return y;
	}

	return x + s * (y - x);
}


vec4 lerp( vec4 x, vec4 y, float s ) 
{
	if ( s <= 0.0f ) {
		return x;
	}
	else if ( s >= 1.0f ) {
		return y;
	}

	vec4 result = vec4(0.0f,0.0f,0.0f,0.0f);
	result.r = x.r + s * (y.r - x.r);
	result.g = x.g + s * (y.g - x.g);
	result.b = x.b + s * (y.b - x.b);
	result.a = x.a + s * (y.a - x.a);

	return result;
}


//change progress, count, and s for interesting effects

vec4 shaderMain( sampler2D inImage )
{
	vec2 uv = gl_TexCoord[0].xy;

	vec2 center = vec2(0.5,0.5);
	vec2 toUV = uv - center;
	vec2 normToUV = toUV;
	
	float progress = 0.90;

	
	vec4 c1 = vec4(0.0,0.0,0.0,0.0);
	int count = 24;
	float s = progress * 0.02;
	
	for(int i=0; i<count; i++)
	{
		c1 += texture2D(inImage, uv - normToUV * s * i); 
	}
	
	c1 /= count;
    vec4 c2 = texture2D(inImage, uv);

	return lerp(c1, c2, progress);
}
