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



/**
 * Opens a scene from an XML file.
 * 
 * @param scene
 * @param command
 * @param filename
 */
void Producer::open(Scene *scene,
                    int command,
                    string filename) {
	
	Node *currentNode;
	Parser parser;
	vector<Tag>::iterator ti;
	
	// Parse file into tags
	std::cout << "Opening " << filename << endl;
	parser.open(filename);
	
	// Process tags
	currentNode = &scene->rootNode;
	try {
		for (ti=parser.tags.begin(); ti!=parser.tags.end(); ++ti) {
			if (ti->name.compare("shape") == 0)
				currentNode = openShape(*ti, currentNode);
			else if (ti->name.compare("translate") == 0)
				currentNode = openTranslation(*ti, currentNode);
		}
	}
	catch (char const *e) {
		cerr << e << endl;
		exit(1);
	}
}



Node* Producer::openShape(Tag &tag,
                          Node *currentNode) {
	
	float size;
	Shape *shape;
	map<string,string>::iterator ai;
	string type;
	
	// Get size attribute
	ai = tag.attributes.find("size");
	if (ai != tag.attributes.end())
		size = atof(ai->second.c_str());
	else
		throw "Shape does not have size.";
	
	// Get type attribute
	ai = tag.attributes.find("type");
	if (ai != tag.attributes.end())
		type = ai->second;
	else
		throw "Shape does not have type.";
	
	// Make shape
	if (type.compare("Box") == 0)
		shape = new Box(size);
	else
		throw "Shape type not supported.";
	
	// Add to scene
	currentNode->addChild(shape);
	return currentNode;
}



Node* Producer::openTranslation(Tag &tag,
                                Node *currentNode) {
	
	float x, y, z;
	map<string,string>::iterator ai;
	Translation *translation;
	
	// Ignore closing tags
	if (tag.closing)
		return currentNode->parent;
	
	// Get x
	ai = tag.attributes.find("x");
	if (ai != tag.attributes.end())
		x = atof(ai->second.c_str());
	else
		throw "Translate does not have x coordinate.";
	
	// Get y
	ai = tag.attributes.find("y");
	if (ai != tag.attributes.end())
		y = atof(ai->second.c_str());
	else
		throw "Translate does not have y coordinate.";
	
	// Get z
	ai = tag.attributes.find("z");
	if (ai != tag.attributes.end())
		z = atof(ai->second.c_str());
	else
		throw "Translate does not have z coordinate.";
	
	// Set position
	translation = new Translation(x, y, z);
	currentNode->addChild(translation);
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
