/*
 * AdvancedFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef ADVANCEDFACTORY_HPP
#define ADVANCEDFACTORY_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include "Factory.hpp"
#include "Cull.hpp"
#include "Framebuffer.hpp"
#include "Fullscreen.hpp"
#include "Octree.hpp"
#include "Target.hpp"
#include "Wireframe.hpp"
using namespace std;


/**
 * @ingroup graph
 * @brief
 *     Factory for creating more esoteric nodes not used by many files.
 */
class AdvancedFactory : public Factory {
	
	public:
		
		static void install();
		static Node* createCull(const Tag &tag);
		static Node* createFramebuffer(const Tag &tag);
		static Node* createFullscreen(const Tag &tag);
		static Node* createOctree(const Tag &tag);
		static Node* createTarget(const Tag &tag);
		static Node* createWireframe(const Tag &tag);
	
	private:
		
		static bool installed;
};


#endif
