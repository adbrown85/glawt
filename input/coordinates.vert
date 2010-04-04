/*
 * coordinates.vert
 * 
 * Author
 *     Andrew Brown
 */
#version 130
uniform mat4 MVPMatrix;
in vec4 vertex;
out vec3 texCoord;


void main() {
	
	gl_Position = MVPMatrix * vertex;
	texCoord = gl_MultiTexCoord0;
}

