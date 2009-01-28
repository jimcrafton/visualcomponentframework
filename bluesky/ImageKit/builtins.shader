
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
