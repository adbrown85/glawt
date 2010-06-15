/*
 * Menu.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "Menu.hpp"


/** Initializes the ActionGroup and UIManager. */
Menu::Menu(Delegate *delegate,
           Gtk::Window *window,
           list<Control*> controls) {
	
	// Commands
	this->delegate = delegate;
	
	// Helpers
	this->window = window;
	shortcutsDialog = new ShortcutsDialog(window, controls);
	
	// UI
	initActionGroup();
	initUIManager();
}


/** Creates the ActionGroup and defines all the actions in it. */
void Menu::initActionGroup() {
	
	// Create
	actionGroup = Gtk::ActionGroup::create();
	
	// Submenus
	initActionGroupFile();
	initActionGroupEdit();
	initActionGroupView();
	initActionGroupHelp();
}


void Menu::initActionGroupFile() {
	
	// File menu
	actionGroup->add(Gtk::Action::create("MenuFile", "_File"));
	
	// Quit
	actionGroup->add(
		Gtk::Action::create(
			"FileQuit", Gtk::Stock::QUIT, "_Quit",
			"Quit the application"
		),
		sigc::mem_fun(*this, &Menu::onActionFileQuit)
	);
}


void Menu::initActionGroupEdit() {
	
	// Edit menu
	actionGroup->add(Gtk::Action::create("MenuEdit", "_Edit"));
	
	// Select all
	actionGroup->add(
		Gtk::Action::create(
			"EditSelectAll", Gtk::Stock::SELECT_ALL, "Select _All",
			"Select all objects"
		),
		sigc::mem_fun(*this, &Menu::onActionEditSelectAll)
	);
	
	// Deselect
	actionGroup->add(
		Gtk::Action::create("EditDeselect", "Deselect", "Deselect objects"),
		sigc::mem_fun(*this, &Menu::onActionEditDeselect)
	);
	
	// Hide
	actionGroup->add(
		Gtk::Action::create("EditHide", "_Hide", "Hide an object"),
		sigc::mem_fun(*this, &Menu::onActionEditHide)
	);
	actionGroup->add(
		Gtk::Action::create("EditShowAll", "_Show All", "Show all objects"),
		sigc::mem_fun(*this, &Menu::onActionEditShowAll)
	);
}


void Menu::initActionGroupView() {
	
	// View menu
	actionGroup->add(Gtk::Action::create("MenuView", "_View"));
	
	// Zoom in
	actionGroup->add(
		Gtk::Action::create(
			"ViewZoomIn", Gtk::Stock::ZOOM_IN, "Zoom _In",
			"Zoom in on the scene"
		),
		sigc::mem_fun(*this, &Menu::onActionViewZoomIn)
	);
	
	// Zoom out
	actionGroup->add(
		Gtk::Action::create(
			"ViewZoomOut", Gtk::Stock::ZOOM_OUT, "Zoom _Out",
			"Zoom out of the scene"
		),
		sigc::mem_fun(*this, &Menu::onActionViewZoomOut)
	);
	
	// Reset
	actionGroup->add(
		Gtk::Action::create(
			"ViewResetCamera", "_Reset",
			"Reset camera to original position and rotation."
		),
		sigc::mem_fun(*this, &Menu::onActionViewReset)
	);
	
	// Information
	actionGroup->add(
		Gtk::Action::create(
			"ViewInformation", "_Information",
			"Draw overlay with frames per second and memory footprint."
		),
		sigc::mem_fun(*this, &Menu::onActionViewInformation)
	);
}


void Menu::initActionGroupHelp() {
	
	// Help menu
	actionGroup->add(Gtk::Action::create("MenuHelp", "_Help"));
	
	// About
	actionGroup->add(
		Gtk::Action::create(
			"HelpAbout", "_About",
			"Information about the program."
		),
		sigc::mem_fun(*this, &Menu::onActionHelpAbout)
	);
	
	// Shortcuts
	actionGroup->add(
		Gtk::Action::create(
			"HelpShortcuts", "_Shortcuts",
			"Mouse and keyboard controls"
		),
		sigc::mem_fun(*this, &Menu::onActionHelpShortcuts)
	);
}


/** Creates the UIManager, adds the action group, and adds the UI. */
void Menu::initUIManager() {
	
	// Create
	uiManager = Gtk::UIManager::create();
	
	// Insert action group
	uiManager->insert_action_group(actionGroup);
	
	// Add UI
	string ui_info = 
		"<ui>"
		"  <menubar name='MenuBar'>"
		"    <menu action='MenuFile'>"
		"      <menuitem action='FileQuit' />"
		"    </menu>"
		"    <menu action='MenuEdit'>"
		"      <menuitem action='EditSelectAll' />"
		"      <menuitem action='EditDeselect' />"
		"      <separator />"
		"      <menuitem action='EditHide' />"
		"      <menuitem action='EditShowAll' />"
		"    </menu>"
		"    <menu action='MenuView'>"
		"      <menuitem action='ViewZoomIn' />"
		"      <menuitem action='ViewZoomOut' />"
		"      <menuitem action='ViewResetCamera' />"
		"      <separator />"
		"      <menuitem action='ViewInformation' />"
		"    </menu>"
		"    <menu action='MenuHelp'>"
		"      <menuitem action='HelpAbout' />"
		"      <menuitem action='HelpShortcuts' />"
		"    </menu>"
		"  </menubar>"
		"  <toolbar name='ToolBar'>"
		"    <toolitem action='FileQuit' />"
		"  </toolbar>"
		"</ui>";
	uiManager->add_ui_from_string(ui_info);
}


/** @return Pointer to a MenuBar widget. */
Gtk::Widget* Menu::getMenuBar() const {
	
	return uiManager->get_widget("/MenuBar");
}


/** Quits the application. */
void Menu::onActionFileQuit() {
	
	if (delegate != NULL) {
		delegate->run(Command::EXIT);
	}
}


/** Selects all the shapes. */
void Menu::onActionEditSelectAll() {
	
	if (delegate != NULL) {
		delegate->run(Command::SELECT_ALL);
		delegate->run(Command::REFRESH);
	}
}


void Menu::onActionEditHide() {
	
	if (delegate != NULL) {
		delegate->run(Command::HIDE);
		delegate->run(Command::REFRESH);
	}
}


void Menu::onActionEditShowAll() {
	
	if (delegate != NULL) {
		delegate->run(Command::SHOW_ALL);
		delegate->run(Command::REFRESH);
	}
}


/** Deselects all the shapes. */
void Menu::onActionEditDeselect() {
	
	if (delegate != NULL) {
		delegate->run(Command::DESELECT);
		delegate->run(Command::REFRESH);
	}
}


/** Zooms in on the scene. */
void Menu::onActionViewZoomIn() {
	
	if (delegate != NULL) {
		delegate->run(Command::ZOOM_IN, 2.0f);
		delegate->run(Command::REFRESH);
	}
}


/** Zooms out on the scene. */
void Menu::onActionViewZoomOut() {
	
	if (delegate != NULL) {
		delegate->run(Command::ZOOM_OUT, 2.0f);
		delegate->run(Command::REFRESH);
	}
}


/** Resets camera to original position and rotation. */
void Menu::onActionViewReset() {
	
	if (delegate != NULL) {
		delegate->run(Command::RESET);
		delegate->run(Command::REFRESH);
	}
}


void Menu::onActionViewInformation() {
	
	if (delegate != NULL) {
		delegate->run(Command::INFORMATION);
		delegate->run(Command::REFRESH);
	}
}


void Menu::onActionHelpAbout() {
	
	About::show(window);
}


void Menu::onActionHelpShortcuts() {
	
	shortcutsDialog->run();
	shortcutsDialog->hide();
}

