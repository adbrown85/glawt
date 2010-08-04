/*
 * Instance.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef INSTANCE_HPP
#define INSTANCE_HPP
#include "common.h"
#include "Duplicate.hpp"
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

/** @brief Smart copy of a group that handles shapes and uniforms.
 * 
 * @warning Default uniforms on shapes in an instance may not work correctly.
 * 
 * @ingroup advanced
 */
class Instance : public Node, public Applicable {
public:
	Instance(const Tag &tag);
	virtual void apply();
	virtual void associateAfter();
	virtual void finalize();
	virtual void finalizeAfter();
	virtual void remove();
	virtual string toString() const;
protected:
	void findExclusions();
	void findShapes();
	void findUniforms();
	void restoreExclusions();
	void restoreShapes();
	void restoreUniforms();
	void saveShapes();
	void saveUniforms();
private:
	Duplicate *duplicate;
	bool suppress;
	Suppressor suppressor;
	string of, exclude;
	map<string,Shape*> exclusions;
	map<Shape*,ShapeSnapshot> shapes;
	map<Uniform*,UniformSnapshot> uniforms;
};


#endif
