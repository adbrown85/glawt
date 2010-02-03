/*
 * Quadtree.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.io.FileNotFoundException;



/**
 * Tree with nodes that have four children to accelerate data access.
 */
public class Quadtree {
	
	private DataSource data;
	private int height;
	private QuadtreeNode root;
	
	
	public Quadtree(DataSource data) {
		
		this.data = data;
		this.height = QuadtreeBuilder.getHeightOf(data);
		this.root = QuadtreeBuilder.build(data);
	}
	
	
	private QuadtreeNode findFirstChild(QuadtreeNode parent,
	                                    IntersectionRecord record) {
		
		return parent.getChild(0);
	}
	
	
	private QuadtreeNode findNextChild(QuadtreeNode parent,
	                                   QuadtreeNode last,
	                                   IntersectionRecord record) {
		
		if (last.index == 3)
			return null;
		
		return parent.getChild(last.index + 1);
	}
	
	
	public void print() {
		
		root.printRecursive();
	}
	
	
	public double sample(Ray ray) {
		
		IntersectionRecord record;
		
		// 
		record = new IntersectionRecord(root, ray);
		return sample(ray, root, record);
	}
	
	
	private double sample(Ray ray,
	                      QuadtreeNode node,
	                      IntersectionRecord record) {
		
		// Check if empty or missed
		if (node.isEmpty() || record.isMiss())
			return 0.0;
		
		// Leaf take sample data
		if (node.isLeaf())
			return sampleAsLeaf(ray, node, record);
		
		// Otherwise sample children
		return sampleChildren(ray, node, record);
	}
	
	
	private double sampleAsLeaf(Ray ray,
	                            QuadtreeNode node,
	                            IntersectionRecord record) {
		
		
	}
	
	
	private double sampleChildren(Ray ray,
	                              QuadtreeNode node,
	                              IntersectionRecord record) {
		
		double result;
		QuadtreeNode current;
		
		current = findFirstChildNode(node);
		while (current != null) {
			updateIntersections(current, record);
			result += sample(ray, current, record);
			current = findNextChildNode(ray, current);
		}
		return result;
	}
	
	
	public static void main(String[] args) {
		
		Quadtree tree;
		
		try {
			
			// Constructor
			tree = new Quadtree(new VolumeData("volume.dat"));
			System.out.println("Height: " + tree.height);
			
			// Build and print
			tree.print();
		}
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}

