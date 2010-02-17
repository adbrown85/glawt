/*
 * IntersectionPair.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.*;
import java.awt.event.*;




/**
 * Container for a pair of Intersections.
 */
public class IntersectionPair implements Drawable {
	
	
	public Intersection min, max;
	
	
	
	/**
	 * Creates a new %IntersectionPair.
	 */
	public IntersectionPair() {
		
		// Initialize
		min = null;
		max = null;
	}
	
	
	
	/**
	 * Adds an %Intersection to the pair.
	 */
	public void add(Intersection intersection) {
		
		if (max == null) {
			max = intersection;
		} else {
			if (intersection.t > max.t) {
				min = max;
				max = intersection;
			} else {
				min = intersection;
			}
		}
	}
	
	
	public void addActionListener(ActionListener listener) {
		
	}
	
	
	
	/**
	 * Draws each Intersection in %IntersectionPair.
	 */
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		min.draw(graphic, dimension);
		max.draw(graphic, dimension);
	}
	
	
	
	/**
	 * Tests if the pair isn't storing any intersections.
	 */
	public boolean empty() {
		
		return min == null && max == null;
	}
}

