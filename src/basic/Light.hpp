/*
 * Light.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef LIGHT_HPP
#define LIGHT_HPP
#include "common.h"
#include "SimpleDrawable.hpp"
#include "Scene.hpp"
#include "Resources.hpp"
#include "Traverser.hpp"
#define LIGHT_DEFAULT_AMBIENT  0.2
#define LIGHT_DEFAULT_DIFFUSE  0.4
#define LIGHT_DEFAULT_SPECULAR 1.0
using namespace std;


/** @brief %Light that has intensities and can be transformed.
 * @ingroup basic
 */
class Light : public SimpleDrawable,
              public Nameable, public Dependent {
public:
	Light(const Tag &tag);
	virtual ~Light();
	virtual void draw() const;
	virtual string toString() const;
private:
	float ambient, diffuse, specular;
	Traverser *traverser;
	Scene *widget;
};


#endif
