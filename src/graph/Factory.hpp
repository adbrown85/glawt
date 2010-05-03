/*
 * Factory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef FACTORY_HPP
#define FACTORY_HPP
#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "FileUtility.hpp"
#include "Node.hpp"
#include "Parser.hpp"
#include "Tag.hpp"
using namespace std;


/**
 * Creator function.
 */
typedef Node* (*creator_t)(const Tag &tag);


/**
 * @ingroup graph
 * @brief Creates nodes from XML tags.
 */
class Factory {
public:
	static Node* create(const Tag &tag,
	                    const string &xmlFilename="");
	static Node* create(const string &text,
	                    const string &xmlFilename="");
	static void install(const string &name,
	                    creator_t creator);
protected:
	static Tag filter(Tag tag,
	                  const string &xmlFilename);
private:
	static map<string,creator_t> creators;
};


#endif
