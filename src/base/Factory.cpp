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
		ostringstream msg;
		msg << "[Factory] Could not find creator function for '"
		    << tag.getName() << "'.";
		throw msg.str().c_str();
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
		path = tag.getAttribute("file");
		path = FileUtility::replaceEnvironmentVariable(path);
		if (!xmlFilename.empty()) {
			path = FileUtility::getRelativePath(xmlFilename, path);
		}
		tag.setAttribute("file", path);
	}
	return tag;
}


Node* Factory::open(string xmlFilename) {
	
	Node *current, *node, *root;
	Parser parser;
	string path;
	vector<Tag> tags;
	vector<Tag>::iterator it;
	
	// Initialize
	root = new Node();
	current = root;
	xmlFilename = FileUtility::replaceEnvironmentVariable(xmlFilename);
	parser.open(xmlFilename);
	
	// Look through tags
	tags = parser.getTags();
	for (it=tags.begin(); it!=tags.end(); ++it) {
		
		// Step back on closing tags
		if (it->isClosing()) {
			current = current->getParent();
			continue;
		}
		
		// Create node and update current
		node = create(*it, xmlFilename);
		current->addChild(node);
		if (!it->isLeaf())
			current = node;
	}
	
	// Finish
	return root;
}

