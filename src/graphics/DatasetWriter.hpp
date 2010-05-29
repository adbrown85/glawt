/*
 * DatasetWriter.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DATASETWRITER_HPP
#define DATASETWRITER_HPP
#include "common.h"
#include "Dataset.hpp"
using namespace std;
using System::glog;


/** @brief Creates a dataset from a text file or another dataset.
 * 
 * The text file should follow the basic form of a VLB file, except the data is 
 * human readable.  In fact, the header is exactly the same, and DatasetHeader 
 * is even used to process it.  The data meanwhile is read in one slice at a 
 * time from front to back.  Each slice starts with the bottom left row and 
 * then proceeds upwards through the rows.  Each value should be separated by 
 * spaces, and line breaks do not matter within the data section, so feel free 
 * to format the data as you wish.  Data is written out as unsigned bytes with 
 * no spaces.
 * 
 * @note Currently the only type supported is <i>unit8</i> (unsigned bytes).
 * 
 * @ingroup graphics
 * @see Dataset
 */
class DatasetWriter {
public:
	DatasetWriter();
	string getInput() const;
	string getOutput() const;
	int getJump() const;
	void setInput(const string &filename);
	void setOutput(const string &filename);
	void setJump(int);
	void write();
protected:
	void writeHeader(ostream &file);
	void writeAsUnsignedShort(ofstream &file);
private:
	Dataset *dataset;
	DatasetHeader *header;
	string input, output;
	int jump;
	static float USHRT_SCALE;
};

inline string DatasetWriter::getInput() const {return input;}
inline string DatasetWriter::getOutput() const {return output;}
inline int DatasetWriter::getJump() const {return jump;}
inline void DatasetWriter::setInput(const string &i) {input = i;}
inline void DatasetWriter::setOutput(const string &o) {output = o;}
inline void DatasetWriter::setJump(int j) {jump = j;}


#endif
