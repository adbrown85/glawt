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
	producer.open(&scene, Command::OPEN, "input/fullscreen.xml");
	scene.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Producer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

