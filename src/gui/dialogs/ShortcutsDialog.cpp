/*
 * ShortcutsDialog.cpp
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#include "ShortcutsDialog.hpp"
#ifdef HAVE_GTK


ShortcutsDialog::ShortcutsDialog(Gtk::Window *window,
                                 list<Control*> &controls) : 
                                 Dialog("Shortcuts",*window,true) {
	
	// Make tree
	build(controls);
	view.set_model(tree.getModel());
	view.append_column("Trigger", tree.columns.key);
	view.append_column("Command", tree.columns.value);
	view.expand_all();
	view.set_rules_hint(true);
	
	// Make scroller
	scroller.add(view);
	scroller.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
	scroller.set_size_request(300, 400);
	
	// Pack
	get_vbox()->pack_start(scroller);
	add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all_children();
}


void ShortcutsDialog::build(list<Control*> &controls) {
	
	list<Control*>::iterator it;
	
	for (it=controls.begin(); it!=controls.end(); ++it) {
		buildFromControl(*it);
	}
}


void ShortcutsDialog::buildFromControl(Control *control) {
	
	std::map<Combo,Binding> bindings;
	std::map<Combo,Binding>::iterator it;
	pair<string,string> couple;
	
	bindings = control->getBindings();
	for (it=bindings.begin(); it!=bindings.end(); ++it) {
		couple = Text::split(it->second.toString(), ' ');
		tree.append(couple.first, Text::trim(couple.second, "\'"));
	}
}


#endif // HAVE_GTK

