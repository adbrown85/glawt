/*
 * Interpreter.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <map>                          // Storing listeners
#include "Cameraman.hpp"
#include "Compositor.hpp"
#include "Director.hpp"
#include "Grip.hpp"
#include "Producer.hpp"
using namespace std;


/* Interface for an object that wants to be notified of a command. */
class CommandListener {
public:
	virtual void onCommandEvent(int command) = 0;
};


/** @brief Interprets commands and passes them on to workers.
 * @ingroup backend
 * @warning Currently only supports one listener per command.
 * 
 * @see Cameraman
 * @see Compositor
 * @see Director
 * @see Grip
 * @see Producer
 */
class Interpreter {
public:
	Interpreter(Scene *scene, Canvas *canvas);
	~Interpreter();
	void addListener(CommandListener *listener, int command);
	void fireEvent(int command);
	Canvas* getCanvas() const;
	Scene* getScene() const;
	void run(int command);
	void run(int command, float argument);
	void run(int command, string argument);
	void setCanvas(Canvas *canvas);
	void setScene(Scene *scene);
private:
	Scene *scene;
	Canvas *canvas;
	map<int,CommandListener*> listeners;
	Cameraman *cameraman;
	Compositor *compositor;
	Director *director;
	Grip *grip;
	Producer *producer;
};
inline Canvas* Interpreter::getCanvas() const {return canvas;}
inline Scene* Interpreter::getScene() const {return scene;}
inline void Interpreter::setCanvas(Canvas *c) {canvas = c;}
inline void Interpreter::setScene(Scene *s) {scene = s;}


#endif
