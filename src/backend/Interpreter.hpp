/*
 * Interpreter.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Cameraman.hpp"
#include "Command.hpp"
#include "Compositor.hpp"
#include "Delegate.hpp"
#include "Director.hpp"
#include "Grip.hpp"
#include "Producer.hpp"
#include "Scene.hpp"
using namespace std;


/* Function pointer listener to be called on a specific command. */
typedef void (*interpreter_listener)();


/**
 * @ingroup backend
 * @brief Interprets commands and passes them on to other %Delegates.
 * 
 * @see Cameraman
 * @see Compositor
 * @see Director
 * @see Grip
 * @see Producer
 */
class Interpreter : public Delegate {
public:
	Interpreter(Scene *scene);
	~Interpreter();
	virtual void addListener(int command, interpreter_listener);
	Scene* getScene() const;
	void print();
	virtual void run(int command);
	virtual void run(int command, float argument);
	virtual void run(int command, string argument);
	void setScene(Scene *scene);
private:
	Scene *scene;
	map<int,void(*)()> listeners;
	vector<Delegate*> delegates;
};



inline Scene* Interpreter::getScene() const {return scene;}

inline void Interpreter::setScene(Scene *scene) {this->scene = scene;}


#endif
