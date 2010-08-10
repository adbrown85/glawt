/*
 * Choose.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CHOOSE_HPP
#define CHOOSE_HPP
#include "common.h"
#include "Node.hpp"
#include "NodeInterfaces.hpp"
#include "NodeEvent.hpp"
#include "Branch.hpp"
using namespace std;


/** @brief Selects a branch to follow.
 * @ingroup advanced
 */
class Choose : public Node, public NodeNotifier {
public:
	Choose(const Tag &tag);
	virtual void associate();
	virtual void finalize();
	virtual bool setAttribute(pair<string,string> attribute);
	virtual string toString() const;
public:
	virtual string getChoice() const;
	virtual bool hasChoice() const;
	virtual void setChoice(const string &choice);
private:
	string choice;
	map<string,Branch*> branches;
};

/** @return Name of the branch that was chosen. */
inline string Choose::getChoice() const {return choice;}

/** @return True if @e choice is not empty. */
inline bool Choose::hasChoice() const {return !choice.empty();}


#endif
