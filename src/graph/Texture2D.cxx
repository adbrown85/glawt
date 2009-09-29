/*
 * Texture2D.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture2D.hpp"
#include "Scene.hpp"
#define NUMBER_OF_TEXTURES 2
using namespace std;
void apply(Node*);
void display(void);
void init(string);
void setTextureCoordinates(float,float);




/**
 * Unit test for Texture.
 */
int main(int argc,
         char *argv[]) {
	
	Texture2D *texture;
	Scene scene;
	Tag tag;
	
	// Initialize
	init("Texture2D");
	
	// Tag
	cout << "\nTesting tag..." << endl;
	tag.attributes["name"] = "foo";
	tag.attributes["file"] = "glsl/bar.frag";
	tag.attributes["size"] = "1024";
	texture = new Texture2D(tag);
	texture->print();
	
	// Create scene
	cout << "\nCreating scene..." << endl;
	scene.addToLast(new Texture2D("crate", "input/crate.jpg"));
	scene.addToLast(new Texture2D("stone", "input/stone.jpg"));
	scene.prepare();
	scene.print();
	
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
		setTextureCoordinates(1.0, 1.0);
		glVertex3f( 1.0,  1.0, 0.0);
		setTextureCoordinates(0.0, 1.0);
		glVertex3f(-1.0,  1.0, 0.0);
		setTextureCoordinates(0.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		setTextureCoordinates(1.0, 0.0);
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



/**
 * Sets texture coordinates on each texture unit.
 */
void setTextureCoordinates(float s,
                           float t) {
	
	for (int i=0; i<NUMBER_OF_TEXTURES; ++i)
		glMultiTexCoord2f(GL_TEXTURE0 + i, s, t);
}

