/*
 * BooleanXor.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "BooleanXor.hpp"


void BooleanXor::calculate() {
	
	// Check size
	if (extents.size() != 2) {
		NodeException e(tag);
		e << "[BooleanXor] Must use two shapes.";
		throw e;
	}
	
	// Calculate with two extents
	map<Shape*,Extent>::iterator it;
	for (it=extents.begin(); it!=extents.end(); ++it) {
		it->second.label = it->first->getID();
		cout << "Set " << it->second.label
		     << " to " << it->first->getID() << endl;
	}
	it = extents.begin();
	++it;
	calculate(extents.begin()->second, it->second);
}


void BooleanXor::calculate(Extent A, Extent B) {
	
	map<int,extent_list>::iterator it;
	Extent *l, *h;
	pair<Extent,Extent> result;
	
	// Initialize
	pieces.clear();
	pieces[A.label] = extent_list();
	pieces[B.label] = extent_list();
	l = &A;
	h = &B;
	
	cout << "A.label = " << A.label << endl;
	cout << "B.label = " << B.label << endl;
	
	// Split
	for (int i=0; i<3; ++i) {
		if (l->lower[i] > h->lower[i]) {
			swap(l, h);
		}
		if (h->lower[i] < l->upper[i]) {
			result = knife(*l, h->lower[i], i);
			it = pieces.find(l->label);
			it->second.push_back(result.first);
			*l = result.second;
			result = knife(*h, l->upper[i], i);
			it = pieces.find(h->label);
			it->second.push_back(result.second);
			*h = result.first;
		}
	}
}


pair<Extent,Extent> BooleanXor::knife(Extent &extent, float at, int on) {
	
	pair<Extent,Extent> result;
	
	result.first = extent;
	result.first.upper[on] = at;
	result.second = extent;
	result.second.lower[on] = at;
	return result;
}


ShapeTraits BooleanXor::getTraits() {
	
	ShapeTraits traits;
	
	traits.count = 72;
	traits.mode = GL_QUADS;
	traits.usage = GL_DYNAMIC_DRAW;
	traits.attributes.push_back("MCVertex");
	return traits;
}


void BooleanXor::initPoints() {
	
	Extent extent;
	int off;
	map<int,extent_list>::iterator pi;
	extent_list::iterator ei;
	
	if (isOverlapped()) {
		cout << "Shapes are overlapped." << endl;
		calculate();
		for (pi=pieces.begin(); pi!=pieces.end(); ++pi) {
			cout << pi->first << endl;
			for (ei=pi->second.begin(); ei!=pi->second.end(); ++ei) {
				cout << "  " << ei->lower << " " << ei->upper << endl;
				extent = *ei;
			}
		}
		pi = pieces.begin();
		++pi;
		off = 0;
		for (ei=pi->second.begin(); ei!=pi->second.end(); ++ei) {
			cout << "off=" << off << endl;
			cout << "id=" << ei->label << endl;
			toArray(points+off, ei->lower, ei->upper);
			off += 24;
		}
	} else {
		cout << "Shapes are not overlapped." << endl;
		toArray(points   , Vector(-0.3,-0.3,-0.1), Vector(-0.1,-0.1,+0.1));
		toArray(points+24, Vector(+0.1,+0.1,-0.1), Vector(+0.3,+0.3,+0.1));
		toArray(points+48, Vector(-0.1,-0.1,-0.1), Vector(+0.1,+0.1,+0.1));
	}
	
	
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(points), points);
}

