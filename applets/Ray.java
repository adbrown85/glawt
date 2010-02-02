/*
 * Ray.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.*;
import java.util.Vector;




public class Ray implements Drawable {
	
	
	public Stroke stroke;
	public Point origin;
	public Vector2D direction;
	public Vector<Intersection> intersections;
	
	
	
	/**
	 * Creates a new %Ray.
	 */
	public Ray(Point origin,
	           Vector2D direction) {
		
		// Copy attributes
		this.origin = origin;
		this.direction = direction;
		
		// Initialize stroke
		stroke = new DottedStroke();
		intersections = new Vector<Intersection>();
	}
	
	
	
	public void addIntersection(Intersection intersection) {
		
		// Add to vector
		intersections.add(intersection);
	}
	
	
	
	public void addIntersectionPair(IntersectionPair intersectionPair) {
		
		// Add to vector
		if (intersectionPair.min != null) {
			intersections.add(intersectionPair.min);
		}
		if (intersectionPair.max != null) {
			intersections.add(intersectionPair.max);
		}
	}
	
	
	
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		Point end;
		
		// Draw origin
		origin.draw(graphic, dimension);
		
		// Draw line
		end = Point.add(origin, Vector2D.scale(direction, 1000));
		graphic.setStroke(stroke);
		graphic.drawLine((int)origin.x, (int)origin.y, (int)end.x, (int)end.y);
		
		// Draw intersections
		for (Intersection intersection : intersections) {
			intersection.draw(graphic, dimension);
		}
	}
	
	
	
	/**
	 * Gets a point along the ray.
	 * 
	 * @param t
	 *     Time of the point along the ray.
	 */
	public Point getPointAt(double t) {
		
		Vector2D offset;
		
		// Check if behind origin
		if (t < 0)
			return null;
		
		// Scale direction by t and add it to the origin
		offset = Vector2D.scale(direction, t);
		return Point.add(origin, offset);
	}
	
	
	
	/**
	 * Gets a point along the ray as an intersection.
	 * 
	 * @param t
	 *     Time of the point along the ray.
	 */
	public Intersection getIntersectionAt(double t) {
		
		// Check if behind origin
		if (t < 0)
			return null;
		
		// Return intersection
		return new Intersection(getPointAt(t), t);
	}
	
	
	
	/**
	 * Prints the %Ray's attributes.
	 */
	public void print() {
		
		System.out.println(toString());
	}
	
	
	
	/**
	 * Formats the %Ray's attributes as a string.
	 */
	public String toString() {
		
		return String.format("[ori:%s dir:%s]", origin, direction);
	}
	
	
	
	/**
	 * Tests the %Ray.
	 */
	public static void main(String[] args) {
		
		Display display;
		Ray ray;
		Point origin;
		Vector2D direction;
		
		// Start
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Ray");
		System.out.println("****************************************");
		System.out.println();
		
		// Create
		origin = new Point(10.0, 20.0);
		direction = new Vector2D(1.0, 1.0);
		ray = new Ray(origin, direction);
		ray.print();
		ray.addIntersection(ray.getIntersectionAt(100));
		
		// Show
		display = new Display("Ray", 640, 480);
		display.add(ray);
		display.start();
		
		// Finish
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Ray");
		System.out.println("****************************************");
		System.out.println();
	}
}

