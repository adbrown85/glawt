/*
 * ButtonPanel.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;
import java.util.Vector;
import javax.swing.*;



/**
 * Horizontal panel of buttons.
 */
public class ButtonPanel extends JPanel
                         implements ActionListener {
	
	Vector<ActionListener> listeners;
	
	
	/**
	 * Creates a new panel of buttons.
	 */
	public ButtonPanel() {
		
		// Initialize
		super(new FlowLayout(FlowLayout.CENTER));
		listeners = new Vector<ActionListener>();
	}
	
	
	/**
	 * Creates a new panel of buttons.
	 */
	public ButtonPanel(int align) {
		
		// Initialize
		super(new FlowLayout(align));
		listeners = new Vector<ActionListener>();
	}
	
	
	/**
	 * Forwards events to its listeners.
	 */
	public void actionPerformed(ActionEvent event) {
		
		for (ActionListener listener : listeners) {
			listener.actionPerformed(event);
		}
	}
	
	
	public void addActionListener(ActionListener listener) {
		
		listeners.add(listener);
	}
	
	
	/**
	 * Adds a button and sets it up for events.
	 */
	public void addButton(String name) {
		
		JButton button;
		
		button = new JButton(name);
		button.addActionListener(this);
		button.setActionCommand(name);
		add(button);
	}
	
	
	public void lockHeight() {
		
		Dimension size;
		
		size = getPreferredSize();
		size.width = Integer.MAX_VALUE;
		setMaximumSize(size);
	}
	
	
	/**
	 * Test for ButtonPanel.
	 */
	public static void main(String[] args) {
		
		JFrame frame;
		ButtonPanel buttonPanel;
		
		// Start
		System.out.println();
		System.out.println("****************************************");
		System.out.println("ButtonPanel");
		System.out.println("****************************************");
		System.out.println();
		
		// Create button panel
		buttonPanel = new ButtonPanel();
		buttonPanel.addButton("Add");
		buttonPanel.addButton("Cancel");
		buttonPanel.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent event) {
				System.out.println(event.getActionCommand());
			}
		});
		
		// Create frame
		frame = new JFrame();
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(buttonPanel);
		frame.pack();
		frame.setVisible(true);
		
		// Finish
		System.out.println();
		System.out.println("****************************************");
		System.out.println("ButtonPanel");
		System.out.println("****************************************");
		System.out.println();
	}
}

