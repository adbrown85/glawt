/*
 * WindowFactory.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WINDOWFACTORY_HPP
#define WINDOWFACTORY_HPP
#include "WindowGTK.hpp"
#include "WindowGLUT.hpp"
using namespace std;


/** @brief Utility for retrieving a window of correct toolkit.
 * @ingroup graphics
 */
class WindowFactory {
public:
	static Window* create();
};


#endif
