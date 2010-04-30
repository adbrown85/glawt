/*
 * Window.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WINDOW_HPP
#define WINDOW_HPP
#include <GL/glut.h>
#include <cstdlib>
#include <iostream>
#include <string>
#include "Matrix.hpp"
#include "Quaternion.hpp"
#include "Vector.hpp"
#define DEFAULT_SCREEN_X 50
#define DEFAULT_SCREEN_Y 300
#define DEFAULT_WIDTH 512
#define DEFAULT_HEIGHT 512
#define DEFAULT_ZOOM -5.0
#define DEFAULT_ROTATE_AMOUNT 15.0
using namespace std;


typedef void (*display_callback_t)(void);
typedef void (*keyboard_callback_t)(unsigned char,int,int);
typedef void (*special_callback_t)(int,int,int);
typedef void (*idle_callback_t)(void);


class Window {
public :
	
	static void init(int argc,
	                 char *argv[]);
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
	static void rotate(float angle,
	                   const Vector &axis);
	static void setDisplay(display_callback_t display);
	static void setKeyboard(keyboard_callback_t keyboard);
	static void setIdle(idle_callback_t idle);
	static void setSpecial(special_callback_t special);
	static void start();
	static void translate(const Vector &move);
	static void translate(float x,
	                      float y,
	                      float z);
	
protected:
	
	static void display(void);
	static void keyboard(unsigned char key,
	                     int x,
	                     int y);
	static void special(int key,
	                    int x,
	                    int y);
	
private:
	
	static int height, width;
	static Quaternion rotation;
	static Vector position;
};


inline void Window::clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

inline void Window::flush() {
	glutSwapBuffers();
}

inline Vector Window::getPosition() {
	return position;
}

inline Matrix Window::getRotationMatrix() {
	return rotation.getMatrix();
}

inline int Window::getHeight() {
	return height;
}

inline int Window::getWidth() {
	return width;
}

inline void Window::init(int argc,
                         char *argv[]) {
	glutInit(&argc, argv);
}

inline void Window::quit() {
	exit(0);
}

inline void Window::refresh() {
	glutPostRedisplay();
}

inline void Window::setDisplay(display_callback_t display) {
	glutDisplayFunc(display);
}

inline void Window::setKeyboard(keyboard_callback_t keyboard) {
	glutKeyboardFunc(keyboard);
}

inline void Window::setIdle(idle_callback_t idle) {
	glutIdleFunc(idle);
}

inline void Window::setSpecial(special_callback_t special) {
	glutSpecialFunc(special);
}

inline void Window::start() {
	check();
	glutMainLoop();
}



#endif
