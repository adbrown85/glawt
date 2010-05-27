/*
 * Producer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef PRODUCER_HPP
#define PRODUCER_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Command.hpp"
#include "Worker.hpp"
#include "AdvancedFactory.hpp"
#include "BasicFactory.hpp"
using namespace std;


/** @brief Worker responsible for creating and storing scenes.
 * @ingroup backend
 */
class Producer : public Worker {
public:
	Producer(Scene *s, Canvas *c) : Worker(s,c) {}
	void copy(int command);
	void cut(int command);
	void duplicate(int command);
	void list(int command);
	void open(int command, const string &arg);
	void paste(int command);
	void quit(int command);
	void save(int command);
};


#endif
