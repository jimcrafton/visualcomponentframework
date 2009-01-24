vec4 shaderMain( sampler2D inImage )
{
	vec4 value = texture2D(inImage, vec2(gl_TexCoord[0]));

	return value;
}
