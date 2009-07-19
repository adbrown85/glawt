/*
 * Producer.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __PRODUCER_HPP__
#define __PRODUCER_HPP__
#include <cstdlib>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <typeinfo>
#include <vector>
#include "Box.hpp"
#include "Command.hpp"
#include "Delegate.hpp"
#include "Node.hpp"
#include "Parser.hpp"
#include "Scene.hpp"
#include "Shape.hpp"
#include "Tag.hpp"
#include "Translation.hpp"
using std::cerr;
using std::endl;
using std::map;
using std::stack;
using std::string;
using std::vector;



/**
 * @brief
 *     %Delegate responsible for creating and storing scenes.
 * @ingroup backend
 */
class Producer : public Delegate {
	
	
	public :
		
		Producer();
		
		virtual void run(int command) {;}
		virtual void run(int command, float argument) {;}
		virtual void run(int command, string argument) {;}
		
		static void copy(Scene *scene, int command);
		static void cut(Scene *scene, int command);
		static void duplicate(Scene *scene, int command);
		static void open(Scene *scene, int command, string filename);
		static void paste(Scene *scene, int command);
		static void quit(Scene *scene, int command);
		static void save(Scene *scene, int command);
	
	
	private :
		
		static Node* openShape(Tag &tag,
		                       Node *currentNode);
		static Node* openTranslation(Tag &tag,
		                             Node *currentNode);
};


#endif
