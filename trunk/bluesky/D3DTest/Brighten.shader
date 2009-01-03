//Brighten.shader


vec4 shaderMain( sampler2D input )
{
	vec4 value = texture2D(input, vec2(gl_TexCoord[0]));

	value.rgb = value.rgb + brightness * value.a;

	return value;
}
