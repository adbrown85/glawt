/*
 * Choose.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Choose.hpp"


/** Initializes attributes. */
Choose::Choose(const Tag &tag) : Node(tag) {
	
	tag.get("choice", choice, false, false);
}


/** Finds and stores all the branches.
 * 
 * @throw NodeException if any children are not branches.
 * @throw NodeException if two branches with the same name are found.
 */
void Choose::associate() {
	
	Branch *branch;
	map<string,Branch*>::iterator bi;
	Node::iterator ni;
	
	// Store branches
	for (ni=begin(); ni!=end(); ++ni) {
		branch = dynamic_cast<Branch*>((*ni));
		if (branch == NULL) {
			NodeException e(getTag());
			e << "[Choose] All children must be branch nodes.";
			throw e;
		}
		bi = branches.find(branch->getName());
		if (bi != branches.end()) {
			NodeException e(getTag());
			e << "[Choose] Branches under choose must have different names.";
			throw e;
		}
		branches[branch->getName()] = branch;
	}
}


/** Activates a choice if it's been set explicitly. */
void Choose::finalize() {
	
	// Activate choice
	if (hasChoice())
		setChoice(choice);
}


/** Set the choice using XML. */
bool Choose::setAttribute(pair<string,string> attribute) {
	
	// Choice
	if (Text::toLower(attribute.first) == "choice") {
		try {
			setChoice(attribute.second);
			return true;
		} catch (NodeException &e) {
			glog << e.getMessage() << endl;
			return false;
		}
	}
	
	// Other
	return false;
}


/** Follow the branch with the name equal to @e choice.
 *
 * @throw NodeException if choice is not the name of a branch.
 */
void Choose::setChoice(const string &choice) {
	
	map<string,Branch*>::iterator it;
	map<string,Branch*>::iterator bi;
	
	// Get the branch with the same name
	it = branches.find(choice);
	if (it == branches.end()) {
		NodeException e(getTag());
		e << "[Choose] Choice must be the name of a branch.";
		throw e;
	}
	
	// Store choice
	this->choice = choice;
	
	// Enable the branch and disable the others
	(it->second)->setFollow(true);
	for (bi=branches.begin(); bi!=it; ++bi)
		(bi->second)->setFollow(false);
	for (bi=++it; bi!=branches.end(); ++bi)
		(bi->second)->setFollow(false);
	
	// Finish
	fireEvent(NodeEvent(this, NodeEvent::MODIFY));
}


/** @return String comprised of the node's attributes. */
string Choose::toString() const {
	
	ostringstream stream;
	
	stream << Node::toString();
	if (!choice.empty())
		stream << " choice='" << choice << "'";
	return stream.str();
}

