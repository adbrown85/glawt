/*
 * Square.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.*;
import java.lang.Math;




public class Square implements Drawable {
	
	
	public AxisAlignedSlab slabs[];
	public double half, size;
	public Point center;
	
	
	
	/**
	 * Creates a new %Square.
	 */
	public Square(double size,
	              Point center) throws Exception {
		
		// Copy
		this.size = size;
		this.center = center;
		
		// Initialize
		this.half = size / 2;
		slabs = new AxisAlignedSlab[2];
		slabs[0] = new AxisAlignedSlab(new Point(center.x,0), size);
		slabs[1] = new AxisAlignedSlab(new Point(0,center.y), size);
	}
	
	
	
	/**
	 * Draws the %Square into a graphic.
	 */
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		double x, y;
		
		// Calculate
		x = center.x - half;
		y = center.y - half;
		
		// Draw
		graphic.drawRect((int)x, (int)y, (int)size, (int)size);
		for (AxisAlignedSlab slab : slabs) {
			slab.draw(graphic, dimension);
		}
	}
	
	
	
	/**
	 * Checks if the square is intersected by a ray.
	 * 
	 * Gets the intersections of the slabs formed by the square.  Finds the 
	 * first intersection from where the ray leaves a slab, and the last 
	 * intersection from where the ray enters a slab.  If the ray ever leaves 
	 * a slab before it enters another, then the ray has missed the square.
	 */
	public Intersection intersectedBy(Ray ray) {
		
		IntersectionPair best, pair;
		
		// Initialize
		best = new IntersectionPair();
		best.min = new Intersection(Double.NEGATIVE_INFINITY);
		best.max = new Intersection(Double.POSITIVE_INFINITY);
		
		// For each slab
		for (AxisAlignedSlab slab : slabs) {
			
			// Get intersections
			pair = slab.intersectedBy(ray);
			if (pair == null) {
				if (slab.contains(ray))
					continue;
				else
					return null;
			}
			ray.addIntersectionPair(pair);
			
			// Update minimum and maximum times
			if (pair.min != null && pair.min.t > best.min.t)
				best.min = pair.min;
			if (pair.max != null && pair.max.t < best.max.t) 
				best.max = pair.max;
			
			// Check if left a slab before entering another
			if (best.min.t > best.max.t)
				return null;
		}
		
		// Return first
		return best.min;
	}
	
	
	
	/**
	 * Prints the %Square's attributes.
	 */
	public void print() {
		
		System.out.println(toString());
	}
	
	
	
	/**
	 * Formats the %Square's attributes as a string.
	 */
	public String toString() {
		
		return String.format("[%.2f %s]", size, center);
	}
	
	
	
	/**
	 * Test for the %Square.
	 */
	public static void main(String[] args) throws Exception {
		
		Display display;
		Intersection intersection;
		Ray ray;
		Square square;
		
		// Start
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Square");
		System.out.println("****************************************");
		System.out.println();
		
		// Create the shape
		square = new Square(100.0, new Point(200.0, 200.0));
		System.out.printf("Square: %s\n", square);
		
		// Do intersection
		ray = new Ray(new Point(600, 340), new Vector2D(-1.0, -0.5));
		intersection = square.intersectedBy(ray);
		if (intersection != null) {
			intersection.setWidth(10);
			ray.addIntersection(intersection);
			System.out.printf("t: %.2f\n", intersection.t);
		}
		
		// Show it
		display = new Display("Square", 640, 480);
		display.add(square);
		display.add(ray);
		display.start();
		
		// Finish
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Square");
		System.out.println("****************************************");
		System.out.println();
	}
}

