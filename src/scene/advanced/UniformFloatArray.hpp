/*
 * UniformFloatArray.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef UNIFORMFLOATARRAY_HPP
#define UNIFORMFLOATARRAY_HPP
#include "common.h"
#include "Uniform.hpp"
#include "Group.hpp"
#include "Shape.hpp"
#include "Calculator.hpp"
using namespace std;


/** @brief Array of uniforms capable of calculating values.
 * @ingroup basic
 */
class UniformFloatArray : public Uniform,
                          public Dependent, public NodeNotifier {
public:
	UniformFloatArray(const Tag &tag);
	virtual ~UniformFloatArray();
	virtual void apply();
	virtual void associate();
	virtual void finalize();
	virtual string toString() const;
public:
	virtual GLsizei getCount() const;
	virtual GLfloat* getValues() const;
	static set<UniformFloatArray*> search(Node *node);
protected:
	void findGroup();
	void findShapes();
private:
	GLfloat *values;
	string as, of;
	GLsizei count;
	Group *group;
	int calculation;
	set<Shape*> shapes;
	Calculator *calculator;
};

inline GLsizei UniformFloatArray::getCount() const {return count;}
inline GLfloat* UniformFloatArray::getValues() const {return values;}


#endif
