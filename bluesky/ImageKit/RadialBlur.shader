//RadialBlur.shader

//change progress, count, and s for interesting effects

vec4 shaderMain( sampler2D inImage )
{
	vec2 uv = gl_TexCoord[0].xy;

	vec2 center = vec2(centerX,centerY);
	vec2 toUV = uv - center;
	vec2 normToUV = toUV;
	
	vec4 c1 = vec4(0.0,0.0,0.0,0.0);
	
	float s = progress * 0.02;
	
	for(int i=0; i<count; i++)
	{
		c1 += texture2D(inImage, uv - normToUV * s * i); 
	}
	
	c1 /= count;
    vec4 c2 = texture2D(inImage, uv);

	return lerp(c1, c2, progress);
}
