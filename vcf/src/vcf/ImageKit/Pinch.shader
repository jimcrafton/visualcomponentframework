//Pinch.shader
vec4 shaderMain( sampler2D inImage )
{
	vec2 uv = gl_TexCoord[0].xy;

	vec2 center = vec2( centerX, centerY );
    vec2 displace = center - uv;
    float range = saturate(1.0 - (length(displace) / (abs(-sin(radius * 8.0) * radius) + 0.00000001)));
    return texture2D(inImage, uv + displace * range * amount);
}
