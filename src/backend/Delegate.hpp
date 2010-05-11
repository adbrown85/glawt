/*
 * Delegate.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DELEGATE_HPP
#define DELEGATE_HPP
#include <map>
#include <string>
#include "Command.hpp"
#include "Scene.hpp"
using namespace std;


/* Function pointer for a command with no arguments. */
typedef void(*handler_0)(Scene*,int);

/* Function pointer for a command with a float argument. */
typedef void(*handler_f)(Scene*,int,float);

/* Function pointer for a command with a string argument. */
typedef void(*handler_s)(Scene*,int,string);


/**
 * @interface Delegate
 * @ingroup backend
 * @brief Interface for a worker that performs %Commands on the %Scene.
 * 
 * @see Cameraman
 * @see Compositor
 * @see Director
 * @see Grip
 * @see Interpreter
 * @see Producer
 * 
 * @todo Should not have scene, getScene(), or setScene() here.
 */
class Delegate {
public:
	map<int,handler_0> getHandlersZero();
	map<int,handler_f> getHandlersFloat();
	map<int,handler_s> getHandlersString();
	string getType() const;
protected:
	string type;
	map<int,handler_0> handlersZero;
	map<int,handler_f> handlersFloat;
	map<int,handler_s> handlersString;
};

/** @return All the zero-argument handlers this delegate contains. */
inline map<int,handler_0> Delegate::getHandlersZero() {return handlersZero;}

/** @return All the float-argument handlers this delegate contains. */
inline map<int,handler_f> Delegate::getHandlersFloat() {return handlersFloat;}

/** @return All the string-argument handlers this delegate contains. */
inline map<int,handler_s> Delegate::getHandlersString() {return handlersString;}

/** @return Name of the delegate */
inline string Delegate::getType() const {return type;}


#endif
