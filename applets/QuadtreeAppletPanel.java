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
	
	DisplayPanel displayPanel;
	QuadtreeAppletSidePanel sidePanel;
	QuadtreeAppletScene scene;
	
	
	public QuadtreeAppletPanel(InputStream stream)
	                           throws FileNotFoundException {
		
		super();
		setLayout(new BoxLayout(this, BoxLayout.LINE_AXIS));
		
		// Make scene
		scene = new QuadtreeAppletScene();
		scene.ray = new Ray(new Point(10,10), new Vector2D(1.0,1.0));
		scene.volume = new Volume(200, new Point(320,240), stream);
		
		// Add components
		sidePanel = new QuadtreeAppletSidePanel(scene);
		add(sidePanel);
		displayPanel = new DisplayPanel(640, 480);
		displayPanel.add(scene.volume);
		displayPanel.add(scene.ray);
		scene.addActionListener(displayPanel);
		add(displayPanel);
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

