//DirectionalBlur.shader

vec4 shaderMain( sampler2D inImage )
{
	vec2 uv = gl_TexCoord[0].xy;

	vec4 c = vec4(0.0);
    float rad = angle * 0.0174533;
    float xOffset = cos(rad);
    float yOffset = sin(rad);

    for(int i=0; i<16; i++)
    {
        uv.x = uv.x - amount * xOffset;
        uv.y = uv.y - amount * yOffset;
        c += texture2D(inImage, uv);
    }

    c /= 16.0;
    
    return c;
}