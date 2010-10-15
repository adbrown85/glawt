/*
 * Factory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Factory.hpp"
map<string,creator_t> Factory::creators;


void Factory::check(const Tag &tag) {
	
	if (!isInstalled(tag.getName())) {
		error(tag);
	}
}


void Factory::install(const string &name, creator_t creator) {
	
	creators[name] = creator;
}


/** Creates copy of @e node as if it were read at line number @e line. */
Node* Factory::copy(Node *node, int line) {
	
	Tag tag;
	
	// Copy tag with new line
	tag = node->getTag();
	tag.setLine(line);
	
	// Finish
	return create(tag);
}


Node* Factory::create(const Tag &tag, const string &xmlFilename) {
	
	creator_t creator;
	map<string,creator_t>::iterator it;
	
	it = creators.find(tag.getName());
	if (it != creators.end()) {
		creator = it->second;
		return (*creator)(filter(tag, xmlFilename));
	} else {
		error(tag);
		return NULL;
	}
}


Node* Factory::create(const string &text, const string &xmlFilename) {
	
	return create(Parser::create(text), xmlFilename);
}


/** @throw NodeException if Factory could not find a creator function. */
void Factory::error(const Tag &tag) {
	
	NodeException e(tag);
	
	e << "[Factory] Could not find creator function for '"
	  << tag.getName() << "'.";
	throw e;
}


Tag Factory::filter(Tag tag, const string &xmlFilename) {
	
	string path;
	
	if (tag.hasAttribute("file")) {
		path = tag["file"];
		path = Path::expand(path);
		if (!xmlFilename.empty()) {
			path = Path::getRelativePath(xmlFilename, path);
		}
		tag["file"] = path;
	}
	return tag;
}


bool Factory::isInstalled(const string &name) {
	
	map<string,creator_t>::iterator it;
	
	it = creators.find(name);
	return (it != creators.end());
}

