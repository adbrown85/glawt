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
	
	private static final int FIRST_STEP=1, SECOND_STEP=2;
	private static final int FIRST_CHILD=0, NULL_CHILD=-1, ROOT_KEY=0;
	private static final long SLEEP_TIME=1000;
	private static final int XZ_PLANE=0;
	private static final int YZ_PLANE=1;
	private static final int MAX_HEIGHT=5;
	private static final int[] jump={1,5,21,85,341,1365,5461,21845,87381};
	
	private AxisAlignedPlane[] planes;
	private boolean[] texture;
	private BoundingBox boundingBox;
	private int height, length;
	
	
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
	                                 BoundsCheck parentTimes,
	                                 int subtreeHeight) {
		
		int name;
		
		// Enters on bottom side, then right or left
		if (parentTimes.t0[0] < parentTimes.t0[1]) {
			if (parentTimes.th[0] < parentTimes.t0[1]) {
				name = 1;
			} else {
				name = 0;
			}
		}
		
		// Enters on left side, then top or bottom
		else {
			if (parentTimes.th[1] < parentTimes.t0[0]) {
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
					case YZ_PLANE: return nullNode();
				}
			case 2:
				switch (findExitPlane(childTimes)) {
					case XZ_PLANE: return nullNode();
					case YZ_PLANE: return getChild(parentNode, 3, subtreeHeight);
				}
			case 3:
				switch (findExitPlane(childTimes)) {
					case XZ_PLANE: return nullNode();
					case YZ_PLANE: return nullNode();
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
	
	
	private NodeIndex getRealChild(NodeIndex parentNode,
	                               NodeIndex childNode,
	                               Ray ray,
	                               int subtreeHeight) {
		
		int name;
		
		if (childNode.name == NULL_CHILD)
			return childNode;
		
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
		return getChild(parentNode, name, subtreeHeight);
	}
	
	
	private boolean isEmpty(NodeIndex node) {
		
		return texture[node.key];
	}

	
	private NodeIndex nullNode() {
		
		NodeIndex node;
		
		node = new NodeIndex();
		node.name = NULL_CHILD;
		return node;
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
				result = sample(ray, rayPrime, times);
			} else {
				result = sample(ray, ray, times);
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
	                      BoundsCheck rootTimes) {
		
		BoundingBox[] box=new BoundingBox[MAX_HEIGHT];
		BoundsCheck[] times=new BoundsCheck[MAX_HEIGHT];
		float result;
		int depth, childDepth, childHeight;
		int[] step=new int[MAX_HEIGHT];
		NodeIndex[] node=new NodeIndex[MAX_HEIGHT],
		            nodePrime=new NodeIndex[MAX_HEIGHT];
		
		// Initialize
		result = 0.0f;
		depth = 0;
		childHeight = height - 1;
		node[0] = new NodeIndex(FIRST_CHILD, ROOT_KEY);
		nodePrime[0] = new NodeIndex(FIRST_CHILD, ROOT_KEY);
		step[0] = FIRST_STEP;
		times[0] = rootTimes;
		box[0] = new BoundingBox(boundingBox);
		for (int i=1; i<MAX_HEIGHT; ++i) {
			nodePrime[i] = new NodeIndex(NULL_CHILD, NULL_CHILD);
			step[i] = FIRST_STEP;
			times[i] = new BoundsCheck();
		}
		
		// While in volume
		while (depth >= 0) {
			switch (step[depth]) {
			case FIRST_STEP:
				
				// Check if empty
				if (isEmpty(node[depth])) {
					updateDisplay(Color.RED);
					--depth;
					++childHeight;
					continue;
				} else {
					updateDisplay(Color.GREEN);
				}
				
				// If a leaf, sample it
				if (depth == height) {
					result += sampleAsLeaf(ray, times[depth]);
					--depth;
					++childHeight;
					continue;
				}
			
			case SECOND_STEP:
				
				// Find first or next child
				childDepth = depth + 1;
				if (nodePrime[childDepth].name == NULL_CHILD) {
					nodePrime[childDepth] = findFirstChild(nodePrime[depth],
					                                       times[depth],
					                                       childHeight);
				} else {
					nodePrime[childDepth] = findNextChild(nodePrime[depth],
					                                      times[childDepth],
					                                      nodePrime[childDepth],
					                                      childHeight);
				}
				node[childDepth] = getRealChild(node[depth],
				                                nodePrime[childDepth],
				                                ray,
				                                childHeight);
				
				// Move up tree if outside of node
				if (nodePrime[childDepth].name == NULL_CHILD) {
					--depth;
					++childHeight;
				}
				
				// Otherwise move to child
				else {
					times[childDepth] = updateTimes(nodePrime[childDepth], times[depth]);
					updateDisplay(ray, times, node, box, depth, childDepth);
					step[depth] = SECOND_STEP;
					step[childDepth] = FIRST_STEP;
					++depth;
					--childHeight;
				}
			}
		}
		
		// Finish
		return result;
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

	
	private void updateDisplay(Ray ray,
                               BoundsCheck[] times,
                               NodeIndex[] node,
                               BoundingBox[] box,
                               int depth,
                               int childDepth) {
	    
		updatePlanes(ray, times[childDepth]);
		updateBoundingBox(node[childDepth], box[depth]);
		box[childDepth] = new BoundingBox(boundingBox);
		updateDisplay(Color.YELLOW);
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
			ray = new Ray(new Point(250,20), new Vector2D(-1.0,1.0));
			
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

