/*
 * Log.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Log.hpp"
using System::glog;


/* Fake to test log listener */
class FakeLogListener : public LogListener {
public:
	virtual void onLogUpdate(const string &text);
};
void FakeLogListener::onLogUpdate(const string &text) {
	cout << "Log updated!" << endl;
}


int main(int argc, char *argv[]) {
	
	Log::iterator it;
	
	// Start
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Log" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	
	// Test
	clog.addListener(new FakeLogListener());
	glog << "This is a message!" << endl;
	glog << "This is a message with a " << 1.5 << endl;
	glog << "This is a message with a " << 1 << endl;
	
	for (it=log.begin(); it!=log.end(); ++it) {
		cout << "  " << *it << endl;
	}
	
	// Finish
	cout << endl;
	cout << "****************************************" << endl;
	cout << "Log" << endl;
	cout << "****************************************" << endl;
	cout << endl;
	return 0;
}

