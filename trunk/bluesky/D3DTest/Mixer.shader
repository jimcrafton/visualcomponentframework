//Mixer.shader


vec4 shaderMain( sampler2D input )
{
	vec4 result = texture2D(input, vec2(gl_TexCoord[0]));
	vec4 in2 = texture2D(input2Image, vec2(gl_TexCoord[0]));

	result.a = in2.rgb;

	return result;
}
