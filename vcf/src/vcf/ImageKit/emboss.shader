//emboss.shader


vec4 shaderMain( sampler2D inImage )
{
	vec4 value = texture2D(inImage, gl_TexCoord[0].xy);

	value.a = 1.0f;
	value.rgb = vec3(0.5f);
	
	value -= texture2D( inImage, gl_TexCoord[0].xy-displacement)*intensity;
	value += texture2D( inImage, gl_TexCoord[0].xy+displacement)*intensity;
	value.rgb = vec3((value.r+value.g+value.b)/3.0f);


	return value;
}
