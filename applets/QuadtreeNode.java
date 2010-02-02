/*
 * QuadtreeNode.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */



/**
 * Node in a Quadtree.
 */
public class QuadtreeNode {
	
	private boolean leaf, empty;
	private double tx0, ty0, tx1, ty1, txh, tyh;
	private QuadtreeNode[4] children;
	private DataSource dataSource;
	
	
	public QuadtreeNode() {
		
		
	}
	
	
	public static void main(String[] args) {
		
		// Start
		System.out.println();
		System.out.println("****************************************");
		System.out.println("QuadtreeNode");
		System.out.println("****************************************");
		System.out.println();
		
		// Test
		
		// Finish
		System.out.println();
		System.out.println("****************************************");
		System.out.println("QuadtreeNode");
		System.out.println("****************************************");
		System.out.println();
	}
}

