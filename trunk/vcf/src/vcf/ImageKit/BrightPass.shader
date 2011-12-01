//brightpass.shader
//used as part of a bloom effect, not really complete?



vec4 shaderMain( sampler2D inImage )
{
	vec3 luminanceVector = vec3(0.2125, 0.7154, 0.0721);
    vec4 sample = texture2D(inImage, gl_TexCoord[0].st);

    float luminance = dot(luminanceVector, sample.rgb);
    luminance = max(0.0, luminance - threshold);
    sample.rgb *= sign(luminance);
    sample.a = 1.0;
    
   return sample;
}
