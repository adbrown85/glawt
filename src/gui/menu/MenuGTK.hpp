/*
 * MenuGTK.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MENUGTK_HPP
#define MENUGTK_HPP
#include "common.h"
#ifdef HAVE_GTK
#include <gtkmm/menubar.h>
#include <gtkmm/stock.h>
#include <gtkmm/uimanager.h>
#include "Delegate.hpp"
#include "About.hpp"
#include "ShortcutsDialog.hpp"
using namespace std;
using Glib::RefPtr;


/** @brief Main menu.
 * @ingroup gui
 */
class MenuGTK {
public:
	MenuGTK(Delegate *delegate, Gtk::Window *window, list<Control*> controls);
	Gtk::Widget* getMenuBar() const;
	void onActionFileQuit();
	void onActionEditHide();
	void onActionEditSelectAll();
	void onActionEditShowAll();
	void onActionEditDeselect();
	void onActionViewZoomIn();
	void onActionViewZoomOut();
	void onActionViewInformation();
	void onActionViewReset();
	void onActionHelpAbout();
	void onActionHelpShortcuts();
protected:
	void initActionGroup();
	void initActionGroupFile();
	void initActionGroupEdit();
	void initActionGroupView();
	void initActionGroupHelp();
	void initUIManager();
private:
	Delegate *delegate;
	RefPtr<Gtk::UIManager> uiManager;
	RefPtr<Gtk::MenuBar> menuBar;
	RefPtr<Gtk::ActionGroup> actionGroup;
	ShortcutsDialog *shortcutsDialog;
	Gtk::Window *window;
};


#endif // HAVE_GTK
#endif
