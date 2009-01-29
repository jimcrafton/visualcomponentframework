//blackandwhite.shader


vec4 shaderMain( sampler2D inImage )
{
	vec4 value = texture2D(inImage, gl_TexCoord[0].xy);
	float lower = 1.0-midpoint;
	float upper = 1.0-lower;
	value.rgb = vec3((value.r + value.g + value.b)/3.0f);
	if (value.r<lower || value.r>upper) value.r = 0.0f; else value.r = 1.0f;
	if (value.g<lower || value.g>upper) value.g = 0.0f; else value.g = 1.0f;
	if (value.b<lower || value.b>upper) value.b = 0.0f; else value.b = 1.0f;	

	return value;
}
