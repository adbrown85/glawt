/*
 * Clone.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CLONE_HPP
#define CLONE_HPP
#include "common.h"
#include "Instance.hpp"
#include "Uniform.hpp"
#include "Shape.hpp"
#include "Suppressor.hpp"
using namespace std;


/* State of a shape. */
struct ShapeSnapshot {
	Program *program;
	list<VertexAttribute> attributes;
};

/* State of a uniform. */
struct UniformSnapshot {
	Program *program;
	int location;
};

/** @brief Smart instance of a group that can handle different programs.
 * 
 * @warning Default uniforms on shapes in a clone may not work correctly.
 * 
 * @see Instance
 * @see Replica
 * 
 * @ingroup advanced
 */
class Clone : public Instance, public Applicable {
public:
	Clone(const Tag &tag);
	virtual void apply();
	virtual void associate();
	virtual void associateAfter();
	virtual void finalize();
	virtual void finalizeAfter();
	virtual void remove() {}
	virtual string toString() const;
protected:
	void findShapes();
	void findUniforms();
	void restoreShapes();
	void restoreUniforms();
	void saveShapes();
	void saveUniforms();
protected:
	map<Shape*,ShapeSnapshot> shapes;
	map<Uniform*,UniformSnapshot> uniforms;
private:
	bool suppress;
	Suppressor suppressor;
};





#endif
