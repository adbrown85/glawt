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
	public double[] pitch;
	
	
	private QuadtreeBuilder(DataSource data) {
		
		// Copy
		this.data = data;
		this.height = getHeightOf(data);
		
		// Pitch array
		pitch = new double[height+2];
		pitch[0] = 1.0;
		for (int i=1; i<pitch.length; ++i) {
			pitch[i] = data.getPitch() / i;
		}
	}
	
	
	public static QuadtreeNode build(DataSource data) {
		
		QuadtreeBuilder builder;
		
		builder = new QuadtreeBuilder(data);
		return builder.buildNode(0, 0, new Point(0.5,0.5));
	}
	
	
	private QuadtreeNode buildNode(int depth,
	                               int index,
	                               Point center) {
		
		QuadtreeNode node;
		
		// Make node
		node = new QuadtreeNode(depth, index, center);
		if (depth == height) {
			buildNodeAsLeaf(node);
		} else {
			buildNodeAsInner(node);
		}
		return node;
	}
	
	
	private void buildNodeAsLeaf(QuadtreeNode node) {
		
		Point samplePoint;
		
		for (int i=0; i<4; ++i) {
			samplePoint = offsetPoint(node.center, i, pitch[node.depth+1]);
			if (data.getSample(samplePoint) > 0.0) {
				return;
			}
		}
		node.setEmpty(true);
	}
	
	
	private void buildNodeAsInner(QuadtreeNode node) {
		
		Point childCenter;
		
		for (int i=0; i<4; ++i) {
			childCenter = offsetPoint(node.center, i, pitch[node.depth+1]);
			node.addChild(buildNode(node.depth+1, i, childCenter));
		}
	}
	
	
	public static int getHeightOf(DataSource data) {
		
		return (int)(Math.log(data.getSize()) / Math.log(4));
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

