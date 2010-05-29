/*
 * DatasetWriter.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "DatasetWriter.hpp"
float DatasetWriter::USHRT_SCALE=((float)1)/USHRT_MAX*UCHAR_MAX;


DatasetWriter::DatasetWriter() {
	
	jump = 1;
	dataset = NULL;
	header = NULL;
}


void DatasetWriter::write() {
	
	clock_t ticks;
	ofstream file;
	
	// Open the dataset
	dataset = new Dataset(input);
	dataset->load();
	
	// Make the header
	header = new DatasetHeader(dataset->getHeader());
	header->setType("uint8");
	header->setEndian("little");
	header->setLow(0);
	header->setHigh(UCHAR_MAX);
	header->setMin(0);
	header->setMax(UCHAR_MAX);
	header->setWidth(dataset->getWidth() / jump);
	header->setHeight(dataset->getHeight() / jump);
	header->setDepth(dataset->getDepth() / jump);
	
	// Write to file
	glog << "[DatasetWriter] Writing to '" << output << "'... ";
	ticks = clock();
	file.open(output.c_str(), ios_base::binary);
	writeHeader(file);
	switch (dataset->getType()) {
	case GL_UNSIGNED_SHORT:
		writeAsUnsignedShort(file);
	}
	
	// Finish
	file.close();
	delete dataset;
	delete header;
	dataset = NULL;
	header = NULL;
	glog << (((double)clock()-ticks)/CLOCKS_PER_SEC) << "s" << endl;
}


void DatasetWriter::writeHeader(ostream &file) {
	
	vector<string> comments;
	vector<string>::iterator it;
	
	// Descriptor and comments
	file << "VLIB.1" << endl;
	comments = header->getComments();
	for (it=comments.begin(); it!=comments.end(); ++it) {
		file << '#' << (*it) << endl;
	}
	
	// Details
	file << header->getWidth() << " " 
	     << header->getHeight() << " " 
	     << header->getDepth() << endl;
	file << header->getType() << endl;
	file << header->getEndian() << endl;
	file << header->getPitch().x << " " 
	     << header->getPitch().y << " "
	     << header->getPitch().z << endl;
	file << header->getMin() << " " << header->getMax() << endl;
	file << header->getLow() << " " << header->getHigh() << endl;
}


void DatasetWriter::writeAsUnsignedShort(ofstream &file) {
	
	GLubyte *slice;
	GLushort *p;
	int length, tally;
	
	// Initialize
	length = header->getWidth() * header->getHeight();
	slice = new GLubyte[length];
	
	// Write each slice to file
	for (int k=0; k<dataset->getDepth(); k+=jump) {
		tally = -1;
		for (int i=0; i<dataset->getHeight(); i+=jump) {
			p = (GLushort*)dataset->findPointerTo(Index(i, 0, k));
			for (int j=0; j<dataset->getWidth(); j+=jump) {
				slice[++tally] = (GLubyte)((float)(*(p+j)) * USHRT_SCALE);
			}
		}
		file.write(reinterpret_cast<char*>(slice), length);
	}
	delete[] slice;
}

