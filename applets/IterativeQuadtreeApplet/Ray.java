/*
 * Ray.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.*;




public class Ray extends BasicDrawable
                 implements Drawable {
	
	private static final double ZERO_TOLERANCE=0.0000001;
	private static final int ORIGIN_WIDTH=12;
	private static final double STROKE_WIDTH=5.0;
	
	public Point origin;
	public Vector2D direction;
	
	
	public Ray(Point origin,
	           Vector2D direction) {
		
		super(Color.BLUE, new DashedStroke(STROKE_WIDTH));
		
		// Initialize
		this.origin = origin;
		this.direction = Vector2D.normalize(direction);
	}
	
	
	public Ray(Ray ray) {
		
		super(Color.BLUE, new DashedStroke(STROKE_WIDTH));
		
		// Copy
		this.origin = new Point(ray.origin);
		this.direction = new Vector2D(ray.direction);
	}
	
	
	public void addIntersectionAt(double t) {
		
		addIntersection(getIntersectionAt(t));
	}
	
	
	public void addIntersection(Intersection intersection) {
		
		// Add to vector
		if (intersection != null) {
			addAccessory(intersection);
		}
	}
	
	
	public void addIntersectionPair(IntersectionPair intersectionPair) {
		
		// Add to vector
		if (intersectionPair.min != null) {
			addAccessory(intersectionPair.min);
		}
		if (intersectionPair.max != null) {
			addAccessory(intersectionPair.max);
		}
	}
	
	
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		Point end;
		
		// Draw line
		end = Point.add(origin, Vector2D.scale(direction, 1000));
		graphic.setColor(color);
		graphic.setStroke(stroke);
		graphic.drawLine((int)origin.x,
		                 (int)(dimension.height - origin.y),
		                 (int)end.x,
		                 (int)(dimension.height - end.y));
		
		// Draw origin and accessories
		origin.setWidth(ORIGIN_WIDTH);
		origin.draw(graphic, dimension);
		super.draw(graphic, dimension);
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
	
	
	public double getValueAt(int i,
	                         double t) {
		
		return origin.get(i) + direction.get(i) * t;
	}
	
	
	public boolean isDirectionZero(int i) {
		
		return Math.abs(direction.get(i)) < ZERO_TOLERANCE;
	}
	
	
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
	
	
	public String toString() {
		
		return String.format("[ori:%s dir:%s]", origin, direction);
	}
	
	
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

