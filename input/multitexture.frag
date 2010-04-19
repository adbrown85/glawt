/*
 * multitexture.frag
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#version 130
uniform sampler2D left, right;
in vec3 TexCoord;
out vec4 FragColor;


void main() {
	
	if (TexCoord.s < 0.5)
		FragColor = texture(left, TexCoord.st);
	else
		FragColor = texture(right, TexCoord.st);
}

