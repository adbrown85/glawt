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
public class QuadtreeNode extends TreeNode {
	
	public boolean empty;
	
	
	/**
	 * Creates a node.
	 * 
	 * @param index
	 *     Identifies node from its siblings.
	 */
	public QuadtreeNode(int index) {
		
		super(index, 4);
	}
	
	
	public QuadtreeNode getChild(int index) {
		
		return (QuadtreeNode)super.getChild(index);
	}
	
	
	public boolean isEmpty() {
		
		return empty;
	}
	
	
	public String toString() {
		
		return String.format("%s, empty=%s", super.toString(), empty);
	}
	
	
	public void setEmpty(boolean empty) {
		
		this.empty = empty;
	}
	
	
	public static void main(String[] args) {
		
		QuadtreeNode root;
		
		// Test
		root = new QuadtreeNode(0);
		for (int i=0; i<4; ++i) {
			root.addChild(new QuadtreeNode(i));
		}
		root.printRecursive();
	}
}

