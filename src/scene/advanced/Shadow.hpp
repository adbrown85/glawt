/*
 * Shadow.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHADOW_HPP
#define SHADOW_HPP
#include "common.h"
#include "Texture.hpp"
#include "SubsceneUser.hpp"
#include "Group.hpp"
#include "Light.hpp"
#include "Resources.hpp"
#include "Target.hpp"
#include "Clone.hpp"
#include "State.hpp"
#include "Scout.hpp"
#define SHADOW_SUBSCENE "ui/shadow-cast.xml"
using namespace std;


/** @brief Shadow map generated from a light and a group.
 * @ingroup advanced
 */
class Shadow : public Texture, public SubsceneUser,
               public NodeListener {
public:
	Shadow(const Tag &tag);
	virtual void associate();
	virtual void finalize();
	virtual void onNodeEvent(NodeEvent &event);
	virtual string toString() const;
protected:
	void findGroup();
	void findLight();
	void findTransforms();
	virtual void openSubscene();
	virtual void prepareSubscene();
	void render();
private:
	string of, from;
	Group *group;
	Light *light;
};


/** Renders the scene from the light's point of view into the shadow map. */
inline void Shadow::onNodeEvent(NodeEvent &event) {render();}


#endif
