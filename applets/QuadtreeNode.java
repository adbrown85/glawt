/*
 * QuadtreeNode.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.io.FileNotFoundException;
import java.util.ArrayList;



/**
 * Node in a Quadtree.
 */
public class QuadtreeNode {
	
	public boolean empty;
	public int depth, index;
	public ArrayList<QuadtreeNode> children;
	public Point center;
	
	
	/**
	 * Creates a node.
	 * 
	 * @param depth
	 *     Depth of the node in the tree.
	 * @param index
	 *     Identifies node from its siblings.
	 * @param center
	 *     Center of the node.
	 */
	public QuadtreeNode(int depth,
	                    int index,
	                    Point center) {
		
		this.depth = depth;
		this.index = index;
		this.center = center;
		this.children = new ArrayList<QuadtreeNode>(4);
	}
	
	
	public void addChild(QuadtreeNode node) {
		
		children.add(node);
	}
	
	
	public QuadtreeNode getChild(int index) {
		
		return children.get(index);
	}
	
	
	public boolean isEmpty() {
		
		return empty;
	}
	
	
	public boolean isLeaf() {
		
		return children.isEmpty();
	}
	
	
	public void print() {
		
		System.out.printf("index=%d, depth=%d, center=%s, empty=%s\n",
		                  index, depth, center, empty);
	}
	
	
	public void printRecursive() {
		
		printRecursive(this);
	}
	
	
	public static void printRecursive(QuadtreeNode node) {
		
		node.print();
		for (QuadtreeNode child : node.children) {
			printRecursive(child);
		}
	}
	
	
	public void setEmpty(boolean empty) {
		
		this.empty = empty;
	}
	
	
	public static void main(String[] args) {
		
		QuadtreeNode root;
		
		// Start
		System.out.println();
		System.out.println("****************************************");
		System.out.println("QuadtreeNode");
		System.out.println("****************************************");
		System.out.println();
		
		// Test
		root = new QuadtreeNode(0, 0, new Point(0.5,0.5));
		root.addChild(new QuadtreeNode(1, 0, new Point(0.25,0.25)));
		root.printRecursive();
		
		// Finish
		System.out.println();
		System.out.println("****************************************");
		System.out.println("QuadtreeNode");
		System.out.println("****************************************");
		System.out.println();
	}
}

