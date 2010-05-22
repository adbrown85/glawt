/*
 * Dataset.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <cstring>
#include "Dataset.hpp"
/*
Dataset *dataset=NULL;
int position, width, height, depth;
*/


/*
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


void mouse(int button, int state, int x, int y) {
	
	Index index(height-y, x, position);
	GLenum type;
	
	if (state != GLUT_UP) {
		return;
	}
	
	// Left button
	if (button == GLUT_LEFT_BUTTON) {
		switch (dataset->getType()) {
		case GL_UNSIGNED_BYTE:
			cout << (int)dataset->getAsByte(index) << endl;
			break;
		case GL_SHORT:
			cout << dataset->getAsShort(index) << endl;
			break;
		case GL_UNSIGNED_SHORT:
			cout << dataset->getAsUnsignedShort(index) << endl;
			break;
		case GL_FLOAT:
			cout << dataset->getAsFloat(index) << endl;
			break;
		}
	}
	
	// Right button
	type = dataset->getType();
	if (button == GLUT_RIGHT_BUTTON) {
		switch (type) {
		case GL_UNSIGNED_BYTE:
			for (int i=-4; i<4; ++i)
				for (int j=-4; j<4; ++j)
					dataset->set(Index(height-y+j,x+i,position), &uc, type);
			break;
		case GL_SHORT:
			for (int i=-4; i<4; ++i)
				for (int j=-4; j<4; ++j)
					dataset->set(Index(height-y+j,x+i,position), &s, type);
			break;
		case GL_UNSIGNED_SHORT:
			for (int i=-4; i<4; ++i)
				for (int j=-4; j<4; ++j)
					dataset->set(Index(height-y+j,x+i,position), &us, type);
			break;
		case GL_FLOAT:
			for (int i=-4; i<4; ++i)
				for (int j=-4; j<4; ++j)
					dataset->set(Index(height-y+j,x+i,position), &f, type);
			break;
		}
		Window::refresh();
	}
	
	// Wheel
	else if (button == GLUT_UP_BUTTON) {
		next();
	} else if (button == GLUT_DOWN_BUTTON) {
		previous();
	}
}


void special(int key, int x, int y) {
	
	switch(key) {
	case GLUT_KEY_UP:
	case GLUT_KEY_RIGHT:
		next();
		break;
	case GLUT_KEY_DOWN:
	case GLUT_KEY_LEFT:
		previous();
		break;
	}
}
*/


int main(int argc, char *argv[]) {
	
	Dataset *dataset;
	DatasetViewer *viewer;
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
		Window::init(argc, argv);
		viewer = new DatasetViewer();
		viewer->setDataset(dataset);
		viewer->start();
	} catch (Exception &e) {
		cerr << e << endl;
		exit(1);
	}
}

