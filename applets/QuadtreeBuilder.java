/*
 * QuadtreeBuilder.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.io.FileNotFoundException;
import java.lang.Math;



/**
 * Builds a quadtree.
 */
public class QuadtreeBuilder {
	
	private DataSource data;
	private int height;
	public double[] childOffsets;
	
	
	private QuadtreeBuilder(DataSource data) {
		
		// Copy
		this.data = data;
		this.height = getHeightOf(data);
		
		// Child offsets
		childOffsets = new double[height+1];
		childOffsets[0] = 0.25;
		for (int i=1; i<childOffsets.length; ++i) {
			childOffsets[i] = childOffsets[i-1] / 2;
		}
	}
	
	
	public static QuadtreeNode build(DataSource data) {
		
		QuadtreeBuilder builder;
		
		builder = new QuadtreeBuilder(data);
		return builder.buildNode(0, new Point(0.5,0.5), 0);
	}
	
	
	private QuadtreeNode buildNode(int depth,
	                               Point center,
	                               int index) {
		
		QuadtreeNode node;
		
		// Make node
		node = new QuadtreeNode(index);
		if (depth == height) {
			buildNodeAsLeaf(depth, center, node);
		} else {
			buildNodeAsInner(depth, center, node);
		}
		return node;
	}
	
	
	private void buildNodeAsLeaf(int depth,
	                             Point center,
	                             QuadtreeNode node) {
		
		Point samplePoint;
		
		for (int i=0; i<4; ++i) {
			samplePoint = offsetPoint(center, i, childOffsets[depth]);
			if (data.getSample(samplePoint) > 0.5) {
				return;
			}
		}
		node.setEmpty(true);
	}
	
	
	private void buildNodeAsInner(int depth,
	                              Point center,
	                              QuadtreeNode node) {
		
		boolean empty;
		Point childCenter;
		QuadtreeNode childNode;
		
		empty = true;
		for (int i=0; i<4; ++i) {
			childCenter = offsetPoint(center, i, childOffsets[depth]);
			childNode = buildNode(depth+1, childCenter, i);
			node.addChild(childNode);
			if (!childNode.isEmpty()) {
				empty = false;
			}
		}
		node.setEmpty(empty);
	}
	
	
	public static int getHeightOf(DataSource data) {
		
		int size;
		
		size = data.getSize();
		return (int)(Math.log(size*size) / Math.log(4)) - 1;
	}
	
	
	private static Point offsetPoint(Point point,
	                                 int index,
	                                 double pitch) {
		
		switch (index) {
		case 0: return Point.add(point, new Point(-pitch,-pitch));
		case 1: return Point.add(point, new Point(+pitch,-pitch));
		case 2: return Point.add(point, new Point(-pitch,+pitch));
		case 3: return Point.add(point, new Point(+pitch,+pitch));
		default: return null;
		}
	}
	
	
	public static void main(String[] args) {
		
		QuadtreeNode root;
		VolumeData data;
		
		try {
			
			// Test
			data = new VolumeData("volume.dat");
			root = QuadtreeBuilder.build(data);
			root.printRecursive();
		}
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}

