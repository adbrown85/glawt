/*
 * RenderFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "RenderFactory.hpp"


RenderFactory::RenderFactory() {
	
	tags.insert("cull");
	tags.insert("framebuffer");
	tags.insert("target");
}


/**
 * Creates a %Node based on the tag's name.
 * 
 * @param tag XML tag with name and attributes.
 * @throws const_char* if tag name not supported.
 */
Node* RenderFactory::create(const Tag &tag) const {
	
	// Supported nodes
	if (tag.name == "cull")
		return new Cull(tag);
	else if (tag.name == "framebuffer")
		return new Framebuffer(tag);
	else if (tag.name == "target")
		return new Target(tag);
	else
		throw "[RenderFactory] Tag not supported by this factory.";
}

