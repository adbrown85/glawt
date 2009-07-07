/*
 * Tag.hpp
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#ifndef _TAG_HPP_
#define _TAG_HPP_
#include <iostream>
#include <map>
#include <string>
using std::map;
using std::ostream;
using std::string;



/**
 * @brief
 *     XML tag holding a map of attributes and their values.
 * @ingroup backend
 */
class Tag {
	
	
	public :
		
		bool closing;
		map<string,string> attributes;
		string name;
		
		Tag() {
			closing = false;
		}
		
		friend ostream& operator<<(ostream &stream, const Tag &tag) {
			
			map<string,string>::const_iterator ai;
			
			stream << tag.name;
			for (ai=tag.attributes.begin(); ai!=tag.attributes.end(); ++ai)
				stream << " [" << ai->first
				       << "," << ai->second 
					   << "]";
			return stream;
		}
};

#endif
