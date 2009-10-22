//wavy.shader


vec4 shaderMain( sampler2D inImage )
{
	vec4 value = texture2D(inImage, gl_TexCoord[0].xy);

	vec2 Tex = gl_TexCoord[0].xy;
	
	Tex.y = Tex.y + (sin(Tex.x*frequency)*amplitude);
	value = texture2D( inImage, Tex.xy);
	
	return value;
}
