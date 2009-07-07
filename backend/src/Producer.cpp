/*
 * Producer.cpp
 *     Responsible for creating and storing scenes.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Producer.hpp"



/**
 * Adds the commands this delegate supports and sets up handlers.
 */
Producer::Producer() {
	
	// Set type
	type = "Producer";
	
	// Add zero-argument handlers
	handlersZero[Command::COPY] = &Producer::copy;
	handlersZero[Command::CUT] = &Producer::cut;
	handlersZero[Command::DUPLICATE] = &Producer::duplicate;
	handlersZero[Command::EXIT] = &Producer::quit;
	handlersZero[Command::PASTE] = &Producer::paste;
	handlersZero[Command::SAVE] = &Producer::save;
	
	// Add string-argument handlers
	handlersString[Command::OPEN] = &Producer::open;
}



void Producer::copy(Scene *scene,
                    int command) {
	
	std::cout << "Producer::cmdCopy(Scene*,int)" << std::endl;
}



void Producer::duplicate(Scene *scene,
                         int command) {
	
	std::cout << "Producer::cmdDuplicate(Scene*,int)" << std::endl;
}



void Producer::cut(Scene *scene,
                   int command) {
	
	std::cout << "Producer::cmdCut(Scene*,int)" << std::endl;
}



void Producer::open(Scene *scene,
                    int command,
                    string filename) {
	
	Node *currentNode;
	Parser parser;
	vector<Tag>::iterator ti;
	
	// Parse file into tags
	parser.open(filename);
	
	// Process tags
	currentNode = &scene->rootNode;
	try {
		for (ti=parser.tags.begin(); ti!=parser.tags.end(); ++ti) {
			if (ti->name.compare("item") == 0)
				openItem(currentNode, *ti);
			else if (ti->name.compare("position") == 0)
				currentNode = openPosition(currentNode, *ti);
		}
	}
	catch (char const *e) {
		cerr << e << endl;
		exit(1);
	}
}



void Producer::openItem(Node *currentNode,
                        Tag &tag) {
	
	float size;
	Item *item;
	map<string,string>::iterator ai;
	string type;
	
	// Get size
	ai = tag.attributes.find("size");
	if (ai != tag.attributes.end())
		size = atof(ai->second.c_str());
	else
		throw "Item does not have size.";
	
	// Get type
	ai = tag.attributes.find("type");
	if (ai != tag.attributes.end())
		type = ai->second;
	else
		throw "Item does not have type.";
	
	// Make item
	if (type.compare("Box") == 0)
		item = new Box(size);
	else
		throw "Item type not supported.";
	
	// Add to scene
	currentNode->add(item);
}



Node* Producer::openPosition(Node *currentNode,
                             Tag &tag) {
	
	float x, y, z;
	map<string,string>::iterator ai;
	Translation *translation;
	
	// Check for closing
	if (tag.closing)
		return currentNode->parent;
	
	// Get x
	ai = tag.attributes.find("x");
	if (ai != tag.attributes.end())
		x = atof(ai->second.c_str());
	else
		throw "Position does not have x coordinate.";
	
	// Get y
	ai = tag.attributes.find("y");
	if (ai != tag.attributes.end())
		y = atof(ai->second.c_str());
	else
		throw "Position does not have y coordinate.";
	
	// Get z
	ai = tag.attributes.find("z");
	if (ai != tag.attributes.end())
		z = atof(ai->second.c_str());
	else
		throw "Position does not have z coordinate.";
	
	// Set position
	translation = new Translation(x, y, z);
	currentNode->add(translation);
	return translation;
}



void Producer::paste(Scene *scene,
                     int command) {
	
	std::cout << "Producer::cmdPaste(Scene*,int)" << std::endl;
}



void Producer::save(Scene *scene,
                    int command) {
	
	std::cout << "Producer::cmdSave(Scene*,int)" << std::endl;
}



void Producer::quit(Scene *scene,
                    int command) {
	
	exit(0);
}



/**
 * Simple test program.
 */
/*
int main(int argc, char *argv[]) {
	
	using namespace std;
	Scene scene;
	Producer producer;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Producer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	producer.open(&scene, Command::OPEN, "input/scene.xml");
	scene.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Producer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
*/
