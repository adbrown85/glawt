/*
 * Translation.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef TRANSLATION_HPP
#define TRANSLATION_HPP
#include <cstdlib>
#include <GL/glut.h>
#include <iostream>
#include <sstream>
#include <string>
#include "Transformation.hpp"
#include "Vector.hpp"
using namespace std;



/**
 * @brief
 *     %Node that moves items in the scene.
 * @ingroup graph
 */
class Translation : public Transformation,
                    public Vector {
	
	
	public :
		
		Translation(float x=0.0,
		            float y=0.0,
		            float z=0.0);
		
		void add(const Vector &B);
		void apply();
		virtual void print() const;
		void remove();
		string toString() const;
};


#endif
