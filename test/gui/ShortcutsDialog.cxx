/*
 * ShortcutsDialog.cxx
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ShortcutsDialog.hpp"
#include <gtkmm/main.h>
#include <gtkmm/window.h>
#include "Keyboard.hpp"
#include "Mouse.hpp"


class FakeCanvas : public Canvas {
public:
	virtual void flush() {}
	virtual void refresh() {}
	virtual void primeStart() {}
	virtual void primeFinish() {}
	virtual void setAutomaticallyRefresh(bool automaticRefresh) {}
	virtual void write(const string &text, int x=15, int y=30) {}
};


class ShortcutsDialogTest {
public:
	void setUp();
	void testShow();
	void onButtonClicked();
private:
	ShortcutsDialog *dialog;
	Gtk::Button button;
	Gtk::Window window;
};


void ShortcutsDialogTest::setUp() {
	
	Delegate *delegate;
	list<Control*> controls;
	Scene *scene;
	Canvas *canvas;
	
	// Make fakes
	scene = new Scene();
	canvas = new FakeCanvas();
	delegate = new Delegate(scene, canvas);
	
	// Make dialog
	controls.push_back(new Mouse(delegate));
	controls.push_back(new Keyboard(delegate));
	dialog = new ShortcutsDialog(&window, controls);
	
	// Make button
	button.set_label("Show");
	button.signal_clicked().connect(
		sigc::mem_fun(*this, &ShortcutsDialogTest::onButtonClicked)
	);
	
	// Pack
	window.set_title("ShortcutsDialog Test");
	window.add(button);
	window.show_all();
}


void ShortcutsDialogTest::testShow() {
	
	Gtk::Main::run(window);
}


void ShortcutsDialogTest::onButtonClicked() {
	
	dialog->run();
	dialog->hide();
}


int main(int argc, char *argv[]) {
	
	Gtk::Main kit(argc, argv);
	ShortcutsDialogTest test;
	
	// Test
	test.setUp();
	test.testShow();
	
	// Start
	return 0;
}

