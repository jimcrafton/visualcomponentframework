//GaussianBlur.shader

#define RADIUS  7
#define KERNEL_SIZE (RADIUS * 2 + 1)
uniform float blurKernel[KERNEL_SIZE];
uniform vec2 offsets[KERNEL_SIZE];



vec4 shaderMain( sampler2D inImage )
{
	vec4 color = texture2D(inImage, gl_TexCoord[0].st );
	vec4 color2 = texture2D(inImage, gl_TexCoord[0].st );
	color.rgb = vec3(0.0);
	color2.rgb = vec3(0.0);
    
    for (int i = 0; i < KERNEL_SIZE; ++i) 
	{
		color.rgb += (texture2D( inImage, gl_TexCoord[0].xy + offsets[i] ) * blurKernel[i]).rgb;

		//color.rgb += (texture2D( inImage, vec2(gl_TexCoord[0].x + offsets[i].x, gl_TexCoord[0].y) ) * blurKernel[i]).rgb;
		//color2.rgb += (texture2D( inImage, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y + offsets[i].y) ) * blurKernel[i]).rgb;
	}
        
    return  color;
}
