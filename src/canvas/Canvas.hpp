/*
 * Canvas.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CANVAS_HPP
#define CANVAS_HPP
#include "common.h"
#include <algorithm>                    // For find
#include "Combo.hpp"
#include "Extensions.hpp"
#include "Toolkit.hpp"
#define CANVAS_WIDTH 512
#define CANVAS_HEIGHT 512
using namespace std;


/* Current mouse coordinates and combination. */
struct CanvasState {
	int x, y;
	Combo combo;
};

/* Change in the state of the canvas and what caused it. */
#define CANVAS_EVENT_TYPE_SIZE 5
class Canvas;
struct CanvasEvent {
	enum {SETUP,DISPLAY,KEY,BUTTON,DRAG};
	int type;
	Canvas *source;
	CanvasState state;
};

/* Object that wants to be informed of changes in the canvas. */
class CanvasListener {
public:
	virtual void onCanvasEvent(const CanvasEvent &event) = 0;
}; 


/** @brief Area in a window that can be drawn to.
 * @ingroup graphics
 */
class Canvas {
public:
	Canvas(int width=CANVAS_WIDTH, int height=CANVAS_HEIGHT);
	void addListener(CanvasListener *listener, int type);
	void clear();
	static void check();
	void fireEvent(int type);
	virtual void flush() = 0;
	virtual GLuint getElapsedTime() = 0;
	int getHeight();
	int getWidth();
	virtual void refresh() = 0;
	virtual void primeStart() = 0;
	virtual void primeFinish() = 0;
	virtual void setAutomaticallyRefresh(bool automaticRefresh);
	virtual void write(const string &text, int x=15, int y=30) = 0;
protected:
	bool isAutomaticallyRefresh();
	virtual void connectIdle() = 0;
	virtual void disconnectIdle() = 0;
	bool isMouseButtonPressed;
	void setStarted(bool started);
	CanvasState state;
private:
	bool automaticallyRefresh, started;
	int height, width;
	list<CanvasListener*> listeners[CANVAS_EVENT_TYPE_SIZE];
};

/** @return Height of the canvas. */
inline int Canvas::getHeight() {return height;}

/** @return Width of the canvas. */
inline int Canvas::getWidth() {return width;}

inline bool Canvas::isAutomaticallyRefresh() {return automaticallyRefresh;}

inline void Canvas::setStarted(bool started) {this->started = started;}


#endif
