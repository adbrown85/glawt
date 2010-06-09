/*
 * Combo.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef COMBO_HPP
#define COMBO_HPP
#include "common.h"
using namespace std;


/* Button or key with modifier and if trigger is up or down. */
struct Combo {
	int trigger, modifier, action;
};


/* Functor for comparing combos. */
class ComboComparator {
public:
	static bool compareTriggers(const Combo &A, const Combo &B);
	static bool compareModifiers(const Combo &A, const Combo &B);
	static bool compareActions(const Combo &A, const Combo &B);
	bool operator()(const Combo &A, const Combo &B);
};

/* Compares two combos by comparing their triggers, modifiers, and actions. */
inline bool ComboComparator::operator()(const Combo &A, const Combo &B) {
	return compareTriggers(A, B);
}

/* Compares the triggers of two combos. */
inline bool ComboComparator::compareTriggers(const Combo &A, const Combo &B) {
	if (A.trigger < B.trigger) {
		return true;
	} else if (A.trigger > B.trigger) {
		return false;
	} else {
		return compareModifiers(A, B);
	}
}

/* Compares the modifiers of two combos. */
inline bool ComboComparator::compareModifiers(const Combo &A, const Combo &B) {
	if (A.modifier < B.modifier) {
		return true;
	} else if (A.modifier > B.modifier) {
		return false;
	} else {
		return compareActions(A, B);
	}
}

/* Compares the actions of two combos. */
inline bool ComboComparator::compareActions(const Combo &A, const Combo &B) {
	if (A.action < B.action) {
		return true;
	} else if (A.action > B.action) {
		return false;
	} else {
		return false;
	}
}


/* Global function for comparing combos. */
bool operator<(const Combo &A, const Combo &B);


#endif
