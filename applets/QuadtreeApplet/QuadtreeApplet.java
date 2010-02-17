/*
 * QuadtreeApplet.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import javax.swing.*;
import java.io.FileNotFoundException;
import java.io.InputStream;



/**
 * Quadtree applet showing traversal.
 */
public class QuadtreeApplet extends JApplet {
	
	
	public void init() {
		
		InputStream stream;
		
		try {
			stream = getClass().getResourceAsStream("volume.dat");
			setContentPane(new QuadtreeAppletPanel(stream));
		} catch (FileNotFoundException e) {
		}
	}
}

