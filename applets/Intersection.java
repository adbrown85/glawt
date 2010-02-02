/*
 * Intersection.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */




/**
 * Circle showing a point at an intersection.
 */
public class Intersection extends Point {
	
	
	double t;
	
	
	
	/**
	 * Creates a new %Intersection from coordinates and a time.
	 */
	public Intersection(double x,
	                    double y,
	                    double t) {
		
		// Initialize
		super(x, y);
		this.t = t;
		setStroked();
	}
	
	
	
	/**
	 * Creates a new %Intersection from a point and a time.
	 */
	public Intersection(Point point,
	                    double t) {
		
		// Initialize
		super(point);
		this.t = t;
		setStroked();
	}
	
	
	
	/**
	 * Creates a new %Intersection from a time.
	 */
	public Intersection(double t) {
		
		// Initialize
		super();
		this.t = t;
		setStroked();
	}
	
	
	
	/**
	 * Test for %IntersectionPoint.
	 */
	public static void main(String[] args) {
		
		Display display;
		Intersection intersection;
		
		// Start
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Intersection");
		System.out.println("****************************************");
		System.out.println();
		
		// Test
		display = new Display("Intersection", 640, 480);
		intersection = new Intersection(45, 50, 100);
		display.add(intersection);
		display.start();
		
		// Finish
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Intersection");
		System.out.println("****************************************");
		System.out.println();
	}
}

