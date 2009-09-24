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



class Index {
	
	
	public :
		
		int i, j, k;
		
		Index() {
			this->i = 0;
			this->j = 0;
			this->k = 0;
		}
		Index(int i,
		      int j,
		      int k) {
			this->i = i;
			this->j = j;
			this->k = k;
		}
		
		friend ostream& operator<<(ostream &stream,
		                           const Index &index) {
			stream << '(' << index.i
			       << ',' << index.j
			       << ',' << index.k
			       << ')';
			return stream;
		}
};


#endif
