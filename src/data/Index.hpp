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
 * @brief Location in a three-dimensional array.
 */
class Index {
public:
	int i, j, k;
	Index();
	Index(int i, int j, int k);
	//Index& operator=(const Index &B);
	void set(int value);
	friend ostream& operator<<(ostream &stream, const Index &index);
	friend Index operator+(const Index &A, const Index &B);
};


inline Index::Index() : i(0), j(0), k(0) {}

inline Index::Index(int i, int j, int k) : i(i), j(j), k(k) {}

inline void Index::set(int v) {this->i = v; this->j = v; this->k = v;}


/*
inline Index& Index::operator=(const Index &B) {
	
	this->i = B.i;
	this->j = B.j;
	this->k = B.k;
	return *this;
}
*/


inline Index operator+(const Index &A, const Index &B) {
	
	return Index(A.i+B.i, A.j+B.j, A.k+B.k);
}


#endif
