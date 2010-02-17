/*
 * Shape.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;



/**
 * Shape with a size, center, and origin.
 */
public class Shape implements Drawable {
	
	public BoundingBox boundingBox;
	public double size;
	public Point center;
	
	
	public Shape(double size,
	             Point center) {
		
		this.size = size;
		this.center = center;
		this.boundingBox = new BoundingBox(size, center);
	}
	
	
	public void addActionListener(ActionListener listener) {
		
	}
	
	
	public BoundsCheck check(Ray ray) {
		
		return boundingBox.check(ray);
	}
	
	
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		graphic.setColor(Color.BLACK);
		boundingBox.draw(graphic, dimension);
	}
	
	
	public BoundingBox getBoundingBox() {
		
		return boundingBox;
	}
	
	
	public void set(double size,
	                Point center) {
		
		this.size = size;
		this.center = new Point(center);
		this.boundingBox = new BoundingBox(size, center);
	}
	
	public String toString() {
		
		return String.format("size=%f, center=%s", size, center);
	}
	
	
	public static void main(String[] args) {
		
		Ray ray;
		BoundsCheck boundsCheck;
		Shape shape;
		DisplayFrame display;
		
		// Constructor
		shape = new Shape(40.0, new Point(80.0,90.0));
		System.out.println(shape);
		
		// Intersect
		ray = new Ray(new Point(9.0,10.0), new Vector2D(1.0,1.0));
		boundsCheck = shape.check(ray);
		System.out.println(boundsCheck);
		
		// Show
		display = new DisplayFrame("Shape", 640, 480);
		display.add(shape);
		display.add(ray);
		if (boundsCheck.isHit()) {
			ray.addIntersectionAt(boundsCheck.tEnter);
			ray.addIntersectionAt(boundsCheck.tLeave);
		}
		display.start();
	}
}

