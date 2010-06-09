/*
 * Menu.hpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef MENU_HPP
#define MENU_HPP
#include "common.h"
#include <gtkmm/menubar.h>
#include <gtkmm/stock.h>
#include <gtkmm/uimanager.h>
#include "Delegate.hpp"
#include "About.hpp"
using namespace std;
using Glib::RefPtr;


/** @brief Main menu.
 * @ingroup gui
 */
class Menu {
public:
	Menu(Delegate *delegate);
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
protected:
	void initActionGroup();
	void initUIManager();
private:
	Delegate *delegate;
	RefPtr<Gtk::UIManager> uiManager;
	RefPtr<Gtk::MenuBar> menuBar;
	RefPtr<Gtk::ActionGroup> actionGroup;
};


#endif
