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
#include "Vector.hpp"
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
	DatasetHeader(istream &stream);
	vector<string> getComments() const;
	int getDepth() const;
	string getEndian() const;
	string getFilename() const;
	int getHeight() const;
	int getHigh() const;
	int getLow() const;
	int getMax() const;
	int getMin() const;
	int getOffset() const;
	Vector getPitch() const;
	string getType() const;
	int getWidth() const;
	void print() const;
	void setEndian(const string &endian);
	void setFilename(const string &filename);
	void setLow(int low);
	void setHigh(int high);
	void setMax(int max);
	void setMin(int min);
	void setType(const string &type);
	void setWidth(int width);
	void setHeight(int height);
	void setDepth(int depth);
protected:
	void check();
	void check(istream &stream);
	void read();
	void read(istream &stream);
private:
	Vector pitch;
	int beginning, offset;
	int high, low, max, min;
	int width, height, depth;
	string endian, filename, type;
	vector<string> comments;
};

/** @return User-added description. */
inline vector<string> DatasetHeader::getComments() const {return comments;}

/** @return Number of samples in the Z direction. */
inline int DatasetHeader::getDepth() const {return depth;}

/** @return Little or big byte ordering. */
inline string DatasetHeader::getEndian() const {return endian;}

/** @return Path to the file the header is contained in. */
inline string DatasetHeader::getFilename() const {return filename;}

/** @return Number of samples in the Y direction. */
inline int DatasetHeader::getHeight() const {return height;}

/** @return Highest value in the dataset according to the header. */
inline int DatasetHeader::getHigh() const {return high;}

/** @return Lowest value in the dataset according to the header. */
inline int DatasetHeader::getLow() const {return low;}

/** @return Maximum possible value according to the header. */
inline int DatasetHeader::getMax() const {return max;}

/** @return Minimum possible value according to the header. */
inline int DatasetHeader::getMin() const {return min;}

/** @return Lines to skip to get past the header.
 * 
 * In other words, the next byte after that will be the first byte of the 
 * actual samples.  Because the Vlib specification is so strict, we assume that 
 * the values read are on six consecutive lines.  Therefore the offset is just 
 * <tt>beginning + 6</tt>, where @c beginning is the value computed from the 
 * check() method.
 */
inline int DatasetHeader::getOffset() const {return offset;}

/** @return Size of samples in each direction. */
inline Vector DatasetHeader::getPitch() const {return pitch;}

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

inline void DatasetHeader::setEndian(const string &e) {endian = e;}
inline void DatasetHeader::setFilename(const string &f) {filename = f;}
inline void DatasetHeader::setHigh(int h) {high = h;}
inline void DatasetHeader::setLow(int l) {low = l;}
inline void DatasetHeader::setMin(int m) {min = m;}
inline void DatasetHeader::setMax(int m) {max = m;}
inline void DatasetHeader::setType(const string &t) {type = t;}
inline void DatasetHeader::setWidth(int w) {width = w;}
inline void DatasetHeader::setHeight(int h) {height = h;}
inline void DatasetHeader::setDepth(int d) {depth = d;}


#endif
