/*
 * Factory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Factory.hpp"


/**
 * Makes a Factory that will create items in a scene.
 * 
 * @param root Pointer to the root node of a scene.
 * @param filename Path to an XML scene description.
 */
Factory::Factory(Node *root,
                 const string &filename) {
	
	// Initialize
	this->root = root;
	this->filename = filename;
}


/**
 * Creates a %Node based on the tag's name.
 * 
 * @param tag XML tag with name and attributes.
 * @throws const_char* if tag name not supported.
 */
Node* Factory::create(const Tag &tag) {
	
	// Supported nodes
	if (tag.name == "ambient")
		return new Ambient(tag);
	else if (tag.name == "box")
		return new Box(tag);
	else if (tag.name == "boxvbo")
		return new BoxVBO(tag);
	else if (tag.name == "cull")
		return new Cull(tag);
	else if (tag.name == "diffuse")
		return new Diffuse(tag);
	else if (tag.name == "framebuffer")
		return new Framebuffer(tag);
	else if (tag.name == "fullscreen")
		return new Fullscreen(tag);
	else if (tag.name == "light")
		return new Light(tag);
	else if (tag.name == "octree")
		return new Octree(tag);
	else if (tag.name == "position")
		return new Position(tag);
	else if (tag.name == "program")
		return new Program(tag);
	else if (tag.name == "shader")
		return new Shader(tag);
	else if (tag.name == "specular")
		return new Specular(tag);
	else if (tag.name == "square")
		return new Square(tag);
	else if (tag.name == "target")
		return new Target(tag);
	else if (tag.name == "texture2d")
		return new Texture2D(tag);
	else if (tag.name == "texture3d")
		return new Texture3D(tag);
	else if (tag.name == "translate")
		return new Translation(tag);
	else if (tag.name == "uniform") {
		return UniformFactory::create(tag);
	}
	
	// Unsupported
	else {
		ostringstream msg;
		msg << "[Factory] Tag '" << tag.name
		    << "' not supported.";
		throw msg.str().c_str();
	}
}


/**
 * Creates items from XML tags.
 * 
 * @throws const_char* from create().
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

