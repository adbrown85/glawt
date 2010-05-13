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
#include "BasicFactory.hpp"
#include "Boolean.hpp"
#include "BooleanAnd.hpp"
#include "BooleanXor.hpp"
#include "Bind.hpp"
#include "Blend.hpp"
#include "Cull.hpp"
#include "Framebuffer.hpp"
#include "Fullscreen.hpp"
#include "Group.hpp"
#include "Instance.hpp"
#include "Octree.hpp"
#include "Target.hpp"
#include "Wireframe.hpp"
using namespace std;


/**
 * @ingroup advanced
 * @brief %Factory for creating more esoteric nodes not used by all files.
 */
class AdvancedFactory : public Factory {
public:
	static void install();
	static Node* createBoolean(const Tag &tag);
	static Node* createBind(const Tag &tag);
	static Node* createBlend(const Tag &tag);
	static Node* createCull(const Tag &tag);
	static Node* createFramebuffer(const Tag &tag);
	static Node* createFullscreen(const Tag &tag);
	static Node* createGroup(const Tag &tag);
	static Node* createInstance(const Tag &tag);
	static Node* createOctree(const Tag &tag);
	static Node* createTarget(const Tag &tag);
	static Node* createWireframe(const Tag &tag);
private:
	static bool installed;
};


#endif
