/*
 * Producer.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __PRODUCER_HEADER__
#define __PRODUCER_HEADER__
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "Box.hpp"
#include "Command.hpp"
#include "Delegate.hpp"
#include "Item.hpp"
#include "Node.hpp"
#include "Parser.hpp"
#include "Tag.hpp"
#include "Scene.hpp"
#include "Translation.hpp"
using std::cerr;
using std::endl;
using std::string;
using std::map;
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
		
		static void openItem(Node *currentNode, Tag &tag);
		static Node* openPosition(Node *currentNode, Tag &tag);
};


#endif
