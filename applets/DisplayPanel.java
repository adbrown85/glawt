/*
 * DisplayPanel.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.*;
import java.awt.event.*;
import java.util.Vector;
import javax.swing.*;




public class DisplayPanel extends Component
                          implements ActionListener {
	
	int width, height;
	Vector<Drawable> drawables;
	
	
	public DisplayPanel() {
		
		init(640, 480);
	}
	
	
	public DisplayPanel(int width,
	                    int height) {
		
		init(width, height);
	}
	
	
	public void actionPerformed(ActionEvent event) {
		
		String command;
		
		command = event.getActionCommand();
		if (command.equals("Update")) {
			repaint();
		}
	}
	
	
	/**
	 * Adds a %Drawable item to the %DisplayPanel.
	 */
	public void add(Drawable drawable) {
		
		// Store the item and register as listener
		drawables.add(drawable);
		drawable.addActionListener(this);
	}
	
	
	private void init(int width,
	                  int height) {
		
		this.width = width;
		this.height = height;
		drawables = new Vector<Drawable>();
		setPreferredSize(new Dimension(width, height));
	}
	
	
	/**
	 * Clears the panel and paints all the Drawable items.
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
	
	
	public static void main(String[] args) {
		
		DisplayPanel displayPanel;
		JFrame frame;
		
		// Display
		displayPanel = new DisplayPanel(640, 480);
		
		// Frame
		frame = new JFrame("DisplayPanel");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false);
		frame.add(displayPanel);
		frame.pack();
		frame.setVisible(true);
	}
}

