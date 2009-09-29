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
 */
Factory::Factory(Node *root) {
	
	// Initialize
	this->root = root;
}



/**
 * Creates a %Node based on the tag's name.
 * 
 * @param tag
 *     XML tag.
 */
Node* Factory::create(const Tag &tag) {
	
	// Box
	if (tag.name.compare("box") == 0)
		return new Box(tag);
	
	// Program
	else if (tag.name.compare("program") == 0)
		return new Program(tag);
	
	// Shader
	else if (tag.name.compare("shader") == 0)
		return new Shader(tag);
	
	// Texture
	else if (tag.name.compare("texture") == 0)
		return createTexture(tag);
	
	// Translation
	else if (tag.name.compare("translate") == 0)
		return new Translation(tag);
	
	// Uniform
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
 * Creates a texture based on its type.
 * 
 * @param tag
 *     XML tag.
 */
Node* Factory::createTexture(const Tag &tag) {
	
	string type;
	
	// 2D or 3D
	tag.get("type", type);
	if (type.compare("2d") == 0)
		return new Texture2D(tag);
	else if (type.compare("3d") == 0)
		return new Texture3D(tag);
	
	// Unsupported
	else
		throw "[Gander,Factory] Texture type not supported.";
}



/**
 * Creates items from XML tags.
 * 
 * @param tags
 *     Reference to a collection of tags.
 */
void Factory::process(const vector<Tag> &tags) {
	
	Node *current, *node;
	vector<Tag>::const_iterator ti;
	
	// Initialize current node
	current = root;
	
	// Look through tags
	for (ti=tags.begin(); ti!=tags.end(); ++ti) {
		
		// Step back on closing tags
		if (ti->closing) {
			current = current->getParent();
			continue;
		}
		
		// Create node and update current
		node = create(*ti);
		current->addChild(node);
		if (!ti->empty)
			current = node;
	}
}

