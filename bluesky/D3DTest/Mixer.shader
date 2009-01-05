//Mixer.shader


vec4 shaderMain( sampler2D inImage )
{
	vec4 result = texture2D(inImage, vec2(gl_TexCoord[0]));
	vec4 in2 = texture2D(input2Image, vec2(gl_TexCoord[0]));

	result.a = (in2.r + in2.g + in2.b) / 3.0;

	return result;
}
