//wavy2.shader



vec4 shaderMain( sampler2D inImage )
{
	vec4 sample = texture2D(inImage, gl_TexCoord[0].xy);

	float timer = 1.0;
	float amt = 0.081;

	vec2 wave;

	wave.y = gl_TexCoord[0].y + (sin((gl_TexCoord[0].x*15)+timer)*amt);
	wave.x = gl_TexCoord[0].x + (sin((gl_TexCoord[0].y*5)+timer)*amt);


	vec4 c=texture2D(inImage,wave);
//	c.b+=0.7f;
	//c.r-=0.25f;

   return c;
}
