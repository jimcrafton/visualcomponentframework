//wavy2.shader



vec4 shaderMain( sampler2D inImage )
{
	vec4 sample = texture2D(inImage, gl_TexCoord[0].xy);	

	vec2 wave;
	wave.y = gl_TexCoord[0].y + (sin((gl_TexCoord[0].x*xAmplitude)+progress)*amount);
	wave.x = gl_TexCoord[0].x + (sin((gl_TexCoord[0].y*yAmplitude)+progress)*amount);

	vec4 c=texture2D(inImage,wave);

   return c;
}
