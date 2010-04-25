/*
 * QuadtreeViewer.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.io.FileNotFoundException;



/**
 * Tree with nodes that have four children to accelerate data access.
 */
public class QuadtreeViewer extends BasicDrawable
                            implements Drawable {
	
	private static final long SLEEP_TIME=1000;
	
	private BoundingBox box;
	private AxisAlignedPlane[] planes;
	private Ray ray;
	
	
	public QuadtreeViewer(Ray ray) {
		
		super(null, null);
		
		// Display
		this.box = null;
		this.planes = new AxisAlignedPlane[6];
		this.ray = ray;
	}
	
	
	public void addIntersectionAt(double time) {
		
		ray.addIntersectionAt(time);
		fireUpdateEvent();
		sleep();
	}
	
	
	public void clear() {
		
		ray.clearAccessories();
		box = null;
		for (int i=0; i<planes.length; ++i) {
			planes[i] = null;
		}
		fireUpdateEvent();
	}
	
	
	public void draw(Graphics2D graphic,
	                 Dimension size) {
		
		// Node bounding box
		if (box != null) {
			for (AxisAlignedPlane plane : planes) {
				if (plane != null) {
					plane.draw(graphic, size);
				}
			}
			box.draw(graphic, size);
		}
		
		// Accessories
		super.draw(graphic, size);
	}
	
	
	public void sleep() {
		
		try {
			Thread.sleep(SLEEP_TIME);
		} catch (InterruptedException e) {
			System.err.println("[QuadtreeViewer] Interrupted in sleep.");
		}
	}
	
	
	public void update(BoundsCheck times) {
		
		updatePlanes(times);
		updateBoundingBox(times);
		update(Color.YELLOW);
	}
	
	
	public void update(Color color) {
		
		box.setColor(color);
		box.setStrokeWidth(3.0);
		fireUpdateEvent();
		sleep();
	}
	
	
	private void updateBoundingBox(BoundsCheck times) {
		
		double size, thx, thy, x0, x1, xh, yh;
		Point center=new Point();
		
		// Calculate size
		x0 = ray.getValueAt(0, times.t0.x);
		x1 = ray.getValueAt(0, times.t1.x);
		size = Math.abs(x1 - x0);
		
		// Calculate center
		thx = (times.t0.x + times.t1.x) * 0.5;
		thy = (times.t0.y + times.t1.y) * 0.5;
		center.x = ray.getValueAt(0, thx);
		center.y = ray.getValueAt(1, thy);
		
		// Create new bounding box
		box = new BoundingBox(size, center);
	}
	
	
	private void updatePlanes(BoundsCheck times) {
		
		double thx, thy, x0, y0, x1, y1, xh, yh;
		
		// Find half times
		thx = (times.t0.x + times.t1.x) * 0.5;
		thy = (times.t0.y + times.t1.y) * 0.5;
		
		// Calculate actual positions
		x0 = ray.getValueAt(0, times.t0.x);
		y0 = ray.getValueAt(1, times.t0.y);
		x1 = ray.getValueAt(0, times.t1.x);
		y1 = ray.getValueAt(1, times.t1.y);
		xh = ray.getValueAt(0, thx);
		yh = ray.getValueAt(1, thy);
		
		// Update planes
		try {
			planes[0] = new AxisAlignedPlane(new Point(x0,0.0));
			planes[1] = new AxisAlignedPlane(new Point(0.0,y0));
			planes[2] = new AxisAlignedPlane(new Point(x1,0.0));
			planes[3] = new AxisAlignedPlane(new Point(0.0,y1));
			planes[4] = new AxisAlignedPlane(new Point(xh,0.0));
			planes[5] = new AxisAlignedPlane(new Point(0.0,yh));
		} catch (Exception e) {
		}
	}
	
	
	public static void main(String[] args)
	                        throws Exception {
		
		BoundingBox box;
		BoundsCheck times;
		DisplayFrame display;
		QuadtreeTexture texture;
		QuadtreeViewer viewer;
		Ray ray;
		Shape shape;
		VolumeData data;
		
		try {
			
			// Setup
			shape = new Shape(300, new Point(200,200));
			data = new VolumeData("volume.dat", shape);
			texture = new QuadtreeTexture(data);
			ray = new Ray(new Point(250,20), new Vector2D(-1.0,1.0));
			viewer = new QuadtreeViewer(ray);
			
			// Show
			display = new DisplayFrame("Quadtree");
			display.add(viewer);
			display.add(shape);
			display.add(data);
			display.add(ray);
			display.start();
			
			// Simulate
			box = shape.getBoundingBox();
			viewer.sleep();
			times = box.check(ray);
			viewer.update(times);
			viewer.update(Color.RED);
			viewer.update(Color.GREEN);
			viewer.clear();
		}
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}

