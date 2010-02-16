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
	
	
	public Vector2D() {
		
		this.x = 0;
		this.y = 0;
	}
	
	
	public Vector2D(double value) {
		
		this.x = value;
		this.y = value;
	}
	
	
	public Vector2D(double x,
	                double y) {
		
		this.x = x;
		this.y = y;
	}
	
	
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
	
	
	public Vector2D minus(Vector2D B) {
		
		Vector2D C = new Vector2D();
		
		// Subtract components
		C.x = this.x - B.x;
		C.y = this.y - B.y;
		return C;
	}
	
	
	/**
	 * Returns the length of the vector.
	 */
	public static double length(Vector2D A) {
		
		return Math.sqrt(A.x*A.x + A.y*A.y);
	}
	
	
	/**
	 * Returns the maximum component of the vector.
	 */
	public static double max(Vector2D A) {
		
		return Math.max(A.x, A.y);
	}
	
	
	/**
	 * Returns the minimum component of the vector.
	 */
	public static double min(Vector2D A) {
		
		return Math.min(A.x, A.y);
	}
	
	
	/**
	 * Returns a unit vector of length 1.
	 */
	public static Vector2D normalize(Vector2D A) {
		
		double invLen;
		
		invLen = 1 / Vector2D.length(A);
		return new Vector2D(A.x*invLen, A.y*invLen);
	}
	
	
	/**
	 * Set a component of the vector by its index.
	 * 
	 * @param i
	 *     Index of the component.
	 */
	public void set(int i,
	                double value) {
		
		switch (i) {
			case 0: 
				x = value;
				break;
			case 1:
				y = value;
				break;
			default:
				throw new IndexOutOfBoundsException("Out of bounds.");
		}
	}
	
	
	/**
	 * Scales a vector by a number.
	 */
	public static Vector2D scale(Vector2D A,
	                             double b) {
		
		return new Vector2D(A.x*b, A.y*b);
	}
	
	
	public static Vector2D subtract(double[] A,
	                                double[] B) {
		
		return new Vector2D(A[0]-B[0], A[1]-B[1]);
	}
	
	
	public void print() {
		
		System.out.println(toString());
	}
	
	
	public String toString() {
		
		return String.format("[%.2f %.2f]", x, y);
	}
	
	
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

