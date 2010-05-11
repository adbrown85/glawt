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
#include <sstream>
#include <string>
#include <vector>
#include "Exception.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * @ingroup data
 * @brief Loads metadata from a dataset.
 * 
 * Perhaps most significant is the type of the data, which determines how many 
 * bytes in the data make up a single sample and what C++ type the sample 
 * corresponds with.  
 * 
 * Also important are the height, width, and depth of the dataset, which is 
 * measured in the number of samples, as well as the offset needed to skip over 
 * the header and get to the data.
 * 
 * Here is the form of a valid file:
 * 
 * <tt>
 * VLIB.1<br>
 * # Comments<br>
 * # More comments<br>
 * width height depth<br>
 * type<br>
 * endian<br>
 * pitchX pitchY pitchZ<br>
 * min max<br>
 * low high<br>
 * </tt>
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
	DatasetHeader(istream &stream);
	int getDepth() const;
	string getFilename() const;
	int getHeight() const;
	int getOffset() const;
	string getType() const;
	int getWidth() const;
	void print() const;
	void write(ostream &stream);
protected:
	
	void check();
	void check(istream &stream);
	void read();
	void read(istream &stream);
private:
	float pitch[3];
	int beginning, offset;
	int high, low, max, min;
	int width, height, depth;
	string endian, filename, type;
	vector<string> comments;
};

/** @return Number of samples in the Z direction. */
inline int DatasetHeader::getDepth() const {return depth;}

/** @return Path to the file the header is contained in. */
inline string DatasetHeader::getFilename() const {return filename;}

/** @return Number of samples in the Y direction. */
inline int DatasetHeader::getHeight() const {return height;}

/**  @return Lines to skip to get past the header.
 * 
 * In other words, the next byte after that will be the first byte of the 
 * actual samples.  Because the Vlib specification is so strict, we assume that 
 * the values read are on six consecutive lines.  Therefore the offset is just 
 * <tt>beginning + 6</tt>, where @c beginning is the value computed from the 
 * check() method.
 */
inline int DatasetHeader::getOffset() const {return offset;}

/** @return String representing the type of the data.
 * 
 * Generally this will be one of:
 *   - @e uint8 for @c char
 *   - @e int16 for @c short
 *   - @e float for @c float
 */
inline string DatasetHeader::getType() const {return type;}

/** @return Number of samples in the X direction. */
inline int DatasetHeader::getWidth() const {return width;}


#endif
