//laplace.shader

#define KERNEL_SIZE 9

// Gaussian kernel
// 1 2 1
// 2 4 2
// 1 2 1	
float kernel[KERNEL_SIZE];

uniform sampler2D colorMap;
uniform float width;
uniform float height;



vec2 offset[KERNEL_SIZE];



vec4 shaderMain( sampler2D inImage )
{
	int i = 0;
	float d = 16.0;
	vec4 sum = vec4(0.0);
	sum.a = 1.0;

	float amt = 1.0;
	float step_w = amt/400;
	float step_h = amt/80;

   
   offset[0] = vec2(-step_w, -step_h);
   offset[1] = vec2(0.0, -step_h);
   offset[2] = vec2(step_w, -step_h);
   
   offset[3] = vec2(-step_w, 0.0);
   offset[4] = vec2(0.0, 0.0);
   offset[5] = vec2(step_w, 0.0);
   
   offset[6] = vec2(-step_w, step_h);
   offset[7] = vec2(0.0, step_h);
   offset[8] = vec2(step_w, step_h);
   
   kernel[0] = 1.0/d; 	kernel[1] = 1.0/d;	kernel[2] = 1.0/d;
   kernel[3] = 1.0/d;	kernel[4] = -4.0/d;	kernel[5] = 1.0/d;
   kernel[6] = 1.0/d;   kernel[7] = 1.0/d;	kernel[8] = 1.0/d;
   
   
   if(gl_TexCoord[0].s<0.495)
   {
	   for( i=0; i<KERNEL_SIZE; i++ )
	   {
			vec4 tmp = texture2D(inImage, gl_TexCoord[0].st + offset[i]);
			sum.rgb += tmp.rgb * kernel[i];
	   }
   }
   else if( gl_TexCoord[0].s>0.505 )
   {
		sum = texture2D(inImage, gl_TexCoord[0].xy);
   }
   else
   {
		sum = vec4(1.0, 0.0, 0.0, 1.0);
	}

   return sum;
}
