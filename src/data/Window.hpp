/*
 * Window.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Matrix.hpp"
#include "Quaternion.hpp"
#include "Vector.hpp"
#include <GL/glut.h>
#define GLUT_UP_BUTTON 3
#define GLUT_DOWN_BUTTON 4
#define DEFAULT_SCREEN_X 50
#define DEFAULT_SCREEN_Y 300
#define DEFAULT_WIDTH 512
#define DEFAULT_HEIGHT 512
#define DEFAULT_ZOOM -10.0
#define DEFAULT_ROTATE_AMOUNT 5.0
using namespace std;


typedef void (*display_callback_t)(void);
typedef void (*keyboard_callback_t)(unsigned char,int,int);
typedef void (*mouse_callback_t)(int,int,int,int);
typedef void (*special_callback_t)(int,int,int);
typedef void (*idle_callback_t)(void);


/**
 * @ingroup data
 * @brief Utility for working with OpenGL and the windowing system.
 */
class Window {
public :
	static void init(int argc, char *argv[]);
	static void applyView();
	static void clear();
	static void check();
	static void create(const string &title,
	                   int width=DEFAULT_WIDTH,
	                   int height=DEFAULT_HEIGHT);
	static void flush();
	static Vector getPosition();
	static Matrix getRotationMatrix();
	static int getHeight();
	static int getWidth();
	static void quit();
	static void refresh();
	static void reset();
	static void rotate(float angle, const Vector &axis);
	static void setDisplay(display_callback_t display);
	static void setKeyboard(keyboard_callback_t keyboard);
	static void setMouse(mouse_callback_t keyboard);
	static void setIdle(idle_callback_t idle);
	static void setSpecial(special_callback_t special);
	static void start();
	static void translate(const Vector &move);
	static void translate(float x, float y, float z);
	static void write(const string &text, int x=15, int y=30);
protected:
	static void display(void);
	static void keyboard(unsigned char key, int x, int y);
	static void mouse(int button, int state, int x, int y);
	static void special(int key, int x, int y);
private:
	static int height, width;
	static Quaternion rotation;
	static Vector position;
};

/** Resets all the pixels in the window. */
inline void Window::clear() {glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);}

/** Forces the window to draw all the pixels to the screen. */
inline void Window::flush() {glutSwapBuffers();}

/** @return Position of the camera. */
inline Vector Window::getPosition() {return position;}

/** @return Rotation of the camera as a matrix. */
inline Matrix Window::getRotationMatrix() {return rotation.getMatrix();}

/** @return the height of the window */
inline int Window::getHeight() {return height;}

/** @return the width of the window */
inline int Window::getWidth() {return width;}

/** Initializes the windowing system. */
inline void Window::init(int argc, char *argv[]) {glutInit(&argc, argv);}

/** Closes the window and exits the program. */
inline void Window::quit() {exit(0);}

/** Forces the window to be redrawn */
inline void Window::refresh() {glutPostRedisplay();}

/** Sets the display callback for the window. */
inline void Window::setDisplay(display_callback_t cb) {glutDisplayFunc(cb);}

/** Sets the keyboard press callback for the window. */
inline void Window::setKeyboard(keyboard_callback_t cb) {glutKeyboardFunc(cb);}

/** Sets the idle callback for the window. */
inline void Window::setIdle(idle_callback_t cb) {glutIdleFunc(cb);}

/** Sets the mouse click callback for the window. */
inline void Window::setMouse(mouse_callback_t cb) {glutMouseFunc(cb);}

/** Sets the special keys callback for the window. */
inline void Window::setSpecial(special_callback_t cb) {glutSpecialFunc(cb);}

/** Opens the window */
inline void Window::start() {check(); glutMainLoop();}

/** Moves the camera. */
inline void Window::translate(float x,float y,float z) {translate(Vector(x,y,z));}



#endif
