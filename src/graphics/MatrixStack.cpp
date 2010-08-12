/*
 * MatrixStack.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "MatrixStack.hpp"


/** Initializes the stack with the identity matrix. */
MatrixStack::MatrixStack() {
	
	matrices.push(Matrix());
}

