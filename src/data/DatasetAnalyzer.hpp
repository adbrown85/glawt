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
#include <utility>
#include <GL/gl.h>
#include "Dataset.hpp"
using namespace std;


/** @brief Finds attributes of a dataset.
 * @ingroup data
 */
class DatasetAnalyzer {
public:
	static void findRange(Dataset *dataset, GLushort &min, GLushort &max);
};

#endif
