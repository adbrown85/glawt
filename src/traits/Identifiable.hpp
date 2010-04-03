/*
 * Identifiable.hpp
 *     Interface featuring the getID method and a comparator for the STL.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef IDENTIFIABLE_HPP
#define IDENTIFIABLE_HPP
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


/**
 * @interface Identifiable
 * @ingroup traits
 * @brief
 *     Interface for an object that has a unique ID number.
 */
class Identifiable {
	
	public :
		
		Identifiable();
		virtual unsigned int getID() const;
		string toString() const;
		
		static Identifiable* findByID(unsigned int id);
		
		class Comparator {
			public :
				bool operator()(const Identifiable &a,
				                const Identifiable &b) {
					return a.getID() < b.getID();
				}
				bool operator()(const Identifiable *a,
				                const Identifiable *b) {
					return a->getID() < b->getID();
				}
		};
	
	private :
		
		unsigned int id;
		
		static unsigned int count;
		static vector<Identifiable*> ids;
};


#endif
