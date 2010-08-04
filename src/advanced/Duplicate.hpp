/*
 * Duplicate.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef DUPLICATE_HPP
#define DUPLICATE_HPP
#include "common.h"
#include "Node.hpp"
#include "Group.hpp"
using namespace std;


/** @brief Simple reuse of a group.
 * 
 * Should only be used if the group includes the Program node that renders 
 * everything.  Otherwise, use Instance.
 * 
 * @note Duplicate cannot be given any children in the XML file as they 
 * will not be destroyed.  They would also not be visible in the Inspector 
 * widget.
 * 
 * @see Instance
 * @ingroup advanced
 */
class Duplicate : public Node {
public:
	Duplicate(const Tag &tag);
	virtual bool areChildrenDestroyable() const;
	virtual bool areChildrenPrintable() const;
	virtual void associate();
	virtual void relink();
	virtual string toString() const;
protected:
	void findGroup();
	void findChildren();
private:
	Group *group;
	string of;
};

inline bool Duplicate::areChildrenDestroyable() const {return false;}
inline bool Duplicate::areChildrenPrintable() const {return false;}




#endif
