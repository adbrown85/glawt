/*
 * Target.cxx
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Box.hpp"
#include "Program.hpp"
#include "Scene.hpp"
#include "Shader.hpp"
#include "Target.hpp"
#include "Uniform.hpp"
void display(void);
void init(string);
void traverse(Node*);
void traverseChildren(Node*);
Scene scene;



/**
 * Unit test for Target.
 * 
 * <texture name="mytexture" size="512">
 *     <framebuffer>
 *         <target link="mytexture" />
 *         <program>
 *             <shader type="fragment" file="glsl/coordinates.frag" />
 *             <shape type="box" />
 *         </program>
 *     </framebuffer>
 *     <program>
 *         <shader type="fragment" file="glsl/texture.frag" />
 *         <shape type="box" />
 *     </program>
 * </texture>
 */
int main() {
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Target" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	init("Target");
	try {
		
		// Add texture
		scene.addToRoot(new Texture2D("mytexture", 512));
		
		// Add framebuffer and target
		scene.addToLast(new Framebuffer());
		scene.addToLast(new Target("mytexture"));
		scene.backup();
		scene.addToLast(new Program());
		scene.addToLast(new Shader("fragment", "glsl/coordinates.frag"));
		scene.backup();
		scene.addToLast(new Box());
		scene.backup();
		scene.backup();
		scene.backup();
		
		// Add program
		scene.addToLast(new Program());
		scene.addToLast(new Shader("fragment", "glsl/texture.frag"));
		scene.backup();
		scene.addToLast(new Uniform("sampler2D", "texture", 0, "mytexture"));
		scene.addToLast(new Box());
		
		// Prepare
		scene.prepare();
		scene.print();
	}
	catch (const char *e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Start display
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}



void display(void) {
	
	// Start
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -4.0);
	
	// Apply and draw
	traverse(&scene.root);
	
	// Finish
	glFlush();
}



/**
 * Initializes the GLUT display.
 */
void init(string title) {
	
	char **argv;
	int argc=0;
	
	// Create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowPosition(50, 300);
	glutInitWindowSize(512, 512);
	glutCreateWindow(title.c_str());
	
	// Set up viewport
	glViewport(0, 0, 512, 512);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(30.0, 1.0, 1.0, 100.0);
	glEnable(GL_CULL_FACE);
}



void traverse(Node *node) {
	
	Applicable *applicable;
	Drawable *drawable;
	
	// Drawable
	drawable = dynamic_cast<Drawable*>(node);
	if (drawable != NULL) {
		drawable->draw();
		traverseChildren(node);
		return;
	}
	
	// Applicable
	applicable = dynamic_cast<Applicable*>(node);
	if (applicable != NULL) {
		applicable->apply();
		traverseChildren(node);
		applicable->remove();
		return;
	}
	
	// Node
	traverseChildren(node);
}



void traverseChildren(Node *node) {
	
	int count;
	vector<Node*> children;
	
	// Traverse each child
	children = node->getChildren();
	count = children.size();
	for (int i=0; i<count; ++i)
		traverse(children[i]);
}

