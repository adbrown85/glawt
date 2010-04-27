/*
 * texture.frag
 *     Allows the user to select a texture with a uniform.
 * 
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#version 130
uniform sampler2D unit;
in vec3 TexCoord;
out vec4 FragColor;



void main() {
	
	FragColor = texture(unit, TexCoord.st);
}

