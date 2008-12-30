//HueAdjust.shader


vec4 shaderMain( sampler2D input )
{
	vec4 value = texture2D(input, vec2(gl_TexCoord[0]));

	value[0] = value[0] * hueVal;
	value[2] = value[2] * hueVal / 2.0;

	return value;
}
