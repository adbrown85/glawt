/*
 * Point.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.*;
import java.awt.geom.*;
import java.lang.IndexOutOfBoundsException;




/**
 * Container for an X,Y coordinate.
 */
public class Point implements Drawable {
	
	
	public double x, y;
	private Ellipse2D.Double ellipse;
	private final int DEFAULT_WIDTH = 6;
	private Stroke stroke;
	
	
	
	/**
	 * Creates a new %Point.
	 */
	public Point() {
		
		// Initialize
		this.x = 0.0;
		this.y = 0.0;
		setWidth(DEFAULT_WIDTH);
		stroke = null;
	}
	
	
	
	/**
	 * Creates a new %Point from two coordinates.
	 */
	public Point(double x,
	             double y) {
		
		// Initialize
		this.x = x;
		this.y = y;
		setWidth(DEFAULT_WIDTH);
		stroke = null;
	}
	
	
	
	/**
	 * Creates a new %Point from another %Point.
	 */
	public Point(Point point) {
		
		// Initialize
		this.x = point.x;
		this.y = point.y;
		setWidth(DEFAULT_WIDTH);
		stroke = null;
	}
	
	
	
	/**
	 * Adds two points together.
	 */
	public static Point add(Point A,
	                        Point B) {
		
		Point C = new Point();
		
		// Add components
		C.x = A.x + B.x;
		C.y = A.y + B.y;
		return C;
	}
	
	
	
	/**
	 * Adds a vector to a point.
	 */
	public static Point add(Point A,
	                        Vector2D B) {
		
		Point C = new Point();
		
		// Add components
		C.x = A.x + B.x;
		C.y = A.y + B.y;
		return C;
	}
	
	
	
	/**
	 * Draws the point in a graphic.
	 */
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		// Draw the ellipse
		if (stroke != null) {
			graphic.setStroke(stroke);
			graphic.draw(ellipse);
		} else {
			graphic.fill(ellipse);
		}
	}
	
	
	
	/**
	 * Returns a component of the %Point by its index.
	 * 
	 * @param i
	 *     Index of the component.
	 */
	public double get(int i) {
		
		switch (i) {
			case 0: 
				return x;
			case 1:
				return y;
			default:
				throw new IndexOutOfBoundsException("Out of bounds.");
		}
	}
	
	
	
	public void setWidth(int width) {
		
		double halfWidth;
		
		// Ellipse
		halfWidth = width * 0.5;
		ellipse = new Ellipse2D.Double(x-halfWidth, y-halfWidth, width, width);
	}
	
	
	
	public void setStroked() {
		
		stroke = new BasicStroke();
	}
	
	
	
	/**
	 * Prints the point.
	 */
	public void print() {
		
		System.out.println(toString());
	}
	
	
	
	/**
	 * Formats the point as a string.
	 */
	public String toString() {
		
		return String.format("[%.2f %.2f]", x, y);
	}
	
	
	
	/**
	 * Test for %Point.
	 */
	public static void main(String[] args) {
		
		Display display;
		Point point;
		
		// Start
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Point");
		System.out.println("****************************************");
		System.out.println();
		
		// Test
		point = new Point(10, 10);
		point.print();
		
		// Display
		display = new Display("Point", 640, 480);
		display.add(point);
		display.start();
		
		// Finish
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Point");
		System.out.println("****************************************");
		System.out.println();
	}
}

