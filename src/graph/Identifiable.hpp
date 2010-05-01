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
 * @ingroup graph
 * @brief
 *     Interface for an object that has a unique ID number.
 */
class Identifiable {
public:
	Identifiable();
	static Identifiable* findByID(unsigned int id);
	virtual unsigned int getID() const;
	string toString() const;
	
	class Comparator {
	public :
		bool operator()(const Identifiable &a,
		                const Identifiable &b);
		bool operator()(const Identifiable *a,
		                const Identifiable *b);
	};
private:
	unsigned int id;
	static unsigned int count;
	static vector<Identifiable*> ids;
};


inline bool Identifiable::Comparator::operator()(const Identifiable &a,
                                                 const Identifiable &b) {
	
	return a.getID() < b.getID();
}
inline bool Identifiable::Comparator::operator()(const Identifiable *a,
                                                 const Identifiable *b) {
	
	return a->getID() < b->getID();
}


#endif
