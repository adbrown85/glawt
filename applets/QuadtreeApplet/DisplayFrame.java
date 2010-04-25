/*
 * DisplayFrame.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import javax.swing.*;




public class DisplayFrame extends JFrame {
	
	DisplayPanel displayPanel;
	JFrame frame;
	
	
	public DisplayFrame(String title) {
		
		super(title);
		
		init(640, 480);
	}
	
	
	public DisplayFrame(String title,
	                    int width,
	                    int height) {
		
		super(title);
		
		init(width, height);
	}
	
	
	/**
	 * Adds a %Drawable item to the %DisplayFrame.
	 */
	public void add(Drawable drawable) {
		
		displayPanel.add(drawable);
	}
	
	
	private void init(int width,
	                  int height) {
		
		displayPanel = new DisplayPanel(width, height);
	}
	
	
	/**
	 * Starts the %DisplayFrame.
	 */
	public void start() {
		
		// Set the characteristics
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setResizable(false);
		
		// Pack and show
		getContentPane().add(displayPanel);
		pack();
		setVisible(true);
	}
	
	
	
	/**
	 * Test for %DisplayFrame.
	 */
	public static void main(String[] args) {
		
		DisplayFrame display;
		
		// Test
		display = new DisplayFrame("DisplayFrame", 640, 480);
		display.start();
	}
}

