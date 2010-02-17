/*
 * QuadtreeAppletScene.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;
import java.util.Vector;
import javax.swing.*;



/**
 * Scene containing the ray and volume.
 */
public class QuadtreeAppletScene {
	
	public Ray ray;
	public Volume volume;
	private Vector<ActionListener> listeners;
	
	
	public QuadtreeAppletScene() {
		
		listeners = new Vector<ActionListener>();
	}
	
	
	public void addActionListener(ActionListener listener) {
		
		listeners.add(listener);
	}
	
	
	public void fireUpdateEvent() {
		
		ActionEvent event;
		
		event = new ActionEvent(this, 0, "Update");
		for (ActionListener listener : listeners) {
			listener.actionPerformed(event);
		}
	}
}

