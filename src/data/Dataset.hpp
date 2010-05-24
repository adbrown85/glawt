/*
 * Dataset.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DATASET_HPP
#define DATASET_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <climits>
#include <cfloat>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <utility>
#include <GL/gl.h>
#include "DatasetHeader.hpp"
#include "Index.hpp"
#include "Tag.hpp"
#include "Window.hpp"
using namespace std;


/**
 * @ingroup data
 * @brief Loads and holds volumetric data.
 * 
 * In most cases, the user is only concerned with getting values from the 
 * data.
 * 
 * To get one value, use one of the @c getAs methods.  However, you should use 
 * @c getType() to determine which one to call first since they will throw an 
 * exception if it doesn't match the dataset's type.  We suggest using a switch 
 * statement for this purpose.
 * 
 * Of course, some purposes will need an actual pointer to all of the data, 
 * such as using the dataset as an OpenGL texture.  In that case, use @c 
 * getData() and @c getType().
 */
class Dataset {
public:
	Dataset(string filename);
	virtual ~Dataset();
	unsigned char getAsByte(const Index &I) const;
	float getAsFloat(const Index &I) const;
	short getAsShort(const Index &I) const;
	unsigned short getAsUnsignedShort(const Index &I) const;
	int getBlock() const;
	void* getData();
	int getDepth() const;
	string getFilename() const;
	GLint getFootprint() const;
	DatasetHeader getHeader() const;
	int getLength() const;
	int getHeight() const;
	int getHigh() const;
	int getLow() const;
	int getMax() const;
	int getMin() const;
	int getMaximumDimension() const;
	GLenum getType() const;
	int getWidth() const;
	char* findPointerTo(const Index &I) const;
	void load(bool raw=false);
	void normalize();
	void print() const;
	void print(Index I);
	void set(const Index &I, const void *value, GLenum type);
	void write(const string &filename, int every=1);
protected:
	void checkIndex(const Index &I) const;
	void get(const Index &I, void *&value) const;
	void initDimensions();
	void initTypeBlock();
	void normalizeAsUnsignedShort();
	void readData();
private:
	DatasetHeader header;
	GLenum type;
	int block, length;
	int width, height, depth, widthTimesHeight;
	void *data;
};

/** @return Number of bytes in one sample. */
inline int Dataset::getBlock() const {return block;}

/** @return Pointer to the start of all the data. */
inline void* Dataset::getData() {return data;}

/** @return Path to the file the dataset was loaded from. */
inline string Dataset::getFilename() const {return header.getFilename();}

/** @return Size in memory of the data. */
inline GLint Dataset::getFootprint() const {return length * block;}

/** @return Header as read from the file. */
inline DatasetHeader Dataset::getHeader() const {return header;}

/** @return Highest value according to the header. */
inline int Dataset::getHigh() const {return header.getHigh();}

/** @return Lowest value according to the header. */
inline int Dataset::getLow() const {return header.getLow();}

/** @return Number of total samples in the dataset. */
inline int Dataset::getLength() const {return length;}

/** @return Maximum possible value according to the header. */
inline int Dataset::getMax() const {return header.getMax();}

/** @return Minimum possible value according to the header. */
inline int Dataset::getMin() const {return header.getMin();}

/** Currently, the return value will be one of 
 *   - @c GL_UNSIGNED_BYTE,
 *   - @c GL_SHORT, or 
 *   - @c GL_UNSIGNED_SHORT, or 
 *   - @c GL_FLOAT,
 * 
 * which can then be used in a @c switch statement.
 * 
 * @return Enumeration representing the type of the data.
 */
inline GLenum Dataset::getType() const {return type;}

/** @return Number of samples in the X direction. */
inline int Dataset::getWidth() const {return width;}

/** @return Number of samples in the Y direction. */
inline int Dataset::getHeight() const {return height;}

/** @return Number of samples in the Z direction. */
inline int Dataset::getDepth() const {return depth;}

/** Prints the header of the dataset. */
inline void Dataset::print() const {header.print();}


/** Utility for viewing a dataset. */
class DatasetViewer {
public:
	void draw();
	void goToNext();
	void goToPrevious();
	static void onDisplay(void);
	static void onMouse(int button, int state, int x, int y);
	static void onSpecial(int key, int x, int y);
	void setDataset(Dataset *dataset);
	void start();
private:
	Dataset *dataset;
	GLenum type;
	int slice, width, height, depth;
	static DatasetViewer *instance;
};



#endif
