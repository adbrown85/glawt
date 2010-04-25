/*
 * QuadtreeTexture.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.io.FileNotFoundException;


public class QuadtreeTexture {
	
	public boolean[] storage;
	public int height, length;
	
	
	public QuadtreeTexture(DataSource data) {
		
		QuadtreeBuilder builder;
		QuadtreeNode root;
		
		// Build nodes
		builder = new QuadtreeBuilder(data);
		root = builder.build();
		
		// Get attributes
		this.height = builder.getHeight();
		this.length = builder.getTotalNodes();
		
		// Store in texture
		this.storage = new boolean[length];
		store(root, 0, 0);
	}
	
	
	public boolean isEmpty(int key) {
		
		return storage[key];
	}
	
	
	public void print() {
		
		for (int i=0; i<storage.length; ++i) {
			System.out.printf("%2d %s\n", i, storage[i]);
		}
	}
	
	
	private int store(QuadtreeNode node,
	                  int key,
	                  int depth) {
		
		// Store self
		storage[key] = node.isEmpty();
		
		// Store children
		if (depth < height) {
			for (int i=0; i<4; ++i) {
				key = store(node.getChild(i), ++key, depth+1);
			}
		}
		return key;
	}
	
	
	public static void main(String args[]) {
		
		QuadtreeTexture texture;
		VolumeData data;
		
		// Start
		System.out.println();
		System.out.println("****************************************");
		System.out.println("QuadtreeTexture");
		System.out.println("****************************************");
		System.out.println();
		
		// Test
		try {
			data = new VolumeData("volume.dat");
			texture = new QuadtreeTexture(data);
			texture.print();
		} catch (FileNotFoundException e) {
			System.err.println(e.getMessage());
		}
		
		// Finish
		System.out.println();
		System.out.println("****************************************");
		System.out.println("QuadtreeTexture");
		System.out.println("****************************************");
		System.out.println();
	}
}

