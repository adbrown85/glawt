/*
 * Texture3D.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Texture3D.hpp"
using namespace std;
void display(void);
void init(int,char*[],string);


/**
 * Unit test for Texture3D.
 */
int main(int argc,
         char *argv[]) {
	
	string filename;
	Tag tag;
	Texture *texture;
	
	// Handle arguments
	if (argc == 1)
		filename = "../../textures/bear.vlb";
	else if (argc == 2)
		filename = argv[1];
	else {
		cerr << "Usage: " << argv[0] << " <filename> " << endl;
		exit(1);
	}
	
	// Initialize OpenGL
	init(argc, argv, "Texture3D");
	
	try {
		
		// Test tag
		cout << "\nTesting tag..." << endl;
		tag.attributes["file"] = filename;
		tag.attributes["name"] = "bear";
		texture = new Texture3D(tag);
		texture->print();
		
		// Create texture
		cout << "\nCreating texture..." << endl;
		Texture3D texture("bear", filename);
		texture.associate();
		
		// Print
		cout << "\nAttributes:" << endl;
		texture.print();
	}
	catch (char const *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Start OpenGL
	cout << "\nStarting OpenGL..." << endl;
	cout << "  Showing cross-section at p=0.5:" << endl;
	glutDisplayFunc(display);
	glutMainLoop();
}


/**
 * Initializes the GLUT display.
 */
void init(int argc,
          char *argv[],
          string title) {
	
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
	glEnable(GL_BLEND);
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
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord3f(1.0, 1.0, 0.5);
		glVertex3f( 1.0,  1.0, 0.0);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord3f(0.0, 1.0, 0.5);
		glVertex3f(-1.0,  1.0, 0.0);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord3f(0.0, 0.0, 0.5);
		glVertex3f(-1.0, -1.0, 0.0);
		glColor4f(1.0, 1.0, 1.0, 1.0);
		glTexCoord3f(1.0, 0.0, 0.5);
		glVertex3f( 1.0, -1.0, 0.0);
	} glEnd();
	
	// Finish
	glFlush();
}

