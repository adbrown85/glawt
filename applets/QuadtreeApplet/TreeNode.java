/*
 * TreeNode.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.util.ArrayList;



/**
 * Generic node for making up a tree.
 */
public class TreeNode {
	
	private int index;
	private ArrayList<TreeNode> children;
	
	
	/**
	 * Creates a node.
	 * 
	 * @param index
	 *     Identifies node from its siblings.
	 */
	public TreeNode(int index) {
		
		init(index, 4);
	}
	
	
	/**
	 * Creates a node.
	 * 
	 * @param index
	 *     Identifies node from its siblings.
	 * @param capacity
	 *     Initial capacity for the list of children.
	 */
	public TreeNode(int index,
	                int capacity) {
		
		init(index, capacity);
	}
	
	
	public void addChild(TreeNode node) {
		
		children.add(node);
	}
	
	
	public TreeNode getChild(int index) {
		
		return children.get(index);
	}
	
	
	public int getIndex() {
		
		return index;
	}
	
	
	private void init(int index,
	                  int capacity) {
		
		this.index = index;
		this.children = new ArrayList<TreeNode>(capacity);
	}
	
	
	public boolean isLeaf() {
		
		return children.isEmpty();
	}
	
	
	public void print() {
		
		System.out.println(toString());
	}
	
	
	public void printRecursive() {
		
		printRecursive(this, "");
	}
	
	
	private static void printRecursive(TreeNode node,
	                                   String indent) {
		
		System.out.print(indent);
		node.print();
		indent += "  ";
		for (TreeNode child : node.children) {
			printRecursive(child, indent);
		}
	}
	
	
	public String toString() {
		
		return String.format("index=%d, leaf=%s", index, isLeaf());
	}
	
	
	public static void main(String[] args) {
		
		TreeNode node;
		
		// Test
		node = new TreeNode(0, 4);
		for (int i=0; i<4; ++i)
			node.addChild(new TreeNode(i));
		node.printRecursive();
	}
}

