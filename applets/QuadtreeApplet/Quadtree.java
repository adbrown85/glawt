/*
 * Quadtree.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;
import java.io.FileNotFoundException;
import java.util.ArrayList;



/**
 * Tree with nodes that have four children to accelerate data access.
 */
public class Quadtree extends BasicDrawable
                      implements Drawable {
	
	private static final long SLEEP_TIME=1000;
	private static final int XZ_PLANE=0;
	private static final int YZ_PLANE=1;
	
	private DataSource data;
	private int height;
	private QuadtreeNode root;
	
	private BoundingBox boundingBox;
	private AxisAlignedPlane[] halfPlanes;
	
	
	public Quadtree(DataSource data) {
		
		super(null, null);
		
		// Core
		this.data = data;
		this.height = QuadtreeBuilder.getHeightOf(data);
		this.root = QuadtreeBuilder.build(data);
		
		// Display
		this.boundingBox = null;
		this.halfPlanes = new AxisAlignedPlane[2];
	}
	
	
	private Point calculateNewCenter(QuadtreeNode child,
	                                 BoundingBox parentBox) {
		
		Point offset;
		
		offset = calculateOffset(child, parentBox);
		return Point.add(parentBox.center, offset);
	}
	
	
	private Point calculateOffset(QuadtreeNode child,
	                              BoundingBox parentBox) {
		
		double shift;
		
		shift = parentBox.size * 0.25;
		switch (child.getIndex()) {
			case 0: return new Point(-shift, -shift);
			case 1: return new Point(+shift, -shift);
			case 2: return new Point(-shift, +shift);
			case 3: return new Point(+shift, +shift);
			default: return null;
		}
	}
	
	
	private void clearDisplay() {
		
		boundingBox = null;
		for (AxisAlignedPlane plane : halfPlanes) {
			plane = null;
		}
		fireUpdateEvent();
	}
	
	
	public void draw(Graphics2D graphic,
	                 Dimension size) {
		
		// Node bounding box
		if (boundingBox != null) {
			boundingBox.draw(graphic, size);
			for (AxisAlignedPlane halfPlane : halfPlanes) {
				if (halfPlane != null) {
					halfPlane.draw(graphic, size);
				}
			}
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
	
	
	private QuadtreeNode findFirstChild(QuadtreeNode parent,
	                                    BoundsCheck times) {
		
		// Enters on bottom side, then right or left
		if (times.t0[0] < times.t0[1]) {
			if (times.th[0] < times.t0[1])
				return parent.getChild(1);
			else
				return parent.getChild(0);
		}
		
		// Enters on left side, then top or bottom
		else {
			if (times.th[1] < times.t0[0])
				return parent.getChild(2);
			else
				return parent.getChild(0);
		}
	}
	
	
	private QuadtreeNode findNextChild(QuadtreeNode parentNode,
	                                   BoundsCheck childTimes,
	                                   QuadtreeNode childNode) {
		
		switch (childNode.getIndex()) {
			case 0:
				switch (findExitPlane(childTimes)) {
					case XZ_PLANE: return parentNode.getChild(2);
					case YZ_PLANE: return parentNode.getChild(1);
				}
			case 1:
				switch (findExitPlane(childTimes)) {
					case XZ_PLANE: return parentNode.getChild(3);
					case YZ_PLANE: return null;
				}
			case 2:
				switch (findExitPlane(childTimes)) {
					case XZ_PLANE: return null;
					case YZ_PLANE: return parentNode.getChild(3);
				}
			case 3:
				switch (findExitPlane(childTimes)) {
					case XZ_PLANE: return null;
					case YZ_PLANE: return null;
				}
			default: throw new IndexOutOfBoundsException();
		}
	}
	
	
	private Vector2D getChange(QuadtreeNode childNode) {
		
		switch (childNode.getIndex()) {
			case 0: return new Vector2D(0, 0);
			case 1: return new Vector2D(1, 0);
			case 2: return new Vector2D(0, 1);
			case 3: return new Vector2D(1, 1);
			default: throw new IndexOutOfBoundsException();
		}
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
	
	
	private QuadtreeNode getRealChild(QuadtreeNode parent,
	                                  QuadtreeNode childNode,
	                                  Ray ray) {
		
		int index;
		
		if (childNode == null)
			return null;
		
		index = childNode.getIndex();
		if (ray.direction.x < 0) {
			switch (index) {
				case 0 : index = 1; break;
				case 1 : index = 0; break;
				case 2 : index = 3; break;
				case 3 : index = 2; break;
			}
		}
		if (ray.direction.y < 0) {
			switch (index) {
				case 0: index = 2; break;
				case 1: index = 3; break;
				case 2: index = 0; break;
				case 3: index = 1; break;
			}
		}
		return parent.getChild(index);
	}
	
	
	public void print() {
		
		root.printRecursive();
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
				result = sample(ray, rayPrime, root, root, times);
			} else {
				result = sample(ray, ray, root, root, times);
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
	                      QuadtreeNode node,
	                      QuadtreeNode nodePrime,
	                      BoundsCheck times) {
		
		// Check if empty or missed
		if (node.isEmpty()) {
			updateDisplay(Color.RED);
			return 0.0;
		} else {
			updateDisplay(Color.GREEN);
		}
		
		// Leaf take sample data
		if (node.isLeaf())
			return sampleAsLeaf(ray, times);
		
		// Otherwise sample children
		return sampleChildren(ray, rayPrime, node, nodePrime, times);
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
	                              QuadtreeNode parentNode,
	                              QuadtreeNode parentNodePrime,
	                              BoundsCheck parentTimesPrime) {
		
		BoundingBox parentBoundingBox;
		BoundsCheck childTimesPrime;
		double result=0;
		QuadtreeNode childNode, childNodePrime;
		
		// Store current bounding box for all children
		parentBoundingBox = new BoundingBox(boundingBox);
		
		// Traverse children until out of parent
		childNodePrime = findFirstChild(parentNode, parentTimesPrime);
		childNode = getRealChild(parentNode, childNodePrime, ray);
		while (childNodePrime != null) {
			childTimesPrime = updateTimes(childNodePrime, parentTimesPrime);
			updateBoundingBox(childNode, parentBoundingBox);
			updatePlanes(ray, childTimesPrime);
			updateDisplay(Color.YELLOW);
			result += sample(ray, rayPrime, childNode, childNodePrime, childTimesPrime);
			childNodePrime = findNextChild(parentNodePrime, childTimesPrime, childNodePrime);
			childNode = getRealChild(parentNode, childNodePrime, ray);
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
	
	
	private void updateBoundingBox(QuadtreeNode childNode,
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
		
		Point hx, hy;
		
		hx = ray.getPointAt(times.th[0]);
		hy = ray.getPointAt(times.th[1]);
		try {
			halfPlanes[0] = new AxisAlignedPlane(new Point(hx.x,0.0));
			halfPlanes[1] = new AxisAlignedPlane(new Point(0.0,hy.y));
		} catch (Exception e) {
		}
	}
	
	
	private BoundsCheck updateTimes(QuadtreeNode childNode,
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
			ray = new Ray(new Point(300,20), new Vector2D(-1.0,1.0));
			
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

