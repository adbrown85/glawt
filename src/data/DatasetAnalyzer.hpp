/*
 * DatasetAnalyzer.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DATASETANALYZER_HPP
#define DATASETANALYZER_HPP
#include <cstdlib>
#include <iostream>
#include <string>
#include <iomanip>
#include <utility>
#include <GL/gl.h>
#include "Dataset.hpp"
using namespace std;


/** @brief Finds information about the values in a dataset.
 * @ingroup data
 */
class DatasetAnalyzer {
public:
	map<float,size_t> findHistogram();
	pair<float,float> findRange();
	void printHistogram();
	void printRange();
	void setDataset(Dataset *dataset);
protected:
	void findHistogramAsUShort(map<float,size_t> &histogram);
	void findRangeAsUShort(pair<float,float> &range);
private:
	Dataset *dataset;
};

/** Assigns the dataset the analyzer will work with. */
inline void DatasetAnalyzer::setDataset(Dataset *d) {dataset = d;}

#endif
