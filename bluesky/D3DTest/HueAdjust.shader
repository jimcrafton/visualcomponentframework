//HueAdjust.shader

uniform sampler2D inputImage;
uniform float hueVal;

#define epsilon 0.0001

void main (void)
{
	vec4 value = texture2D(inputImage, vec2(gl_TexCoord[0]));

	value[0] = value[0] * hueVal;
	value[2] = value[2] * hueVal / 2.0;

	gl_FragColor = value;

}