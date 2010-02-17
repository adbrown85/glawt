/*
 * Point.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import java.lang.IndexOutOfBoundsException;




/**
 * Container for an X,Y coordinate.
 */
public class Point implements Drawable {
	
	private static final int DEFAULT_WIDTH=6;
	
	public double x, y;
	public int width;
	private Stroke stroke;
	
	
	public Point() {
		
		init(0.0, 0.0);
	}
	
	
	public Point(double x,
	             double y) {
		
		init(x, y);
	}
	
	
	public Point(Object[] values) {
		
		set(values);
		init(x, y);
	}
	
	
	public Point(Point point) {
		
		init(point.x, point.y);
	}
	
	
	public static Point add(Point A,
	                        double b) {
		
		return new Point(A.x+b, A.y+b);
	}
	
	
	public static Point add(Point A,
	                        Point B) {
		
		Point C = new Point();
		
		// Add components
		C.x = A.x + B.x;
		C.y = A.y + B.y;
		return C;
	}
	
	
	public static Point add(Point A,
	                        Vector2D B) {
		
		Point C = new Point();
		
		// Add components
		C.x = A.x + B.x;
		C.y = A.y + B.y;
		return C;
	}
	
	
	public void addActionListener(ActionListener listener) {
		
	}
	
	
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		double halfWidth;
		int x, y;
		
		// Find coordinates
		halfWidth = (double)width * 0.5;
		x = (int)(this.x - halfWidth + 0.5);
		y = (int)(dimension.height - this.y - halfWidth + 0.5);
		
		// Draw
		graphic.setColor(Color.BLACK);
		if (stroke != null) {
			graphic.setStroke(stroke);
			graphic.drawOval(x, y, width, width);
		} else {
			graphic.fillOval(x, y, width, width);
		}
	}
	
	
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
	
	
	public void init(double x,
	                 double y) {
		
		this.x = x;
		this.y = y;
		setWidth(DEFAULT_WIDTH);
		stroke = null;
	}
	
	
	public void set(Object[] array) {
		
		x = ((Number)array[0]).doubleValue();
		y = ((Number)array[1]).doubleValue();
	}
	
	
	public void setWidth(int width) {
		
		this.width = width;
	}
	
	
	public void setStroked() {
		
		stroke = new BasicStroke();
	}
	
	
	public static Point subtract(Point A,
	                             double b) {
		
		return new Point(A.x-b, A.y-b);
	}
	
	
	public static Point subtract(Point A,
	                             Point B) {
		
		return new Point(A.x-B.x, A.y-B.y);
	}
	
	
	public void print() {
		
		System.out.println(toString());
	}
	
	
	public Double[] toArray() {
		
		Double[] array;
		
		array = new Double[2];
		array[0] = x;
		array[1] = y;
		return array;
	}
	
	
	public String toString() {
		
		return String.format("[%.2f %.2f]", x, y);
	}
	
	
	public static void main(String[] args) {
		
		DisplayFrame display;
		Point point;
		
		// Test
		point = new Point(320, 240);
		point.print();
		
		// Display
		display = new DisplayFrame("Point", 640, 480);
		display.add(point);
		display.start();
	}
}

