/*
 * QuadtreeAppletPanel.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.InputStream;
import javax.swing.*;



/**
 * Main panel of the applet tying together the side and display panels.
 */
public class QuadtreeAppletPanel extends JPanel {
	
	private static final int DISPLAY_WIDTH=512;
	private static final int DISPLAY_HEIGHT=512;
	private static final int VOLUME_SIZE=350;
	
	DisplayPanel displayPanel;
	QuadtreeAppletSidePanel sidePanel;
	QuadtreeAppletScene scene;
	
	
	public QuadtreeAppletPanel(InputStream stream)
	                           throws FileNotFoundException {
		
		super();
		setLayout(new BoxLayout(this, BoxLayout.LINE_AXIS));
		
		// Initialize
		initScene(stream);
		initComponents();
	}
	
	
	public void initComponents() {
		
		// Side panel
		sidePanel = new QuadtreeAppletSidePanel(scene);
		add(sidePanel);
		
		// Display panel
		displayPanel = new DisplayPanel(DISPLAY_WIDTH, DISPLAY_HEIGHT);
		displayPanel.add(scene.volume);
		displayPanel.add(scene.ray);
		scene.addActionListener(displayPanel);
		add(displayPanel);
	}
	
	
	public void initScene(InputStream stream) {
		
		Point middle;
		
		// Find middle
		middle = new Point();
		middle.x = DISPLAY_WIDTH * 0.5;
		middle.y = DISPLAY_HEIGHT * 0.5;
		
		// Make scene
		scene = new QuadtreeAppletScene();
		scene.ray = new Ray(new Point(10,10), new Vector2D(1.0,1.0));
		scene.volume = new Volume(VOLUME_SIZE, middle, stream);
	}
	
	
	public static void main(String[] args) {
		
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				
				JFrame frame;
				QuadtreeAppletPanel panel;
				InputStream stream;
				
				try {
					
					// Create panel
					stream = new FileInputStream("volume.dat");
					panel = new QuadtreeAppletPanel(stream);
					
					// Show frame
					frame = new JFrame("QuadtreeAppletPanel");
					frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
					frame.setResizable(false);
					frame.setContentPane(panel);
					frame.pack();
					frame.setVisible(true);
				} 
				catch (FileNotFoundException e) {
					e.printStackTrace();
				}
			}
		});
	}
}

