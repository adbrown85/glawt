/*
 * Identifiable.hpp
 *     Interface featuring the getID method and a comparator for the STL.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __IDENTIFIABLE_HPP__
#define __IDENTIFIABLE_HPP__
#include <iostream>
#include <vector>
using std::ostream;
using std::vector;



/**
 * @interface Identifiable
 * @ingroup traits
 * @brief
 *     Interface for an object that has a unique ID number.
 */
class Identifiable {
	
	
	public :
		
		Identifiable();
		static Identifiable* findByID(unsigned int id);
		virtual unsigned int getID() const;
		friend ostream& operator<<(ostream& stream,
		                           const Identifiable& item);
		
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
