/*
 * Identifiable.hpp
 *     Interface featuring the getID method and a comparator for the STL.
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef __IDENTIFIABLE_HEADER__
#define __IDENTIFIABLE_HEADER__



/**
 * @interface Identifiable
 * @brief
 *     Interface for an object that has unique ID numbers.
 * @ingroup core
 */
class Identifiable {
	
	
	public :
		
		virtual int getID() const = 0;
		
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
};


#endif
