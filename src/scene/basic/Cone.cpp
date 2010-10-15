/*
 * Cone.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Cone.hpp"


ShapeTraits Cone::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = 12 * 3;
	traits.mode = GL_TRIANGLES;
	traits.usage = GL_STATIC_DRAW;
	traits.attributes.push_back("MCVertex");
	traits.attributes.push_back("MCNormal");
	return traits;
}


void Cone::updateBuffer() {
	
	updateBufferPoints();
	updateBufferNormals();
}


void Cone::updateBufferPoints() {
	
	GLfloat (*P)[3];
	int i;
	list<Vector> points;
	list<Vector>::iterator curr, next;
	Vector tip(0,0,-1,1);
	
	// Initialize
	P = new GLfloat[getCount()][3];
	points = Math::computeCircle(0.5, getCount() / 3);
	points.push_back(Vector(0.5,0,0,1));
	
	// Fill array
	curr = points.begin();
	next = ++(points.begin());
	while (next != points.end()) {
		i = distance(points.begin(), curr) * 3;
		for (int j=0; j<3; ++j) {
			P[ i ][j] = (*curr)[j];
			P[i+1][j] = tip[j];
			P[i+2][j] = (*next)[j];
		}
		++curr;
		++next;
	}
	
	// Send to buffer
	setBufferData("MCVertex", P);
	delete[] P;
}


void Cone::updateBufferNormals() {
	
	GLfloat (*N)[3];
	int i;
	list<Vector> points;
	list<Vector>::iterator curr, next;
	Vector normal, tip(0,0,-1,1);
	
	// Initialize
	N = new GLfloat[getCount()][3];
	points = Math::computeCircle(0.5, getCount() / 3);
	points.push_back(Vector(0.5,0,0,1));
	
	// Fill array
	curr = points.begin();
	next = ++(points.begin());
	while (next != points.end()) {
		i = distance(points.begin(), curr) * 3;
		normal = cross(tip-*curr, *next-*curr);
		for (int j=0; j<3; ++j) {
			N[ i ][j] = normal[j];
			N[i+1][j] = normal[j];
			N[i+2][j] = normal[j];
		}
		++curr;
		++next;
	}
	
	// Send to buffer
	setBufferData("MCNormal", N);
	delete[] N;
}

