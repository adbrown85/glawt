/*
 * Combo.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Combo.hpp"


/* Global function for comparing combos. */
bool operator<(const Combo &A, const Combo &B) {
	
	return ComboComparator::compareTriggers(A, B);
}

