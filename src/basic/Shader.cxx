/*
 * Shader.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Shader.hpp"


int main(int argc,
         char *argv[]) {
	
	Program *program;
	Shader *shader;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shader" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	try {
		
		// Create window
		glutInit(&argc, argv);
		glutInitDisplayMode(GLUT_SINGLE);
		glutInitWindowSize(512, 512);
		glutCreateWindow("Shader");
		
		// Test
		program = new Program();
		shader = new Shader("Shader.frag");
		cout << "Shader type: " << shader->getType() << endl;
		program->addChild(shader);
		program->associateTree();
		shader->list();
	}
	catch (const char *e) {
		cerr << e << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Shader" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

