//Bloom.shader

vec4 AdjustSaturation(vec4 color, float saturation)
{
    float grey = dot(color.rgb, vec3(0.3, 0.59, 0.11));
	vec4 g4 = vec4(grey,grey,grey,1.0);

    return lerp(g4, color, saturation);
}

vec4 shaderMain( sampler2D inImage ) 
{
	vec2 uv = gl_TexCoord[0].xy;

    vec4 base = texture2D(inImage, uv);
    vec4 bloom = saturate((base - threshold) / (1.0 - threshold));
    
    // Adjust color saturation and intensity.
    bloom = AdjustSaturation(bloom, bloomSaturation) * bloomIntensity;
    base = AdjustSaturation(base, baseSaturation) * baseIntensity;
    
    // Darken down the base image in areas where there is a lot of bloom,
    // to prevent things looking excessively burned-out.
    base *= (1.0 - saturate(bloom));
    
    // Combine the two images.
    return base + bloom;
}