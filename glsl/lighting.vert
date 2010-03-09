/*
 * lighting.vert
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */



void light(in int i,
           inout vec4 ambient,
           inout vec4 diffuse) {
	
	float nDotL, nDotHV, pf;
	vec3 L;
	
	L = normalize(vec3(gl_LightSource[i].position - gl_Position));
	nDotL = max(0.0, dot(gl_Normal, L));
	
/*
	nDotHV = max(0.0, dot(normal, vec3(gl_LightSource[i].halfVector)));
	if (nDotL == 0.0)
		pf = 0.0;
	else
		pf = pow(nDotHV, gl_FrontMaterial.shininess);
*/
	
	ambient += gl_LightSource[i].ambient;
	diffuse += gl_LightSource[i].diffuse * nDotL;
	/* specular += gl_LightSource[i].specular * pf; */
}



/**
 * Computes the color of the fragment from ambient and diffuse light.
 */
void main() {
	
	vec4 ambient, diffuse;
	
	/* Initialize */
	ambient = vec4(0.0, 0.0, 0.0, 1.0);
	diffuse = vec4(0.0, 0.0, 0.0, 1.0);
	
	/* Color from ambient and diffuse light */
	gl_TexCoord[0] = gl_MultiTexCoord0;
	gl_Position = ftransform();
	light(0, ambient, diffuse);
	gl_FrontColor = ambient + diffuse;
}

