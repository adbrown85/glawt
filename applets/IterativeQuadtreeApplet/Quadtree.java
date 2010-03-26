/*
 * Quadtree.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.io.FileNotFoundException;



/**
 * Tree with nodes that have four children to accelerate data access.
 */
public class Quadtree extends BasicDrawable
                      implements Drawable {
	
	private static final long SLEEP_TIME=1000;
	private static final int XZ_PLANE=0;
	private static final int YZ_PLANE=1;
	private static final int[] jump={1,5,21,85,341,1365,5461,21845,87381};
	
	private AxisAlignedPlane[] planes;
	private boolean[] texture;
	private BoundingBox boundingBox;
	private int height, length;
	private NodeIndex root;
	
	
	public Quadtree(DataSource data) {
		
		super(null, null);
		
		// Build
		build(data);
		
		// Display
		this.boundingBox = null;
		this.planes = new AxisAlignedPlane[6];
	}
	
	
	private void build(DataSource data) {
		
		QuadtreeBuilder builder;
		QuadtreeNode root;
		
		// Build nodes and store in texture
		builder = new QuadtreeBuilder(data);
		root = builder.build();
		root.printRecursive();
		this.height = builder.getHeight();
		this.length = builder.getTotalNodes();
		this.texture = new boolean[length];
		store(root, 0, 0);
		this.root = new NodeIndex();
	}
	
	
	private Point calculateNewCenter(NodeIndex childNode,
	                                 BoundingBox parentBox) {
		
		Point offset;
		
		offset = calculateOffset(childNode, parentBox);
		return Point.add(parentBox.center, offset);
	}
	
	
	private Point calculateOffset(NodeIndex childNode,
	                              BoundingBox parentBox) {
		
		double shift;
		
		shift = parentBox.size * 0.25;
		switch (childNode.name) {
			case 0: return new Point(-shift, -shift);
			case 1: return new Point(+shift, -shift);
			case 2: return new Point(-shift, +shift);
			case 3: return new Point(+shift, +shift);
			default: return null;
		}
	}
	
	
	private void clearDisplay() {
		
		boundingBox = null;
		for (int i=0; i<planes.length; ++i) {
			planes[i] = null;
		}
		fireUpdateEvent();
	}
	
	
	public void draw(Graphics2D graphic,
	                 Dimension size) {
		
		// Node bounding box
		if (boundingBox != null) {
			for (AxisAlignedPlane plane : planes) {
				if (plane != null) {
					plane.draw(graphic, size);
				}
			}
			boundingBox.draw(graphic, size);
		}
		
		// Accessories
		super.draw(graphic, size);
	}
	
	
	private int findExitPlane(BoundsCheck times) {
		
		if (times.t1[0] < times.t1[1]) {
			return YZ_PLANE;
		} else {
			return XZ_PLANE;
		}
	}
	
	
	private NodeIndex findFirstChild(NodeIndex parentNode,
	                                 BoundsCheck times,
	                                 int subtreeHeight) {
		
		int name;
		
		// Enters on bottom side, then right or left
		if (times.t0[0] < times.t0[1]) {
			if (times.th[0] < times.t0[1]) {
				name = 1;
			} else {
				name = 0;
			}
		}
		
		// Enters on left side, then top or bottom
		else {
			if (times.th[1] < times.t0[0]) {
				name = 2;
			} else {
				name = 0;
			}
		}
		
		// Calculate key
		return getChild(parentNode, name, subtreeHeight);
	}
	
	
	private NodeIndex findNextChild(NodeIndex parentNode,
	                                BoundsCheck childTimes,
	                                NodeIndex lastChildNode,
	                                int subtreeHeight) {
		
		switch (lastChildNode.name) {
			case 0:
				switch (findExitPlane(childTimes)) {
					case XZ_PLANE: return getChild(parentNode, 2, subtreeHeight);
					case YZ_PLANE: return getChild(parentNode, 1, subtreeHeight);
				}
			case 1:
				switch (findExitPlane(childTimes)) {
					case XZ_PLANE: return getChild(parentNode, 3, subtreeHeight);
					case YZ_PLANE: return null;
				}
			case 2:
				switch (findExitPlane(childTimes)) {
					case XZ_PLANE: return null;
					case YZ_PLANE: return getChild(parentNode, 3, subtreeHeight);
				}
			case 3:
				switch (findExitPlane(childTimes)) {
					case XZ_PLANE: return null;
					case YZ_PLANE: return null;
				}
			default: throw new IndexOutOfBoundsException();
		}
	}
	
	
	private Vector2D getChange(NodeIndex childNode) {
		
		switch (childNode.name) {
			case 0: return new Vector2D(0, 0);
			case 1: return new Vector2D(1, 0);
			case 2: return new Vector2D(0, 1);
			case 3: return new Vector2D(1, 1);
			default: throw new IndexOutOfBoundsException();
		}
	}
	
	
	private NodeIndex getChild(NodeIndex parentNode,
	                           int childName,
	                           int subtreeHeight) {
		
		NodeIndex childNode=new NodeIndex();
		
		// Calculate key and name for child
		childNode.key = (parentNode.key+1) + (childName*jump[subtreeHeight]);
		childNode.name = childName;
		return childNode;
	}
	
	
	private Ray getRayPrime(Ray ray,
	                        BoundingBox boundingBox) {
		
		boolean flipped;
		double center, origin;
		Ray rayPrime;
		
		// Copy ray
		rayPrime = new Ray(ray);
		rayPrime.setColor(Color.ORANGE);
		
		// Try to flip it
		flipped = false;
		for (int i=0; i<2; ++i) {
			if (ray.direction.get(i) < 0) {
				center = boundingBox.center.get(i);
				origin = center - (ray.origin.get(i) - center);
				rayPrime.origin.set(i, origin);
				rayPrime.direction.set(i, -ray.direction.get(i));
				flipped = true;
			}
		}
		
		// Finish
		if (flipped) {
			return rayPrime;
		} else {
			return null;
		}
	}
	
	
	private NodeIndex getRealChild(NodeIndex parent,
	                               NodeIndex childNode,
	                               Ray ray,
	                               int subtreeHeight) {
		
		int name;
		
		if (childNode == null)
			return null;
		
		name = childNode.name;
		if (ray.direction.x < 0) {
			switch (name) {
				case 0 : name = 1; break;
				case 1 : name = 0; break;
				case 2 : name = 3; break;
				case 3 : name = 2; break;
			}
		}
		if (ray.direction.y < 0) {
			switch (name) {
				case 0: name = 2; break;
				case 1: name = 3; break;
				case 2: name = 0; break;
				case 3: name = 1; break;
			}
		}
		return getChild(parent, name, subtreeHeight);
	}
	
	
	private boolean isEmpty(NodeIndex node) {
		
		return texture[node.key];
	}
	
	
	public double sample(Ray ray,
	                     Shape shape) {
		
		double result;
		BoundsCheck times;
		Ray rayPrime;
		
		// Reset
		ray.clearAccessories();
		
		// Get times from bounding box
		boundingBox = new BoundingBox(shape.getBoundingBox());
		times = boundingBox.check(ray);
		updatePlanes(ray, times);
		updateDisplay(Color.YELLOW);
		
		// Sample
		if (times.isHit()) {
			rayPrime = getRayPrime(ray, boundingBox);
			if (rayPrime != null) {
				ray.addAccessory(rayPrime);
				times = boundingBox.check(rayPrime);
				result = sample(ray, rayPrime, root, root, times, 0, height);
			} else {
				result = sample(ray, ray, root, root, times, 0, height);
			}
		} else {
			updateDisplay(Color.RED);
			result = 0.0;
		}
		clearDisplay();
		return result;
	}
	
	
	private double sample(Ray ray,
	                      Ray rayPrime,
	                      NodeIndex node,
	                      NodeIndex nodePrime,
	                      BoundsCheck times,
	                      int depth,
	                      int subtreeHeight) {
		
		// Check if empty or missed
		if (isEmpty(node)) {
			updateDisplay(Color.RED);
			return 0.0;
		} else {
			updateDisplay(Color.GREEN);
		}
		
		// Leaf take sample data
		if (depth == height)
			return sampleAsLeaf(ray, times);
		
		// Otherwise sample children
		return sampleChildren(ray, rayPrime, node, nodePrime, times, depth+1, subtreeHeight-1);
	}
	
	
	private double sampleAsLeaf(Ray ray,
	                            BoundsCheck times) {
		
		double t;
		RayTimePair pair;
		
		pair = times.getIntersectionTimes();
		t = pair.first + 10.0;
		while (t < pair.second) {
			ray.addIntersectionAt(t);
			fireUpdateEvent();
			sleep();
			t += 10.0;
		}
		
		return 0.2;
	}
	
	
	private double sampleChildren(Ray ray,
	                              Ray rayPrime,
	                              NodeIndex parentNode,
	                              NodeIndex parentNodePrime,
	                              BoundsCheck parentTimesPrime,
	                              int depth,
	                              int subtreeHeight) {
		
		BoundingBox parentBoundingBox;
		BoundsCheck childTimesPrime;
		double result=0;
		NodeIndex childNode, childNodePrime;
		
		// Store current bounding box for all children
		parentBoundingBox = new BoundingBox(boundingBox);
		
		// Traverse children until out of parent
		childNodePrime = findFirstChild(parentNode, parentTimesPrime, subtreeHeight);
		childNode = getRealChild(parentNode, childNodePrime, ray, subtreeHeight);
		while (childNodePrime != null) {
			childTimesPrime = updateTimes(childNodePrime, parentTimesPrime);
			updateBoundingBox(childNode, parentBoundingBox);
			updatePlanes(ray, childTimesPrime);
			updateDisplay(Color.YELLOW);
			result += sample(ray, rayPrime, childNode, childNodePrime, childTimesPrime, depth, subtreeHeight);
			childNodePrime = findNextChild(parentNodePrime, childTimesPrime, childNodePrime, subtreeHeight);
			childNode = getRealChild(parentNode, childNodePrime, ray, subtreeHeight);
		}
		return result;
	}
	
	
	private void sleep() {
		
		try {
			Thread.sleep(SLEEP_TIME);
		} catch (InterruptedException e) {
			System.err.println("[Quadtree] Interrupted in sleep.");
		}
	}
	
	
	private int store(QuadtreeNode node,
	                  int key,
	                  int depth) {
		
		// Store self
		texture[key] = node.isEmpty();
		
		// For 
		if (depth < height) {
			for (int i=0; i<4; ++i) {
				key = store(node.getChild(i), ++key, depth+1);
			}
		}
		return key;
	}
	
	
	private void updateBoundingBox(NodeIndex childNode,
	                               BoundingBox parentBoundingBox) {
		
		double size;
		Point center;
		
		// Create bounding box from new size and center
		size = parentBoundingBox.size * 0.5;
		center = calculateNewCenter(childNode, parentBoundingBox);
		boundingBox = new BoundingBox(size, center);
	}
	
	
	private void updatePlanes(Ray ray,
	                          BoundsCheck times) {
		
		double t0x, t0y, t1x, t1y, thx, thy;
		
		t0x = ray.getValueAt(0, times.t0[0]);
		t0y = ray.getValueAt(1, times.t0[1]);
		t1x = ray.getValueAt(0, times.t1[0]);
		t1y = ray.getValueAt(1, times.t1[1]);
		thx = ray.getValueAt(0, times.th[0]);
		thy = ray.getValueAt(1, times.th[1]);
		try {
			planes[0] = new AxisAlignedPlane(new Point(t0x,0.0));
			planes[1] = new AxisAlignedPlane(new Point(0.0,t0y));
			planes[2] = new AxisAlignedPlane(new Point(t1x,0.0));
			planes[3] = new AxisAlignedPlane(new Point(0.0,t1y));
			planes[4] = new AxisAlignedPlane(new Point(thx,0.0));
			planes[5] = new AxisAlignedPlane(new Point(0.0,thy));
		} catch (Exception e) {
		}
	}
	
	
	private BoundsCheck updateTimes(NodeIndex childNode,
	                                BoundsCheck parentTimes) {
		
		BoundsCheck childTimes;
		Vector2D change, delta, halfDelta;
		
		// Initialize
		change = getChange(childNode);
		delta = Vector2D.subtract(parentTimes.t1, parentTimes.t0);
		halfDelta = Vector2D.scale(delta, 0.5);
		
		// Calculate child times
		childTimes = new BoundsCheck();
		childTimes.t0[0] = parentTimes.t0[0] + (halfDelta.x * change.x);
		childTimes.t0[1] = parentTimes.t0[1] + (halfDelta.y * change.y);
		childTimes.t1[0] = childTimes.t0[0] + halfDelta.x;
		childTimes.t1[1] = childTimes.t0[1] + halfDelta.y;
		childTimes.th[0] = (childTimes.t0[0] + childTimes.t1[0]) * 0.5;
		childTimes.th[1] = (childTimes.t0[1] + childTimes.t1[1]) * 0.5;
		return childTimes;
	}
	
	
	private void updateDisplay(Color color) {
		
		boundingBox.setColor(color);
		boundingBox.setStrokeWidth(3.0);
		fireUpdateEvent();
		sleep();
	}
	
	
	public static void main(String[] args)
	                        throws Exception {
		
		double sample;
		DisplayFrame display;
		Quadtree quadtree;
		Ray ray;
		Shape shape;
		VolumeData volumeData;
		
		try {
			
			// Setup
			shape = new Shape(300, new Point(200,200));
			volumeData = new VolumeData("volume.dat");
			volumeData.setBoundingBox(shape.getBoundingBox());
			quadtree = new Quadtree(volumeData);
			ray = new Ray(new Point(50,20), new Vector2D(1.0,1.0));
			
			// Show
			display = new DisplayFrame("Quadtree");
			display.add(quadtree);
			display.add(shape);
			display.add(volumeData);
			display.add(ray);
			display.start();
			
			// Test
			for (int i=0; i<3; ++i) {
				Thread.sleep(2000);
				sample = quadtree.sample(ray, shape);
				System.out.printf("Sample: %.2f\n", sample);
			}
		}
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}

