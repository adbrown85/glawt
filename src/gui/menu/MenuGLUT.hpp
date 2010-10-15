/*
 * MenuGLUT.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MENUGLUT_HPP
#define MENUGLUT_HPP
#include "common.h"
#ifdef HAVE_GLUT
#include "Control.hpp"
using namespace std;


/** @brief Menu of commands for GLUT.
 * @ingroup gui
 */
class MenuGLUT : public Control {
public:
	MenuGLUT(Delegate *delegate);
	virtual void install();
	virtual void load() {}
	static void onClick(GLint option);
protected:
	void addMenuEntries(list<int> &entries);
	void createFileMenu();
	void createEditMenu();
	void createViewMenu();
private:
	static MenuGLUT *instance;
	int mainMenuID, fileMenuID, editMenuID, viewMenuID;
};


#endif // HAVE_GLUT
#endif
