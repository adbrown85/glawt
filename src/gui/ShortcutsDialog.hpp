/*
 * ShortcutsDialog.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef SHORTCUTSDIALOG_HPP
#define SHORTCUTSDIALOG_HPP
#include "common.h"
#include <gtkmm/dialog.h>
#include <gtkmm/stock.h>
#include <gtkmm/window.h>
#include "AttributeTree.hpp"
#include "Control.hpp"
using namespace std;


/** @brief Dialog listing shortcuts.
 * @ingroup gui
 */
class ShortcutsDialog : public Gtk::Dialog {
public:
	ShortcutsDialog(Gtk::Window *window, list<Control*> &controls);
protected:
	void build(list<Control*> &controls);
	void buildFromControl(Control *control);
private:
	AttributeTree tree;
	Gtk::TreeView view;
	Gtk::ScrolledWindow scroller;
};


#endif
