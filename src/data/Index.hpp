/*
 * Index.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef INDEX_HPP
#define INDEX_HPP
#include <cstdlib>
#include <iostream>
using namespace std;


/**
 * @ingroup data
 * @brief
 *     Location in a three-dimensional array.
 */
class Index {
	
	public :
		
		int i, j, k;
		
		Index();
		Index(int i,
		      int j,
		      int k);
		Index& operator=(const Index &B);
		void set(int value);
		
		friend ostream& operator<<(ostream &stream,
		                           const Index &index);
		friend Index operator+(const Index &A,
		                       const Index &B);
};


inline Index::Index() {
	
	this->i = 0;
	this->j = 0;
	this->k = 0;
}


inline Index::Index(int i,
                    int j,
                    int k) {
	
	this->i = i;
	this->j = j;
	this->k = k;
}


inline void Index::set(int value) {
	
	this->i = value;
	this->j = value;
	this->k = value;
}


inline Index& Index::operator=(const Index &B) {
	
	this->i = B.i;
	this->j = B.j;
	this->k = B.k;
	return *this;
}


inline ostream& operator<<(ostream &stream,
                           const Index &index) {
	
	stream << '(' << index.i
	       << ',' << index.j
	       << ',' << index.k
	       << ')';
	return stream;
}


inline Index operator+(const Index &A,
                       const Index &B) {
	
	return Index(A.i+B.i, A.j+B.j, A.k+B.k);
}


#endif
