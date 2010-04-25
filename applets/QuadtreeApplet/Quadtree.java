/*
 * Quadtree.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.*;
import java.awt.event.*;
import java.io.FileNotFoundException;
import java.util.ArrayList;


public class Quadtree extends BasicDrawable
                      implements Drawable {
	
	private static final int FIRST_STEP=1, SECOND_STEP=2;
	private static final int FIRST_CHILD=0, ROOT_KEY=0;
	private static final int XZ_PLANE=0;
	private static final int YZ_PLANE=1;
	private static final int MAX_HEIGHT=9;
	private static final int[] jump={1,5,21,85,341,1365,5461,21845,87381};
	
	public BoundsCheck[] t=new BoundsCheck[MAX_HEIGHT];
	public BoundingBox box;
	public float result;
	public int c, d, height;                     // child depth, depth, height
	public int[] step=new int[MAX_HEIGHT];
	public NodeIndex[] node=new NodeIndex[MAX_HEIGHT];
	public QuadtreeTexture texture;
	public QuadtreeViewer viewer;
	public Ray ray;
	public Shape shape;
	
	
	public Quadtree(QuadtreeTexture texture,
	                Ray ray,
	                Shape shape) {
		
		super(null, null);
		
		// Copy inputs
		this.texture = texture;
		this.ray = ray;
		this.shape = shape;
		
		// Initialize others
		this.box = new BoundingBox(shape.getBoundingBox());
		this.height = texture.height;
		this.viewer = new QuadtreeViewer(ray);
		
		// Initialize node, step, times
		for (int i=0; i<MAX_HEIGHT; ++i) {
			node[i] = new NodeIndex(-1, -1);
			step[i] = FIRST_STEP;
			t[i] = new BoundsCheck();
		}
		node[0] = new NodeIndex(ROOT_KEY, FIRST_CHILD);
	}
	
	
	public void addActionListener(ActionListener listener) {
		
		super.addActionListener(listener);
		viewer.addActionListener(listener);
	}
	
	
	public void draw(Graphics2D graphic,
	                 Dimension size) {
		
		viewer.draw(graphic, size);
	}
	
	
	private void findEntryChild() {
		
		// Enters on bottom side, then right or left
		if (t[d].t0.x < t[d].t0.y) {
			if (t[d].th.x < t[d].t0.y) {
				updateChild(1);
			} else {
				updateChild(0);
			}
		}
		
		// Enters on left side, then top or bottom
		else {
			if (t[d].th.y < t[d].t0.x) {
				updateChild(2);
			} else {
				updateChild(0);
			}
		}
	}
	
	
	private int findExitPlane() {
		
		if (t[c].t1.x < t[c].t1.y) {
			return YZ_PLANE;
		} else {
			return XZ_PLANE;
		}
	}
	
	
	private void findNextChild() {
		
		int exitPlane;
		
		exitPlane = findExitPlane();
		switch (node[c].name) {
			case 0:
				switch (exitPlane) {
					case XZ_PLANE: updateChild(2); return;
					case YZ_PLANE: updateChild(1); return;
				}
			case 1:
				switch (exitPlane) {
					case XZ_PLANE: updateChild(3); return;
					case YZ_PLANE: node[c].name = -1; return;
				}
			case 2:
				switch (exitPlane) {
					case XZ_PLANE: node[c].name = -1; return;
					case YZ_PLANE: updateChild(3); return;
				}
			case 3:
				node[c].name = -1; return;
			default: throw new IndexOutOfBoundsException();
		}
	}
	
	
	private double sample() {
		
		// Initialize
		t[0] = box.check(ray);
		viewer.update(t[0]);
		
		// While in volume
		while (d >= 0) {
			switch (step[d]) {
			case FIRST_STEP:
				
				// Check if empty
				if (texture.isEmpty(node[d].key)) {
					viewer.update(Color.RED);
					--d;
					continue;
				} else {
					viewer.update(Color.GREEN);
				}
				
				// If a leaf, sample it
				if (d == height) {
					sampleAsLeaf();
					--d;
					continue;
				}
				
				// Calculate half times
				t[d].th.x = (t[d].t0.x + t[d].t1.x) * 0.5;
				t[d].th.y = (t[d].t0.y + t[d].t1.y) * 0.5;
			
			case SECOND_STEP:
				
				// Find entry or next child
				c = d + 1;
				if (node[c].name == -1) {
					findEntryChild();
				} else {
					findNextChild();
					if (node[c].name == -1) {
						--d;
						continue;
					}
				}
				
				// Move to child
				updateEndTimes();
				step[d] = SECOND_STEP;
				step[c] = FIRST_STEP;
				++d;
				viewer.update(t[c]);
			}
		}
		
		// Finish
		viewer.clear();
		return result;
	}
	
	
	private void sampleAsLeaf() {
		
		double time;
		RayTimePair pair;
		
		pair = t[d].getIntersectionTimes();
		time = pair.first + 10.0;
		while (time < pair.second) {
			result += 0.1;
			viewer.addIntersectionAt(time);
			time += 10.0;
		}
	}
	
	
	private void updateChild(int cName) {
		
		// Calculate key and name for child
		node[c].name = cName;
		node[c].key = (node[d].key + 1) + (cName * jump[height-c]);
	}
	
	
	private void updateEndTimes() {
		
		// Calculate times for child from parent
		switch (node[c].name) {
		case 0:
			t[c].t0.x = t[d].t0.x;
			t[c].t0.y = t[d].t0.y;
			t[c].t1.x = t[d].th.x;
			t[c].t1.y = t[d].th.y;
			break;
		case 1:
			t[c].t0.x = t[d].th.x;
			t[c].t0.y = t[d].t0.y;
			t[c].t1.x = t[d].t1.x;
			t[c].t1.y = t[d].th.y;
			break;
		case 2:
			t[c].t0.x = t[d].t0.x;
			t[c].t0.y = t[d].th.y;
			t[c].t1.x = t[d].th.x;
			t[c].t1.y = t[d].t1.y;
			break;
		case 3:
			t[c].t0.x = t[d].th.x;
			t[c].t0.y = t[d].th.y;
			t[c].t1.x = t[d].t1.x;
			t[c].t1.y = t[d].t1.y;
			break;
		}
	}
	
	
	public static void main(String args[]) {
		
		DisplayFrame display;
		double result;
		Quadtree quadtree;
		QuadtreeTexture texture;
		Ray ray;
		Shape shape;
		VolumeData data;
		
		// Start
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Quadtree");
		System.out.println("****************************************");
		System.out.println();
		
		try {
			
			// Set up
			shape = new Shape(300, new Point(200,200));
			data = new VolumeData("volume.dat", shape);
			texture = new QuadtreeTexture(data);
			ray = new Ray(new Point(45,20), new Vector2D(1.0,1.0));
			quadtree = new Quadtree(texture, ray, shape);
			
			// Show
			display = new DisplayFrame("QuadtreeSampler");
			display.add(data);
			display.add(shape);
			display.add(quadtree);
			display.add(ray);
			display.start();
			
			// Run
			result = quadtree.sample();
			System.out.printf("result = %.2f\n", result);
		}
		catch (FileNotFoundException e) {
			System.err.println(e.getMessage());
		}
		
		// Finish
		System.out.println();
		System.out.println("****************************************");
		System.out.println("Quadtree");
		System.out.println("****************************************");
		System.out.println();
	}
}

