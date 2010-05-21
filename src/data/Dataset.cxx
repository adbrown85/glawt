/*
 * Dataset.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cstring>
#include "Dataset.hpp"
#include "Window.hpp"
Dataset *dataset=NULL;
int position, width, height, depth;


/* GLUT special keys callback. */
void special(int key, int x, int y) {
	
	switch(key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_RIGHT:
		if (position == depth-1)
			position = -1;
		++position;
		Window::refresh();
		break;
	case GLUT_KEY_DOWN:
	case GLUT_KEY_LEFT:
		if (position == 0)
			position = depth;
		--position;
		Window::refresh();
		break;
	}
}


/* Draws a slice to the screen. */
void display(void) {
	
	char *data;
	ostringstream stream;
	
	// Clear
	Window::clear();
	stream << position;
	Window::write(stream.str());
	
	// Draw pixels
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();
			glRasterPos2f(-1.0, -1.0);
		glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	data = reinterpret_cast<char*>(dataset->getData());
	data += position * width * height * dataset->getBlock();
	glDrawPixels(width, height, GL_LUMINANCE, dataset->getType(), data);
	
	// Finish
	Window::flush();
}


int main(int argc, char *argv[]) {
	
	string filename;
	
	// Handle arguments
	if (argc == 1) {
		filename = "../../textures/bear.vlb";
	} else if (argc == 2) {
		filename = argv[1];
	} else {
		cerr << "Usage: " << argv[0] << " [<filename>]" << endl;
		exit(1);
	}
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Dataset" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Initialize
	try {
		dataset = new Dataset(filename);
		dataset->load();
		dataset->print();
		width = dataset->getWidth();
		height = dataset->getHeight();
		depth = dataset->getDepth();
		position = 0;
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
	
	// Start the window
	Window::init(argc, argv);
	Window::create(filename, dataset->getWidth(), dataset->getHeight());
	Window::setDisplay(&display);
	Window::setSpecial(&special);
	Window::start();
}

