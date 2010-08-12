/*
 * UniformSampler.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "UniformSampler.hpp"


/** @throws NodeException if @e link attribute is not specified. */
UniformSampler::UniformSampler(const Tag &tag) :
                               Uniform(tag) {
	
	tag.get("value", value, false);
	if (link.empty()) {
		NodeException e(tag);
		e << "[UniformSampler] Sampler types require link to texture.";
		throw e;
	}
}


void UniformSampler::apply() {
	
	if (location == -1)
		return;
	
	glUniform1i(location, value);
}


void UniformSampler::associate() {
	
	Texture *texture;
	
	// Program
	Uniform::associate();
	
	// Get unit of linked texture
	texture = Texture::find(this, getLink());
	if (texture == NULL) {
		NodeException e(tag);
		e << "[UniformSampler] Could not find texture with '" << link
		  << "' as name.";
		throw e;
	}
	value = texture->getUnit();
}


string UniformSampler::toString() const {
	
	ostringstream stream;
	
	stream << Uniform::toString();
	stream << " value='" << value << "'";
	return stream.str();
}

