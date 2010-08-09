/*
 * Shadow.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHADOW_HPP
#define SHADOW_HPP
#include "common.h"
#include "Texture2D.hpp"
#include "Group.hpp"
#include "Light.hpp"
#include "Scene.hpp"
#include "Resources.hpp"
#include "Target.hpp"
#include "Clone.hpp"
#include "Traverser.hpp"
#include "State.hpp"
#define SHADOW_SUBSCENE_FILENAME "ui/shadow-cast.xml"
using namespace std;


/** @brief Shadow map generated from a light and a group.
 * @ingroup advanced
 */
class Shadow : public Texture2D,
               public NodeListener {
public:
	Shadow(const Tag &tag);
	virtual ~Shadow();
	virtual void associate();
	virtual void finalize();
	virtual void onNodeEvent(NodeEvent &event);
	virtual string toString() const;
protected:
	void findGroup();
	void findLight();
	void findTransforms();
	void openSubscene();
	void prepareSubscene();
	void render();
private:
	string of, from;
	Group *group;
	Light *light;
	Scene *subscene;
	Traverser *traverser;
};


/** Renders the scene from the light's point of view into the shadow map. */
inline void Shadow::onNodeEvent(NodeEvent &event) {render();}


#endif
