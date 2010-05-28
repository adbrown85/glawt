/*
 * Delegate.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Delegate.hpp"


class FakeCommandListener : public CommandListener {
public:
	virtual void onCommandEvent(int command);
};
void FakeCommandListener::onCommandEvent(int command) {
	cout << "FakeCommandListener::onCommandEvent(int)" << endl;
}


int main(int argc, char *argv[]) {
	
	Canvas *canvas;
	Scene scene;
	Delegate Delegate(&scene, canvas);
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Delegate" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Run
	cout << "Run commands:" << endl;
	Delegate.run(Command::COPY);
	Delegate.addListener(new FakeCommandListener(), Command::CUT);
	Delegate.run(Command::CUT);
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Delegate" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

