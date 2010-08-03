/*
 * AdvancedFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef ADVANCEDFACTORY_HPP
#define ADVANCEDFACTORY_HPP
#include "common.h"
#include "Factory.hpp"
#include "BasicFactory.hpp"
#include "Bind.hpp"
#include "Blend.hpp"
#include "BooleanAnd.hpp"
#include "Boolean.hpp"
#include "BooleanXor.hpp"
#include "Clear.hpp"
#include "Cull.hpp"
#include "Depth.hpp"
#include "Framebuffer.hpp"
#include "Fullscreen.hpp"
#include "Instance.hpp"
#include "Octree.hpp"
#include "Outputs.hpp"
#include "Placeholder.hpp"
#include "Renderbuffer.hpp"
#include "Screen.hpp"
#include "Sort.hpp"
#include "Target.hpp"
using namespace std;


/** @brief %Factory for creating more esoteric nodes not used by all files.
 * @ingroup advanced
 */
class AdvancedFactory : public Factory {
public:
	static void install();
	static Node* createBoolean(const Tag &tag);
	static Node* createBind(const Tag &tag);
	static Node* createBlend(const Tag &tag);
	static Node* createClear(const Tag &tag);
	static Node* createCull(const Tag &tag);
	static Node* createDepth(const Tag &tag);
	static Node* createFramebuffer(const Tag &tag);
	static Node* createFullscreen(const Tag &tag);
	static Node* createInstance(const Tag &tag);
	static Node* createOctree(const Tag &tag);
	static Node* createOutputs(const Tag &tag);
	static Node* createPlaceholder(const Tag &tag);
	static Node* createRenderbuffer(const Tag &tag);
	static Node* createScreen(const Tag &tag);
	static Node* createSort(const Tag &tag);
	static Node* createTarget(const Tag &tag);
private:
	static bool installed;
};


#endif
