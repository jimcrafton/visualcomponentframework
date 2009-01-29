//Ripple.shader

vec4 shaderMain( sampler2D inImage )
{
	vec2 center  = vec2(centerX, centerY);
	
	vec2 uv = gl_TexCoord[0].xy;
	vec2 dir = uv - center;
   
	vec2 toPixel = uv - center; // vector from center to pixel
	float distance = length(toPixel);
	vec2 direction = toPixel/distance;
	float angle = atan(direction.x, direction.y);
	vec2 wave = vec2(sin(frequency * distance + phase),cos(frequency * distance + phase));
		
	float falloff = saturate(1.0-distance);
	falloff *= falloff;
		
	distance += amplitude * wave.x * falloff;
	direction.y = sin(angle);
	direction.x = cos(angle);
   vec2 uv2 = center + distance * direction;
   
   float lighting = saturate(wave.y * falloff) * 0.2 + 0.8;
   
   vec4 color = texture2D( inImage, uv2 );
   color.rgb *= lighting;
   
   return color;
}