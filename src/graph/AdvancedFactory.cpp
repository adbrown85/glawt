/*
 * AdvancedFactory.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "AdvancedFactory.hpp"


void AdvancedFactory::install() {
	
	Factory::install("cull", &createCull);
	Factory::install("framebuffer", &createFramebuffer);
	Factory::install("fullscreen", &createFullscreen);
	Factory::install("octree", &createOctree);
	Factory::install("target", &createTarget);
}


Node* AdvancedFactory::createCull(const Tag &tag) {
	
	return new Cull(tag);
}


Node* AdvancedFactory::createFramebuffer(const Tag &tag) {
	
	return new Framebuffer(tag);
}


Node* AdvancedFactory::createFullscreen(const Tag &tag) {
	
	return new Fullscreen(tag);
}


Node* AdvancedFactory::createOctree(const Tag &tag) {
	
	return new Octree(tag);
}


Node* AdvancedFactory::createTarget(const Tag &tag) {
	
	return new Target(tag);
}

