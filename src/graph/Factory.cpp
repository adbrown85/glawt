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


Node* Factory::create(const Tag &tag,
                      const string &xmlFilename) {
	
	creator_t creator;
	map<string,creator_t>::iterator it;
	
	it = creators.find(tag.getName());
	if (it != creators.end()) {
		creator = it->second;
		return (*creator)(filter(tag, xmlFilename));
	} else {
		Exception e;
		e << "[Factory] Could not find creator function for '"
		  << tag.getName() << "'.";
		throw e;
	}
}


Node* Factory::create(const string &text,
                      const string &xmlFilename) {
	
	return create(Parser::create(text), xmlFilename);
}


Tag Factory::filter(Tag tag,
                    const string &xmlFilename) {
	
	string path;
	
	if (tag.hasAttribute("file")) {
		path = tag["file"];
		path = FileUtility::replaceEnvironmentVariable(path);
		if (!xmlFilename.empty()) {
			path = FileUtility::getRelativePath(xmlFilename, path);
		}
		tag["file"] = path;
	}
	return tag;
}

