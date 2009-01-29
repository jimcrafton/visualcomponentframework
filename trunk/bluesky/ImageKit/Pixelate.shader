//Pixelate.shader


vec4 shaderMain( sampler2D inImage )
{
	vec2 uv = gl_TexCoord[0].xy;
	float pixels;
	float segment_progress;
	if (progress < 0.5)
	{
		segment_progress = 1.0 - progress * 2.0;
	}
	else
	{		
		segment_progress = (progress - 0.5) * 2.0;

	}
    
    pixels = 5.0 + 1000.0 * segment_progress * segment_progress;
	vec2 newUV = round(uv * pixels) / pixels;
	
    vec4 c1 = texture2D(inImage, newUV);
    vec4 c2 = texture2D(inImage, newUV); //this would be a secondary image here

	float lerp_progress = saturate((progress - 0.4) / 0.2);
	return lerp(c1,c1, lerp_progress);	
}