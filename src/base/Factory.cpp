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
		return (*creator)(tag);
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


Node* Factory::open(const string &filename) {
	
	Node *current, *node, *root;
	map<string,string>::const_iterator ai;
	Parser parser;
	string path;
	vector<Tag>::iterator ti;
	
	// Initialize
	root = new Node();
	current = root;
	parser.open(filename);
	
	// Look through tags
	for (ti=parser.tags.begin(); ti!=parser.tags.end(); ++ti) {
		
		// Step back on closing tags
		if (ti->closing) {
			current = current->getParent();
			continue;
		}
		
		// Make "file" attributes relative to scene file
		ai = ti->attributes.find("file");
		if (ai != ti->attributes.end()) {
			path = FileUtility::getRelativePath(filename, ai->second);
			ti->attributes["file"] = path;
		}
		
		// Create node and update current
		node = create(*ti);
		current->addChild(node);
		if (!ti->empty)
			current = node;
	}
	
	// Finish
	return root;
}

