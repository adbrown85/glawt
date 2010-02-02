/*
 * Display.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.*;
import java.util.Vector;
import javax.swing.*;




public class Display extends Component {
	
	
	Container pane;
	JFrame frame;
	int width, height;
	String title;
	Vector<Drawable> drawables;
	
	
	
	/**
	 * Creates a new %Display.
	 */
	public Display(String title,
	               int width,
	               int height) {
		
		// Initialize
		this.title = title;
		this.width = width;
		this.height = height;
		drawables = new Vector<Drawable>();
	}
	
	
	
	/**
	 * Adds a %Drawable item to the %Display.
	 */
	public void add(Drawable drawable) {
		
		// Store the item
		drawables.add(drawable);
	}
	
	
	
	/**
	 * Paints the %Display.
	 */
	public void paint(Graphics g) {
		
		Graphics2D graphic = (Graphics2D)g;
		
		// Clear
		graphic.setRenderingHint(RenderingHints.KEY_ANTIALIASING,
		                         RenderingHints.VALUE_ANTIALIAS_ON);
		graphic.setBackground(Color.WHITE);
		graphic.clearRect(0, 0, width, height);
		
		// Draw each drawable
		for (Drawable drawable : drawables) {
			drawable.draw(graphic, new Dimension(width, height));
		}
	}
	
	
	
	/**
	 * Starts the %Display.
	 */
	public void start() {
		
		// Make frame
		frame = new JFrame("Display");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false);
		
		// Pack and display
		pane = frame.getContentPane();
		pane.setPreferredSize(new Dimension(width, height));
		pane.add(this);
		frame.pack();
		frame.setVisible(true);
	}
	
	
	
	/**
	 * Test for %Display.
	 */
	public static void main(String[] args) {
		
		Display display;
		
		// Start
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Display");
		System.out.println("****************************************");
		System.out.println();
		
		// Test
		display = new Display("Display", 640, 480);
		display.start();
		
		// Finish
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Display");
		System.out.println("****************************************");
		System.out.println();
	}
}

