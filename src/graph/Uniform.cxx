/*
 * Uniform.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <string>
#include <vector>
#include "Node.hpp"
#include "Program.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"
#include "Uniform.hpp"
using namespace std;
void apply(Node*);
void display(void);
void init(string);



/**
 * Unit test for Uniform.
 */
int main(int argc,
         char *argv[]) {
	
	Scene scene;
	Tag tag;
	Uniform *uniform;
	
	// Initialize
	init("Uniform");
	
	try {
		
		// Test tag
		tag.attributes["type"] = "int";
		tag.attributes["name"] = "foo";
		tag.attributes["value"] = "36.9";
		tag.attributes["link"] = "bar";
		uniform = new Uniform(tag);
		uniform->print();
		
		// Create scene
		scene.addToLast(new Texture2D("crate", "input/crate.jpg"));
		scene.addToLast(new Texture2D("stone", "input/stone.jpg"));
		scene.addToLast(new Program());
		scene.addToLast(new Shader("fragment", "glsl/texture.frag"));
		scene.addToLast(new Uniform("sampler2D", "primary", 0, "stone"));
		
		// Prepare scene
		scene.prepare();
		scene.print();
	}
	catch (const char *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Start display
	apply(&scene.root);
	glutDisplayFunc(display);
	glutMainLoop();
}



/**
 * Utility for applying Nodes.
 */
void apply(Node *node) {
	
	Applicable *applicable;
	int count;
	vector<Node*> children;
	
	// Apply node
	applicable = dynamic_cast<Applicable*>(node);
	if (applicable != NULL)
		applicable->apply();
	
	// Apply children
	children = node->getChildren();
	count = children.size();
	for (int i=0; i<count; ++i)
		apply(children[i]);
}



/**
 * GLUT display callback.
 */
void display(void) {
	
	// Initialize
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -4.0);
	
	// Draw
	glBegin(GL_QUADS); {
		glTexCoord2f(1.0, 1.0);
		glVertex3f( 1.0,  1.0, 0.0);
		glTexCoord2f(0.0, 1.0);
		glVertex3f(-1.0,  1.0, 0.0);
		glTexCoord2f(0.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glTexCoord2f(1.0, 0.0);
		glVertex3f( 1.0, -1.0, 0.0);
	} glEnd();
	
	// Finish
	glFlush();
}



/**
 * Initializes the GLUT display.
 */
void init(string title) {
	
	char **argv;
	int argc=0;
	
	// Print
	cout << endl;
	cout << "****************************************" << endl;
	cout << title << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(50, 300);
	glutInitWindowSize(640, 480);
	glutCreateWindow(title.c_str());
	
	// Set up viewport
	glViewport(0, 0, 640, 480);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1.33, 1.0, 100.0);
}

