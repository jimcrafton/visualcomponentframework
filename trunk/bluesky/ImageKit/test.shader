//test.shader

float lerp( float x, float y, float s ) 
{
	if ( s <= 0.0 ) {
		return x;
	}
	else if ( s >= 1.0 ) {
		return y;
	}

	return x + s * (y - x);
}


vec2 lerp( vec2 x, vec2 y, float s ) 
{
	if ( s <= 0.0 ) {
		return x;
	}
	else if ( s >= 1.0 ) {
		return y;
	}

	vec2 result = vec2(0.0,0.0);
	result.x = x.x + s * (y.x - x.x);
	result.y = x.y + s * (y.y - x.y);

	return result;
}


vec3 lerp( vec3 x, vec3 y, float s ) 
{
	if ( s <= 0.0 ) {
		return x;
	}
	else if ( s >= 1.0 ) {
		return y;
	}

	vec3 result = vec3(0.0,0.0,0.0);
	result.r = x.r + s * (y.r - x.r);
	result.g = x.g + s * (y.g - x.g);
	result.b = x.b + s * (y.b - x.b);

	return result;
}

vec4 lerp( vec4 x, vec4 y, float s ) 
{
	if ( s <= 0.0 ) {
		return x;
	}
	else if ( s >= 1.0 ) {
		return y;
	}

	vec4 result = vec4(0.0,0.0,0.0,0.0);
	result.r = x.r + s * (y.r - x.r);
	result.g = x.g + s * (y.g - x.g);
	result.b = x.b + s * (y.b - x.b);
	result.a = x.a + s * (y.a - x.a);

	return result;
}

float saturate( float val ) 
{
	float result = clamp(val, 0.0, 1.0);
	return result;
}

vec2 saturate( vec2 val ) 
{
	vec2 result = clamp(val, 0.0, 1.0);
	return result;
}


vec3 saturate( vec3 val ) 
{
	vec3 result = clamp(val, 0.0, 1.0);
	return result;
}


vec4 saturate( vec4 val ) 
{
	vec4 result = clamp(val, 0.0, 1.0);
	return result;
}







vec4 DirectionalBlur( sampler2D inImage )
{
	float Angle = 15.0;
	float BlurAmount = 20.4;

	vec2 uv = gl_TexCoord[0].xy;

	vec4 c = vec4(0.0);
    float rad = Angle * 0.0174533;
    float xOffset = cos(rad);
    float yOffset = sin(rad);

    for(int i=0; i<16; i++)
    {
        uv.x = uv.x - BlurAmount * xOffset;
        uv.y = uv.y - BlurAmount * yOffset;
        c += texture2D(inImage, uv);
    }

    c /= 16.0;
    
    return c;
}

vec4 AdjustSaturation(vec4 color, float saturation)
{
    float grey = dot(color.rgb, vec3(0.3, 0.59, 0.11));
	vec4 g4 = vec4(grey,grey,grey,1.0);

    return lerp(g4, color, saturation);
}



vec4 Convolve( mat3 Kernel, sampler2D inImage ) 
{
	int Width = 400;
	int Height = 80;
	int Dist = 2;//.3;

	int i, j;
	vec2 coord;
	float contrib = 0.0;
	vec4 sum = vec4(0.0);

	// 3x3 convolution matrix
	for(i = -1; i <= 1; i++) 
		for(j = -1; j <= 1; j++) {
			coord = gl_TexCoord[0].st + vec2(float(i) * (1.0/float(Width)) * float(Dist), float(j) * (1.0/float(Height)) * float(Dist));
			sum += Kernel[i+1][j+1] * texture2D(inImage, coord.xy);
			contrib += Kernel[i+1][j+1];
		}

	return sum / contrib;
}


vec4 GaussianBlur( sampler2D inImage )
{
	mat3 gaussianBlur = mat3(1.0f, 2.0f, 1.0f, 2.0f, 4.0f, 2.0f, 1.0f, 2.0f, 1.0f );
	mat3 sharpen = mat3( 0.0f,-1.0f, 0.0f,-1.0f, 5.0f,-1.0f, 0.0f,-1.0f, 0.0f );
	mat3 blur = mat3( 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f );
	mat3 edgeDetect = mat3( 1.0f, 1.0f, 1.0f, 1.0f, 8.0f, 1.0f, 1.0f, 1.0f, 1.0f );
	mat3 edgeEnhance = mat3( 0.0f, 0.0f, 0.0f,-1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f );
	mat3 emboss = mat3( 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,-1.0f );

	return Convolve( sharpen, inImage );
}


vec4 shaderMain( sampler2D inImage )
{
	
	return Bloom(inImage);	
}
