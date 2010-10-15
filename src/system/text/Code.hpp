/*
 * Code.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef CODE_HPP
#define CODE_HPP
#include "common.h"
using namespace std;


/* Line of code. */
struct CodeLine {
	string filename, text;
	int number;
};

/** @brief Source code loaded from multiple files.
 * @ingroup system
 */
class Code {
public:
	typedef vector<CodeLine>::iterator iterator;
public:
	void add(const CodeLine &line);
	void add(const string &filename, int number, const string &text);
	iterator begin();
	iterator end();
	void clear();
public:    // Accessors
	size_t size() const;
	CodeLine getLine(int number) const;
private:
	vector<CodeLine> lines;
};

/** @return Iterator to the beginning of the code lines. */
inline Code::iterator Code::begin() {return lines.begin();}

/** @return Iterator to the end of the code lines. */
inline Code::iterator Code::end() {return lines.end();}

/** Clears all the lines stored. */
inline void Code::clear() {lines.clear();}

/** @return Number of lines stored. */
inline size_t Code::size() const {return lines.size();}

/** @return Line of code at index equal to @e number. */
inline CodeLine Code::getLine(int number) const {return lines[number];}



#endif
