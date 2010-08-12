/*
 * UniformSampler.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformSampler.hpp"


/** @throws NodeException if @e link attribute is not specified. */
UniformSampler::UniformSampler(const Tag &tag) : Uniform(tag) {
	
	// Check link
	if (!hasLink()) {
		NodeException e(tag);
		e << "[UniformSampler] Sampler types require link to texture.";
		throw e;
	}
}


/** Sets the value in the program. */
void UniformSampler::apply() {
	
	if (location == -1)
		return;
	
	glUniform1i(location, value);
}


/** Finds the correct texture and then sets @e value to its unit. */
void UniformSampler::associate() {
	
	Texture *texture;
	
	// Program
	Uniform::associate();
	
	// Get unit of linked texture
	texture = Texture::find(this, getLink());
	if (texture == NULL) {
		NodeException e(tag);
		e << "[UniformSampler] Could not find texture '" << getLink() << "'";
		throw e;
	}
	value = texture->getUnit();
}


/** @return String comprised of the node's attributes. */
string UniformSampler::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " value='" << value << "'";
	return stream.str();
}

