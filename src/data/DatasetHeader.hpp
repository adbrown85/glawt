/*
 * DatasetHeader.hpp
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DATASETHEADER_HPP
#define DATASETHEADER_HPP
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup data
 * @brief
 *     Loads metadata from a dataset.
 * 
 * Perhaps most significant is the type of the data, which determines how many 
 * bytes in the data make up a single sample and what C++ type the sample 
 * corresponds with.  
 * 
 * Also important are the height, width, and depth of the dataset, which is 
 * measured in the number of samples, as well as the offset needed to skip over 
 * the header and get to the data.
 * 
 * @see check()
 * @see getWidth()
 * @see getHeight()
 * @see getDepth()
 * @see getOffset()
 * @see getType()
 */
class DatasetHeader {
	
	public :
		
		DatasetHeader(string filename);
		DatasetHeader(const Tag &tag);
		void check();
		void print() const;
		void read();
		
		int getDepth() const;
		string getFilename() const;
		int getHeight() const;
		int getOffset() const;
		string getType() const;
		int getWidth() const;
	
	private:
		
		float pitch[3];
		int beginning, offset;
		int high, low, max, min;
		int width, height, depth;
		string endian, filename, type;
		vector<string> comments;
};


/**
 * @return Number of samples in the Z direction.
 */
inline int DatasetHeader::getDepth() const {return depth;}


/**
 * @return Path to the file the header is contained in.
 */
inline string DatasetHeader::getFilename() const {return filename;}


/**
 * @return Number of samples in the Y direction.
 */
inline int DatasetHeader::getHeight() const {return height;}


/**
 * This is the number of lines that should be skipped to get to the start 
 * of the actual data in the file.  In other words, the next byte after that 
 * will be the first byte of the actual samples.  Because the Vlib 
 * specification is so strict, we assume that the values read are on six 
 * consecutive lines.  Therefore the offset is just <tt>beginning + 6</tt>, 
 * where @c beginning is the value computed from the check() method.
 * 
 * @return Lines to skip to get past the header.
 */
inline int DatasetHeader::getOffset() const {return offset;}


/**
 * Generally this will be one of:
 *   @li @e uint8 for @c char
 *   @li @e int16 for @c short
 *   @li @e float for @c float
 * 
 * @return String representing the type of the data.
 */
inline string DatasetHeader::getType() const {return type;}


/**
 * @return Number of samples in the X direction.
 */
inline int DatasetHeader::getWidth() const {return width;}


#endif
