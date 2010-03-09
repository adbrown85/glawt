/*
 * Slice.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
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
 * @brief
 *     Utility for accessing and drawing a slice of a volume.
 * @ingroup data
 */
class Slice {
	
	
	public :
		
		Slice(Dataset *dataset,
		      int index);
		void draw();
		void next();
		void previous();
		
		int getIndex() {return index;}
	
	
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


#endif
