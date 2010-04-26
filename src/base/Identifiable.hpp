/*
 * Identifiable.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef IDENTIFIABLE_HPP
#define IDENTIFIABLE_HPP
#include <iostream>
#include <sstream>
#include <vector>
using namespace std;


/**
 * @interface Identifiable
 * @ingroup base
 * @brief
 *     Interface for an object that has a unique ID number.
 */
class Identifiable {
	
	public:
		
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
	
	private:
		
		unsigned int id;
		
		static unsigned int count;
		static vector<Identifiable*> ids;
};


#endif
