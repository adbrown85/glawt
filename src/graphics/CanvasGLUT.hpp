/*
 * CanvasGLUT.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CANVASGLUT_HPP
#define CANVASGLUT_HPP
#include "common.h"
#ifdef HAVE_GLUT
#include <GL/glut.h>
#include "Canvas.hpp"
using namespace std;


class CanvasGLUT : public Canvas {
public:
	CanvasGLUT(int width=CANVAS_WIDTH, int height=CANVAS_HEIGHT);
	virtual void flush();
	virtual GLuint getElapsedTime();
	virtual void refresh();
	virtual void primeStart() {};
	virtual void primeFinish() {};
	virtual void onRealize();
	virtual void setAutomaticallyRefresh(bool automaticRefresh) {};
	virtual void write(const string &text, int x=15, int y=30);
protected:
	static void display(void);
	static void keyboard(unsigned char key, int x, int y);
	static void mouse(int button, int state, int x, int y);
	static void special(int key, int x, int y);
	static void motion(int x, int y);
	void updateModifier();
private:
	static CanvasGLUT *instance;
};

inline void CanvasGLUT::flush() {glutSwapBuffers();}

inline void CanvasGLUT::refresh() {glutPostRedisplay();}


#endif // HAVE_GLUT
#endif
