uniform sampler2D myTexture;

#define epsilon 0.0001

void main (void)
{
	
 vec4 value = texture2D(myTexture, vec2(gl_TexCoord[0]));
 
 //if ((value[0] > 1.0-epsilon) && (value[2] > 1.0-epsilon))
   //discard;
   
   

	//value[0] *= 0.5+sin(gl_TexCoord[0].y*50.0)*2.0;
	//value[1] *= 0.5+sin(gl_TexCoord[0].x*10.0)*2.0;
	//value[2] *= 0.5+cos(gl_TexCoord[0].x*50.0)*4.0;

	//value[3] *= 0.5+cos(gl_TexCoord[0].x*7.0);

	//value[3] *= 0.5;

	value[0] += 0.25;
	value[0] += 0.25;

	
	gl_FragColor = value;



  vec4 sum = vec4(0.0);
   float blurSize = 0.90;///512.0; // I've chosen this size because this will result in that every step will be one pixel wide if the RTScene texture is of size 512x512
 
	//vTexCoord = gl_TexCoord;

   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   sum += texture2D(myTexture, vec2(gl_TexCoord[0].x - 4.0*blurSize, gl_TexCoord[0].y)) * 1.0/25.0;
   sum += texture2D(myTexture, vec2(gl_TexCoord[0].x - 3.0*blurSize, gl_TexCoord[0].y)) * 2.0/25.0;
   sum += texture2D(myTexture, vec2(gl_TexCoord[0].x - 2.0*blurSize, gl_TexCoord[0].y)) * 3.0/25.0;
   sum += texture2D(myTexture, vec2(gl_TexCoord[0].x - blurSize, gl_TexCoord[0].y)) * 4.0/25.0;
   sum += texture2D(myTexture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y)) * 5.0/25.0;
   sum += texture2D(myTexture, vec2(gl_TexCoord[0].x + blurSize, gl_TexCoord[0].y)) * 4.0/25.0;
   sum += texture2D(myTexture, vec2(gl_TexCoord[0].x + 2.0*blurSize, gl_TexCoord[0].y)) * 3.0/25.0;
   sum += texture2D(myTexture, vec2(gl_TexCoord[0].x + 3.0*blurSize, gl_TexCoord[0].y)) * 2.0/25.0;
   sum += texture2D(myTexture, vec2(gl_TexCoord[0].x + 4.0*blurSize, gl_TexCoord[0].y)) * 1.0/25.0;
 
 sum[3] = 0.5;
   gl_FragColor = sum;


}