/*
 * BooleanAnd.frag
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#version 130

// Uniforms
uniform vec4 Color0;
uniform vec4 Color1;
uniform sampler2D Unit0;
uniform sampler2D Unit1;

// Input
in vec3 Coord0;
in vec3 Coord1;

// Output
out vec4 FragColor;


/** Computes the fragment color from a combination of inputs. */
void main() {
	
	//FragColor = vec4(TexCoord_1, 1);
	//FragColor = Color1;
	FragColor = texture(Unit0,Coord0.st) * texture(Unit1,Coord1.st);
}

