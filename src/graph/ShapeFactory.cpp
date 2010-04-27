/*
 * ShapeFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ShapeFactory.hpp"


ShapeFactory::ShapeFactory() {
	
	tags.insert("cube");
	tags.insert("fullscreen");
	tags.insert("square");
}


/**
 * Creates a %Node based on the tag's name.
 * 
 * @param tag XML tag with name and attributes.
 * @throws const_char* if tag name not supported.
 */
Node* ShapeFactory::create(const Tag &tag) const {
	
	// Supported nodes
	if (tag.name == "cube")
		return new Cube(tag);
	else if (tag.name == "fullscreen")
		return new Fullscreen(tag);
	else if (tag.name == "square")
		return new Square(tag);
	else
		throw "[ShapeFactory] Tag not supported by this factory.";
}

