/*
 * DatasetAnalyzer.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "DatasetAnalyzer.hpp"



void DatasetAnalyzer::printHistogram() {
	
	map<float,size_t> histogram;
	map<float,size_t>::iterator it;
	ostringstream stream;
	int width=2;
	
	// Get the histogram
	histogram = findHistogram();
	
	// Print it
	if (dataset->getType() == GL_FLOAT) {
		cout << fixed << setprecision(2);
		width += 2;
	} else {
		cout << fixed << setprecision(0);
	}
	stream << dataset->getHigh();
	width += stream.str().length();
	cout << setw(width) << dataset->getLow() << " " << 0 << endl;
	for (it=histogram.begin(); it!=histogram.end(); ++it) {
		cout << setw(width) << it->first << " " << it->second << endl;
	}
	
	// Reset
	cout << resetiosflags(ios_base::floatfield);
	cout << setprecision(6);
}


map<float,size_t> DatasetAnalyzer::findHistogram() {
	
	pair<float,float> range;
	map<float,size_t> histogram;
	float subrange;
	
	// Setup subranges
	range = pair<float,float>(dataset->getLow(),dataset->getHigh());
	subrange = (range.second - range.first) / 10;
	for (int i=1; i<10; ++i) {
		histogram[range.first + (subrange * i)] = 0;
	}
	histogram[range.second] = 0;
	
	// Compute the values
	switch (dataset->getType()) {
	case GL_UNSIGNED_SHORT:
		findHistogramAsUShort(histogram);
		break;
	default:
		throw Exception("[DatasetAnalyzer] Dataset type not supported.");
	}
	return histogram;
}


void DatasetAnalyzer::findHistogramAsUShort(map<float,size_t> &histogram) {
	
	GLushort *p, *end;
	float value;
	map<float,size_t>::iterator it;
	
	// Initialize
	end = ((GLushort*)dataset->getData()) + dataset->getLength();
	
	// Look through all the voxels
	p = (GLushort*)dataset->getData();
	while (p < end) {
		for (it=histogram.begin(); it!=histogram.end(); ++it) {
			value = (float)(*p);
			if (value <= (it->first)) {
				++(it->second);
				break;
			}
		}
		p += 1;
	}
}


void DatasetAnalyzer::printRange() {
	
	pair<float,float> range;
	
	range = findRange();
	cout << "  Low  " << range.first << endl;
	cout << "  High " << range.second << endl;
}


pair<float,float> DatasetAnalyzer::findRange() {
	
	pair<float,float> range;
	
	// Initialize
	range.first = dataset->getMax();
	range.second = dataset->getMin();
	
	// Compute based on type
	switch (dataset->getType()) {
	case GL_UNSIGNED_SHORT:
		findRangeAsUShort(range);
		break;
	default:
		throw Exception("[DatasetAnalyzer] Dataset type not supported.");
	}
	return range;
}


void DatasetAnalyzer::findRangeAsUShort(pair<float,float> &range) {
	
	GLushort *p, *end;
	
	// Initialize
	end = ((GLushort*)dataset->getData()) + dataset->getLength();
	
	// Look through all the voxels
	p = (GLushort*)dataset->getData();
	while (p < end) {
		range.first = std::min(range.first, (float)(*p));
		range.second = std::max(range.second, (float)(*p));
		p += 1;
	}
}



