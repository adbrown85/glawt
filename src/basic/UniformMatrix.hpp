/*
 * UniformMatrix.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef UNIFORMMATRIX_HPP
#define UNIFORMMATRIX_HPP
#include "Uniform.hpp"
using namespace std;


class UniformMatrix : public Uniform {
	
	public:
		
		UniformMatrix(const Tag &tag);
		virtual void apply();
		virtual void remove();
	
	private:
		
		enum MatrixType{MODELVIEW, PROJECTION, MODELVIEW_PROJECTION, NORMAL};
		
		GLfloat value[16];
		MatrixType matrixType;
};


#endif
