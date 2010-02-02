/*
 * Vector2D.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.lang.IndexOutOfBoundsException;




/**
 * 2D vector with X and Y coordinates.
 */
public class Vector2D {
	
	public double x, y;
	
	
	
	/**
	 * Creates a new Vector2D.
	 */
	public Vector2D() {
		
		x = 0;
		y = 0;
	}
	
	
	
	/**
	 * Creates a new Vector2D.
	 * 
	 * @param x
	 *     X component.
	 * @param y
	 *     Y component.
	 */
	public Vector2D(double x,
	                double y) {
		
		this.x = x;
		this.y = y;
	}
	
	
	
	/**
	 * Creates a new Vector2D by copying another.
	 * 
	 * @param B
	 *     %Vector2D object to copy.
	 */
	public Vector2D(Vector2D B) {
		
		this.x = B.x;
		this.y = B.y;
	}
	
	
	
	/**
	 * Returns a component of the vector by its index.
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
	
	
	
	/**
	 * Subtracts a vector from this vector.
	 */
	public Vector2D minus(Vector2D B) {
		
		Vector2D C = new Vector2D();
		
		// Subtract components
		C.x = this.x - B.x;
		C.y = this.y - B.y;
		return C;
	}
	
	
	
	/**
	 * Scales a vector by a number.
	 */
	public static Vector2D scale(Vector2D A,
	                             double b) {
		
		Vector2D C = new Vector2D();
		
		// Multiply components
		C.x = A.x * b;
		C.y = A.y * b;
		return C;
	}
	
	
	
	/**
	 * Prints the vector.
	 */
	public void print() {
		
		System.out.println(toString());
	}
	
	
	
	/**
	 * Formats the vector as a string.
	 */
	public String toString() {
		
		return String.format("[%.2f %.2f]", x, y);
	}
	
	
	
	/**
	 * Test for Vector2D.
	 */
	public static void main(String[] args) {
		
		Vector2D A, B, C;
		
		// Start
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Vector2D");
		System.out.println("****************************************");
		System.out.println();
		
		// Test constructors
		System.out.println("Testing constructors:");
		A = new Vector2D();
		A.print();
		B = new Vector2D(20.0, 50.5);
		B.print();
		
		// Test copy constructor
		System.out.println("\nTesting copy constructor:");
		C = new Vector2D(B);
		B.x = 30.0;
		C.print();
		B.print();
		
		// Test get
		System.out.println("\nTesting get:");
		System.out.printf("B[0] = %f\n", B.get(0));
		System.out.printf("B[1] = %f\n", B.get(1));
		
		// Finish
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Vector2D");
		System.out.println("****************************************");
		System.out.println();
	}
}

