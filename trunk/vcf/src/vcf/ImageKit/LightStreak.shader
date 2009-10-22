//LightStreak.shader


vec4 shaderMain( sampler2D inImage ) 
{
	
	vec2 uv = gl_TexCoord[0].xy;

	vec2 Direction = vec2(xDirection, yDirection);
    vec2 PixelSize = vec2(pixelWidth, pixelHeight);

    vec4 pixelColor = texture2D(inImage, uv);
    vec4 bright = saturate((pixelColor - brightThreshold) / (1.0 - brightThreshold));

    pixelColor += bright;

    float weightIter = pow(float(numSamples), float(iteration));
    
    for(int sample=0; sample<numSamples; sample++)
    {
        float weight = pow(attenuation, weightIter * float(sample));
        vec2 texCoord = uv + (Direction * weightIter * vec2(float(sample), float(sample)) * PixelSize);
        pixelColor += saturate(weight) * texture2D(inImage,  texCoord);
    }
      
    return pixelColor * scale;	
}
