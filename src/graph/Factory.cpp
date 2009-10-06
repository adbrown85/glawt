/*
 * Factory.cpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include "Factory.hpp"



/**
 * Makes a Factory that will create items in a scene.
 * 
 * @param root
 *     Pointer to the root node of a scene.
 * @param filename
 *     Path to an XML scene description.
 */
Factory::Factory(Node *root,
                 string filename) {
	
	// Initialize
	this->root = root;
	this->filename = filename;
}



/**
 * Creates a %Node based on the tag's name.
 * 
 * @param tag
 *     XML tag with name and attributes.
 */
Node* Factory::create(const Tag &tag) {
	
	// Supported nodes
	if (tag.name.compare("box") == 0)
		return new Box(tag);
	else if (tag.name.compare("cull") == 0)
		return new Cull(tag);
	else if (tag.name.compare("framebuffer") == 0)
		return new Framebuffer(tag);
	else if (tag.name.compare("fullscreen") == 0)
		return new Fullscreen(tag);
	else if (tag.name.compare("program") == 0)
		return new Program(tag);
	else if (tag.name.compare("shader") == 0)
		return new Shader(tag);
	else if (tag.name.compare("square") == 0)
		return new Square(tag);
	else if (tag.name.compare("target") == 0)
		return new Target(tag);
	else if (tag.name.compare("texture2d") == 0)
		return new Texture2D(tag);
	else if (tag.name.compare("texture3d") == 0)
		return new Texture3D(tag);
	else if (tag.name.compare("translate") == 0)
		return new Translation(tag);
	else if (tag.name.compare("uniform") == 0)
		return new Uniform(tag);
	
	// Unsupported
	else {
		string message = "[Gander,Factory] Tag '";
		message += tag.name + "' not supported.";
		throw message.c_str();
	}
}



/**
 * Creates items from XML tags.
 * 
 * @param tags
 *     Reference to a collection of tags.
 */
void Factory::start() {
	
	Node *current, *node;
	map<string,string>::const_iterator ai;
	string path;
	vector<Tag>::iterator ti;
	
	// Initialize
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
}

