/*
 * MenuGTK.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "MenuGTK.hpp"
#ifdef HAVE_GTK


/** Initializes the ActionGroup and UIManager. */
MenuGTK::MenuGTK(Delegate *delegate,
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
void MenuGTK::initActionGroup() {
	
	// Create
	actionGroup = Gtk::ActionGroup::create();
	
	// Submenus
	initActionGroupFile();
	initActionGroupEdit();
	initActionGroupView();
	initActionGroupHelp();
}


void MenuGTK::initActionGroupFile() {
	
	// File menu
	actionGroup->add(Gtk::Action::create("MenuFile", "_File"));
	
	// Quit
	actionGroup->add(
		Gtk::Action::create(
			"FileQuit", Gtk::Stock::QUIT, "_Quit",
			"Quit the application"
		),
		sigc::mem_fun(*this, &MenuGTK::onActionFileQuit)
	);
}


void MenuGTK::initActionGroupEdit() {
	
	// Edit menu
	actionGroup->add(Gtk::Action::create("MenuEdit", "_Edit"));
	
	// Select all
	actionGroup->add(
		Gtk::Action::create(
			"EditSelectAll", Gtk::Stock::SELECT_ALL, "Select _All",
			"Select all objects"
		),
		sigc::mem_fun(*this, &MenuGTK::onActionEditSelectAll)
	);
	
	// Deselect
	actionGroup->add(
		Gtk::Action::create("EditDeselect", "Deselect", "Deselect objects"),
		sigc::mem_fun(*this, &MenuGTK::onActionEditDeselect)
	);
	
	// Hide
	actionGroup->add(
		Gtk::Action::create("EditHide", "_Hide", "Hide an object"),
		sigc::mem_fun(*this, &MenuGTK::onActionEditHide)
	);
	actionGroup->add(
		Gtk::Action::create("EditShowAll", "_Show All", "Show all objects"),
		sigc::mem_fun(*this, &MenuGTK::onActionEditShowAll)
	);
}


void MenuGTK::initActionGroupView() {
	
	// View menu
	actionGroup->add(Gtk::Action::create("MenuView", "_View"));
	
	// Zoom in
	actionGroup->add(
		Gtk::Action::create(
			"ViewZoomIn", Gtk::Stock::ZOOM_IN, "Zoom _In",
			"Zoom in on the scene"
		),
		sigc::mem_fun(*this, &MenuGTK::onActionViewZoomIn)
	);
	
	// Zoom out
	actionGroup->add(
		Gtk::Action::create(
			"ViewZoomOut", Gtk::Stock::ZOOM_OUT, "Zoom _Out",
			"Zoom out of the scene"
		),
		sigc::mem_fun(*this, &MenuGTK::onActionViewZoomOut)
	);
	
	// Reset
	actionGroup->add(
		Gtk::Action::create(
			"ViewResetCamera", "_Reset",
			"Reset camera to original position and rotation."
		),
		sigc::mem_fun(*this, &MenuGTK::onActionViewReset)
	);
	
	// Information
	actionGroup->add(
		Gtk::Action::create(
			"ViewInformation", "_Information",
			"Draw overlay with frames per second and memory footprint."
		),
		sigc::mem_fun(*this, &MenuGTK::onActionViewInformation)
	);
}


void MenuGTK::initActionGroupHelp() {
	
	// Help menu
	actionGroup->add(Gtk::Action::create("MenuHelp", "_Help"));
	
	// About
	actionGroup->add(
		Gtk::Action::create(
			"HelpAbout", "_About",
			"Information about the program."
		),
		sigc::mem_fun(*this, &MenuGTK::onActionHelpAbout)
	);
	
	// Shortcuts
	actionGroup->add(
		Gtk::Action::create(
			"HelpShortcuts", "_Shortcuts",
			"Mouse and keyboard controls"
		),
		sigc::mem_fun(*this, &MenuGTK::onActionHelpShortcuts)
	);
}


/** Creates the UIManager, adds the action group, and adds the UI. */
void MenuGTK::initUIManager() {
	
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
Gtk::Widget* MenuGTK::getMenuBar() const {
	
	return uiManager->get_widget("/MenuBar");
}


/** Quits the application. */
void MenuGTK::onActionFileQuit() {
	
	if (delegate != NULL) {
		delegate->run(Command::EXIT);
	}
}


/** Selects all the shapes. */
void MenuGTK::onActionEditSelectAll() {
	
	if (delegate != NULL) {
		delegate->run(Command::SELECT_ALL);
		delegate->run(Command::REFRESH);
	}
}


void MenuGTK::onActionEditHide() {
	
	if (delegate != NULL) {
		delegate->run(Command::HIDE);
		delegate->run(Command::REFRESH);
	}
}


void MenuGTK::onActionEditShowAll() {
	
	if (delegate != NULL) {
		delegate->run(Command::SHOW_ALL);
		delegate->run(Command::REFRESH);
	}
}


/** Deselects all the shapes. */
void MenuGTK::onActionEditDeselect() {
	
	if (delegate != NULL) {
		delegate->run(Command::DESELECT);
		delegate->run(Command::REFRESH);
	}
}


/** Zooms in on the scene. */
void MenuGTK::onActionViewZoomIn() {
	
	if (delegate != NULL) {
		delegate->run(Command::ZOOM_IN, 2.0f);
		delegate->run(Command::REFRESH);
	}
}


/** Zooms out on the scene. */
void MenuGTK::onActionViewZoomOut() {
	
	if (delegate != NULL) {
		delegate->run(Command::ZOOM_OUT, 2.0f);
		delegate->run(Command::REFRESH);
	}
}


/** Resets camera to original position and rotation. */
void MenuGTK::onActionViewReset() {
	
	if (delegate != NULL) {
		delegate->run(Command::RESET);
		delegate->run(Command::REFRESH);
	}
}


void MenuGTK::onActionViewInformation() {
	
	if (delegate != NULL) {
		delegate->run(Command::INFORMATION);
		delegate->run(Command::REFRESH);
	}
}


void MenuGTK::onActionHelpAbout() {
	
	About::show(window);
}


void MenuGTK::onActionHelpShortcuts() {
	
	shortcutsDialog->run();
	shortcutsDialog->hide();
}


#endif // HAVE_GTK

