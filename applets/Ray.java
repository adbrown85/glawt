/*
 * Ray.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.*;
import java.awt.event.*;
import java.util.Vector;




public class Ray implements Drawable {
	
	public static final double ZERO_TOLERANCE=0.0000001;
	public static final Stroke stroke;
	
	public Point origin;
	public Vector2D direction;
	public Vector<Intersection> intersections;
	
	
	static {
		stroke = new DashedStroke(5.0);
	}
	
	
	public Ray(Point origin,
	           Vector2D direction) {
		
		this.origin = origin;
		this.direction = Vector2D.normalize(direction);
		intersections = new Vector<Intersection>();
	}
	
	
	public void addActionListener(ActionListener listener) {
		
	}
	
	
	public void addIntersectionAt(double t) {
		
		addIntersection(getIntersectionAt(t));
	}
	
	
	public void addIntersection(Intersection intersection) {
		
		// Add to vector
		if (intersection != null) {
			intersections.add(intersection);
		}
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
		
		// Draw line
		end = Point.add(origin, Vector2D.scale(direction, 1000));
		graphic.setColor(Color.BLUE);
		graphic.setStroke(stroke);
		graphic.drawLine((int)origin.x,
		                 (int)(dimension.height - origin.y),
		                 (int)end.x,
		                 (int)(dimension.height - end.y));
		
		// Draw origin
		origin.draw(graphic, dimension);
		
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
	 * Returns the time at a value on a given component.
	 */
	public double getTimeAt(int i,
	                        double value) {
		
		double di=direction.get(i), oi=origin.get(i);
		
		// If parallel to axis use infinity based on origin
		if (Math.abs(di) < ZERO_TOLERANCE) {
			if (value < oi) {
				return Double.NEGATIVE_INFINITY;
			} else if (value > oi) {
				return Double.POSITIVE_INFINITY;
			} else {
				return 0.0;
			}
		}
		
		// Otherwise just calculate normally
		return (value - oi) / di;
	}
	
	
	public boolean isDirectionZero(int i) {
		
		return Math.abs(direction.get(i)) < ZERO_TOLERANCE;
	}
	
	
	/**
	 * Prints the %Ray's attributes.
	 */
	public void print() {
		
		System.out.println(toString());
	}
	
	
	public void setDirection(Object[] values) {
		
		setDirection(new Vector2D(values));
	}
	
	
	public void setDirection(Vector2D direction) {
		
		this.direction = Vector2D.normalize(direction);
	}
	
	
	public void setOrigin(Object[] values) {
		
		setOrigin(new Point(values));
	}
	
	
	public void setOrigin(Point origin) {
		
		this.origin = new Point(origin);
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
		
		DisplayFrame display;
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
		display = new DisplayFrame("Ray");
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

