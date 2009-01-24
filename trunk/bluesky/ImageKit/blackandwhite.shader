//blackandwhite.shader


vec4 shaderMain( sampler2D inImage )
{
	vec4 value = texture2D(inImage, gl_TexCoord[0].xy);

	value.rgb = vec3((value.r + value.g + value.b)/3.0f);
	if (value.r<0.2 || value.r>0.8) value.r = 0.0f; else value.r = 1.0f;
	if (value.g<0.2 || value.g>0.8) value.g = 0.0f; else value.g = 1.0f;
	if (value.b<0.2 || value.b>0.8) value.b = 0.0f; else value.b = 1.0f;	

	return value;
}
