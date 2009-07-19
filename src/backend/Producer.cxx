/*
 * Producer.cxx
 *
 * Author
 *     Andy Brown <andybrown85@gmail.com>
 */
#include <iostream>
#include "Producer.hpp"
#include "Scene.hpp"
using namespace std;



/**
 * Simple test program.
 */
int main(int argc, char *argv[]) {
	
	Scene scene;
	Producer producer;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Producer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	producer.open(&scene, Command::OPEN, "../../input/scene.xml");
	scene.print();
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Producer" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}
