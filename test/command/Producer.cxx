/*
 * Producer.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include <iostream>
#include "Producer.hpp"
#include "Scene.hpp"
using namespace std;


/**
 * Simple test program.
 */
int main(int argc,
         char *argv[]) {
	
	Producer producer;
	Scene scene;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Producer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	try {
		producer.open(&scene, Command::OPEN, "Producer.xml");
		scene.print();
	} catch (Exception &e) {
		cerr << e << endl;
	}
	
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Producer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

