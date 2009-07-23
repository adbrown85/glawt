/*
 * Shader.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Shader.hpp"
using namespace std;



/**
 * Unit test for Shader.
 */
int main(int argc,
         char *argv[]) {
	
	Shader shader;
	string filename="Shader.glsl";
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shader" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize OpenGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Shader");
	
	// Load and compile
	shader.load('f', filename);
	shader.print();
	shader.compile();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shader" << endl;
	cout << "****************************************" << endl;
	cout << endl;
}
