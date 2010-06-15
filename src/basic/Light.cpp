/*
 * Light.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Light.hpp"


Light::Light(const Tag &tag) : SimpleTransformable(tag) {
	
	string name;
	
	// Intensities
	if (!tag.get("ambient", ambient, false)) {
		ambient = LIGHT_DEFAULT_AMBIENT;
	} if (!tag.get("diffuse", diffuse, false)) {
		diffuse = LIGHT_DEFAULT_DIFFUSE;
	} if (!tag.get("specular", specular, false)) {
		specular = LIGHT_DEFAULT_SPECULAR;
	}
	
	// Name
	if (tag.get("name", name, false)) {
		setName(name);
	}
}


string Light::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	if (hasName())
		stream << " name='" << getName() << "'";
	stream << " ambient='" << ambient << "'"
	       << " diffuse='" << diffuse << "'"
	       << " specular='" << specular << "'";
	return stream.str();
}

