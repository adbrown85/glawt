/*
 * GeneralFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "GeneralFactory.hpp"


/**
 * Creates a %Node based on the tag's name.
 * 
 * @param tag XML tag with name and attributes.
 * @throws const_char* if tag name not supported.
 */
Node* GeneralFactory::create(const Tag &tag) {
	
	// Supported nodes
	if (tag.name == "cull")
		return new Cull(tag);
	else if (tag.name == "cube")
		return new Cube(tag);
	else if (tag.name == "framebuffer")
		return new Framebuffer(tag);
	else if (tag.name == "fullscreen")
		return new Fullscreen(tag);
	else if (tag.name == "octree")
		return new Octree(tag);
	else if (tag.name == "program")
		return new Program(tag);
	else if (tag.name == "scale")
		return new Scale(tag);
	else if (tag.name == "shader")
		return new Shader(tag);
	else if (tag.name == "squarevbo")
		return new SquareVBO(tag);
	else if (tag.name == "target")
		return new Target(tag);
	else if (tag.name == "texture2d")
		return new Texture2D(tag);
	else if (tag.name == "texture3d")
		return new Texture3D(tag);
	else if (tag.name == "translate")
		return new Translation(tag);
}

