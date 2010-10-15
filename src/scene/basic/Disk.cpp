/*
 * Disk.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Disk.hpp"


ShapeTraits Disk::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = 12 + 2;
	traits.mode = GL_TRIANGLE_FAN;
	traits.usage = GL_STATIC_DRAW;
	traits.attributes.push_back("MCVertex");
	traits.attributes.push_back("MCNormal");
	return traits;
}


void Disk::updateBuffer() {
	
	updateBufferPoints();
	updateBufferNormals();
}


void Disk::updateBufferPoints() {
	
	GLfloat (*P)[3];
	int i;
	list<Vector> points;
	list<Vector>::iterator it;
	
	// Calculate
	points = Math::computeCircle(0.5, getCount()-2);
	points.push_front(Vector(0,0,0,1));
	points.push_back(Vector(0.5,0,0,1));
	
	// Fill array
	P = new GLfloat[getCount()][3];
	for (it=points.begin(); it!=points.end(); ++it) {
		i = distance(points.begin(), it);
		for (int j=0; j<3; ++j) {
			P[i][j] = (*it)[j];
		}
	}
	
	// Send to buffer
	setBufferData("MCVertex", P);
	delete[] P;
}


void Disk::updateBufferNormals() {
	
	GLfloat (*N)[3];
	
	// Fill array
	N = new GLfloat[getCount()][3];
	for (int i=0; i<(int)getCount(); ++i) {
		N[i][0] = 0.0;
		N[i][1] = 0.0;
		N[i][2] = 1.0;
	}
	
	// Send to buffer
	setBufferData("MCNormal", N);
	delete[] N;
}

