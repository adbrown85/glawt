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
		
		Translation();
		Translation(float x,
		            float y,
		            float z);
		
		void add(const Vector &B);
		void apply();
		virtual void print() const;
		void remove();
		
		friend ostream& operator<<(ostream &stream,
		                           const Translation &translation);
};


#endif
