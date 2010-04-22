/*
 * UniformSampler.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformSampler.hpp"


UniformSampler::UniformSampler(const Tag &tag) :
                               Uniform(tag) {
	
	className = "UniformSampler";
	tag.get("value", value, false);
	if (link.empty())
		throw "[UniformSampler] Sampler types require link to texture.";
}


void UniformSampler::apply() {
	
	glUniform1i(location, value);
}


void UniformSampler::associate() {
	
	Node *current;
	Texture *texture;
	
	// Program
	Uniform::associate();
	
	// Get unit of linked texture
	current = parent;
	while (current != NULL) {
		texture = dynamic_cast<Texture*>(current);
		if (texture != NULL && texture->getName().compare(link) == 0)
			break;
		current = current->getParent();
	}
	if (texture == NULL) {
		ostringstream msg;
		msg << "[UniformSampler] Could not find texture with '" << link
		    << "'as name.";
		throw msg.str().c_str();
	}
	value = texture->getUnit();
}


void UniformSampler::remove() {
	
}


string UniformSampler::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " value='" << value << "'";
	return stream.str();
}

