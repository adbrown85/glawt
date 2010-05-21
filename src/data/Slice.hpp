/*
 * Slice.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SLICE_HPP
#define SLICE_HPP
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <GL/glut.h>
#include <iomanip>
#include <iostream>
#include "Dataset.hpp"


/**
 * @ingroup data
 * @brief Utility for accessing and drawing a slice of a volume.
 */
class Slice {
public :
	Slice(Dataset *dataset, int index);
	void draw();
	int getIndex() const;
	void next();
	void previous();
protected:
	void initType();
private:
	GLenum type;
	int block, height, index, length, total, width;
	Dataset *dataset;
};

inline int Slice::getIndex() const {return index;}


#endif
