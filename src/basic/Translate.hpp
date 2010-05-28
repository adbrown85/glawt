/*
 * Translate.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRANSLATE_HPP
#define TRANSLATE_HPP
#include "common.h"
#include "Matrix.hpp"
#include "Tag.hpp"
#include "Transformation.hpp"
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief %Node that moves items in the scene.
 */
class Translate : public Transformation,
                  public Vector {
public:
	Translate(const Tag &tag);
	void add(const Vector &B);
	virtual void apply();
	virtual void applyTo(Matrix &matrix);
	static Translate* find(Node *node);
	virtual void remove();
	virtual bool setAttribute(pair<string,string> attribute);
	virtual string toString() const;
protected:
	virtual void sortByDepthEnd(Matrix &matrix);
};


#endif
