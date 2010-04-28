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

