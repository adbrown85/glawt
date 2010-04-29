/*
 * Translation.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef TRANSLATION_HPP
#define TRANSLATION_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Matrix.hpp"
#include "Tag.hpp"
#include "Transformation.hpp"
#include "Vector.hpp"
using namespace std;


/**
 * @ingroup basic
 * @brief
 *     %Node that moves items in the scene.
 */
class Translation : public Transformation,
                    public Vector {
	
	public:
		
		Translation(float x=0.0,
		            float y=0.0,
		            float z=0.0);
		Translation(const Tag &tag);
		
		void add(const Vector &B);
		virtual void apply();
		virtual void remove();
		virtual string toString() const;
	
	protected:
		
		virtual void sortByDepthBeg(Matrix &matrix);
		virtual void sortByDepthEnd(Matrix &matrix);
};


#endif
