/*
 * TransformFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "TransformFactory.hpp"


TransformFactory::TransformFactory() {
	
	tags.insert("scale");
	tags.insert("translate");
}


/**
 * Creates a %Node based on the tag's name.
 * 
 * @param tag XML tag with name and attributes.
 * @throws const_char* if tag name not supported.
 */
Node* TransformFactory::create(const Tag &tag) const {
	
	// Supported nodes
	if (tag.name == "scale")
		return new Scale(tag);
	else if (tag.name == "translate")
		return new Translation(tag);
	else
		throw "[TransformFactory] Tag not supported by this factory.";
}

