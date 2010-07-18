/*
 * Toolkit.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Toolkit.hpp"


Toolkit::Toolkit(int argc, char *argv[]) {
	
#ifdef HAVE_GTK
	kit = new Gtk::Main(argc, argv);
	Gtk::GL::init(argc, argv);
#endif
#ifdef HAVE_GLUT
	glutInit(&argc, argv);
#endif
}


Toolkit::~Toolkit() {
	
#ifdef HAVE_GTK
	delete kit;
#endif
}

