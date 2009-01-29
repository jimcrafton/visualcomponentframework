//Swirl.shader

vec4 shaderMain( sampler2D inImage ) 
{
	vec2 center  = vec2(centerX, centerY);
	vec2 angleFrequency = vec2(xFrequency,yFrequency);

	vec2 uv = gl_TexCoord[0].xy;

	vec2 dir = uv - center;
   float l = length(dir);
   float angle = atan(dir.x,dir.y);
   
   float newAng = angle + spiralStrength * l;
   float xAmt = cos(angleFrequency.x * newAng) * l;
   float yAmt = sin(angleFrequency.y * newAng) * l;
   
   vec2 newCoord = center + vec2(xAmt, yAmt);
   
   return texture2D( inImage, newCoord );
}