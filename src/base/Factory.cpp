/*
 * Factory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Factory.hpp"
map<string,creator_t> Factory::creators;


void Factory::install(const string &name,
                      creator_t creator) {
	
	creators[name] = creator;
}


Node* Factory::create(const Tag &tag) {
	
	creator_t creator;
	map<string,creator_t>::iterator it;
	
	it = creators.find(tag.name);
	if (it != creators.end()) {
		creator = it->second;
		return (*creator)(replace(tag));
	} else {
		ostringstream msg;
		msg << "[Factory] Could not find creator function for '"
		    << tag.name << "'.";
		throw msg.str().c_str();
	}
}


Node* Factory::create(const string &text) {
	
	return create(Parser::create(text));
}


Node* Factory::open(string filename) {
	
	Node *current, *node, *root;
	Parser parser;
	string path;
	vector<Tag> tags;
	vector<Tag>::iterator it;
	
	// Initialize
	root = new Node();
	current = root;
	filename = FileUtility::replaceEnvironmentVariable(filename);
	parser.open(filename);
	
	// Look through tags
	tags = parser.getTags();
	for (it=tags.begin(); it!=tags.end(); ++it) {
		
		// Step back on closing tags
		if (it->isClosing()) {
			current = current->getParent();
			continue;
		}
		
		// Create node and update current
		node = create(*it);
		current->addChild(node);
		if (!it->isLeaf())
			current = node;
	}
	
	// Finish
	return root;
}


Tag Factory::replace(const Tag &tag) {
	
	map<string,string>::iterator ai;
	string path;
	Tag copy(tag);
	
	ai = copy.attributes.find("file");
	if (ai != copy.attributes.end()) {
		path = FileUtility::replaceEnvironmentVariable(ai->second);
		ai->second = path;
	}
	return copy;
}

