/*
 * Shape.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;



/**
 * Shape with a size, center, and origin.
 */
public class Shape extends BasicDrawable
                   implements Drawable {
	
	public BoundingBox boundingBox;
	public double size;
	public Point center;
	
	
	public Shape(double size,
	             Point center) {
		
		super(null, null);
		
		// Initialize
		this.size = size;
		this.center = center;
		this.boundingBox = new BoundingBox(size, center);
	}
	
	
	public BoundsCheck check(Ray ray) {
		
		return boundingBox.check(ray);
	}
	
	
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		// Bounding box
		graphic.setColor(Color.BLACK);
		boundingBox.draw(graphic, dimension);
		
		// Accessories
		super.draw(graphic, dimension);
	}
	
	
	public BoundingBox getBoundingBox() {
		
		return new BoundingBox(boundingBox);
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
		RayTimePair rayTimes;
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
			rayTimes = boundsCheck.getIntersectionTimes();
			ray.addIntersectionAt(rayTimes.first);
			ray.addIntersectionAt(rayTimes.second);
		}
		display.start();
	}
}

