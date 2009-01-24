//emboss.shader


vec4 shaderMain( sampler2D inImage )
{
	vec4 value = texture2D(inImage, gl_TexCoord[0].xy);

	value.a = 1.0f;
	value.rgb = vec3(0.5f);
	float displacement = 0.001;
	float val = 2.0f;
	value -= texture2D( inImage, gl_TexCoord[0].xy-displacement)*val;
	value += texture2D( inImage, gl_TexCoord[0].xy+displacement)*val;
	value.rgb = vec3((value.r+value.g+value.b)/3.0f);


	return value;
}
