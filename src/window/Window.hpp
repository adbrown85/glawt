/*
 * Window.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GLAWT_WINDOW_HPP
#define GLAWT_WINDOW_HPP
#include "common.h"
#include "Canvas.hpp"
using namespace std;


/** @brief Abstract wrapper for a window.
 * @ingroup graphics
 */
class Window {
public:
	Window() {}
	virtual ~Window() {}
	virtual void add(Canvas *canvas) = 0;
	virtual void* getNativeWindow() = 0;
	virtual string getTitle();
	virtual void run() = 0;
	virtual void setIcon(string filename) = 0;
	virtual void setTitle(string title);
	virtual void show() = 0;
private:
	string title;
	int width, height;
};

inline string Window::getTitle() {return title;}


#endif
