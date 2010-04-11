/*
 * Slice.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SLICE_HPP
#define SLICE_HPP
#include <cstdlib>
#include <fstream>
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include "Dataset.hpp"


/**
 * @ingroup data
 * @brief
 *     Utility for accessing and drawing a slice of a volume.
 */
class Slice {
	
	public :
		
		Slice(Dataset *dataset,
		      int index);
		void draw();
		int getIndex() const;
		void next();
		void previous();
	
	private:
		
		GLenum type;
		int block, height, index, length, total, width;
		Dataset *dataset;
		
		Slice();
		void drawAsByte(int offset);
		void drawAsFloat(int offset);
		void drawAsShort(int offset);
		void initType();
};


inline int Slice::getIndex() const {return index;}


#endif
