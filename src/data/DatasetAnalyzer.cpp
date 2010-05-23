/*
 * DatasetAnalyzer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "DatasetAnalyzer.hpp"


void DatasetAnalyzer::findRange(Dataset *dataset,
                                GLushort &minimum,
                                GLushort &maximum) {
	
	GLushort *p, *end;
	
	// Check if loaded
	if (((GLushort*)dataset->getData()) == NULL) {
		throw Exception("[DatasetAnalyzer] Dataset needs to be loaded.");
	}
	
	// Initialize
	end = ((GLushort*)dataset->getData()) + dataset->getLength();
	minimum = dataset->getMax();
	maximum = dataset->getMin();
	
	// Look through 
	p = (GLushort*)dataset->getData();
	while (p < end) {
		minimum = min(minimum, (*p));
		maximum = max(maximum, (*p));
		p += 1;
	}
}



