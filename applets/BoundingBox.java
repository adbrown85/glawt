/*
 * BoundingBox.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;



/**
 * Axis-aligned box around a shape.
 */
public class BoundingBox implements Drawable {
	
	public Color color;
	public double size;
	public Point center, lower, upper;
	public Stroke stroke;
	
	
	public BoundingBox(double size,
	                   Point center) {
		
		this.color = Color.BLACK;
		this.size = size;
		this.center = center;
		this.lower = Point.subtract(center, size*0.5);
		this.upper = Point.add(center, size*0.5);
		this.stroke = new BasicStroke();
	}
	
	
	public BoundingBox(BoundingBox other) {
		
		this.color = Color.BLACK;
		this.size = other.size;
		this.center = other.center;
		this.lower = other.lower;
		this.upper = other.upper;
		this.stroke = new BasicStroke();
	}
	
	
	public void addActionListener(ActionListener listener) {
		
	}
	
	
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		int size, x, y;
		
		graphic.setColor(color);
		graphic.setStroke(stroke);
		x = (int)(lower.x + 0.5);
		y = (int)(dimension.height - upper.y + 0.5);
		size = (int)(this.size + 0.5);
		graphic.drawRect(x, y, size, size);
	}
	
	
	public BoundsCheck check(Ray ray) {
		
		BoundsCheck bc=new BoundsCheck();
		
		// Calculate times
		for (int i=0; i<2; ++i) {
			bc.t0[i] = ray.getTimeAt(i, lower.get(i));
			bc.t1[i] = ray.getTimeAt(i, upper.get(i));
			if (ray.isDirectionZero(i)) {
				if (ray.origin.get(i) < center.get(i)) {
					bc.th[i] = Double.POSITIVE_INFINITY;
				} else if (ray.origin.get(i) > center.get(i)) {
					bc.th[i] = Double.NEGATIVE_INFINITY;
				} else {
					bc.th[i] = 0.0;
				}
			}
			else {
				bc.th[i] = (bc.t0[i] + bc.t1[i]) * 0.5;
			}
		}
		return bc;
	}
	
	
	public void setColor(Color color) {
		
		this.color = new Color(color.getRGB());
	}
	
	
	public void setStrokeWidth(double width) {
		
		this.stroke = new BasicStroke((float)width);
	}
	
	
	public String toString() {
		
		return String.format("lower=%s, upper=%s", lower, upper);
	}
	
	
	public static void main(String[] args) {
		
		BoundingBox boundingBox;
		BoundsCheck[] boundsChecks=new BoundsCheck[3];
		Ray[] rays=new Ray[3];
		Display display;
		
		// Start
		boundingBox = new BoundingBox(40.0, new Point(80.0,90.0));
		System.out.println(boundingBox);
		display = new Display("Bounding Box");
		display.add(boundingBox);
		
		// Check rays
		rays[0] = new Ray(new Point(30.0,80.0), new Vector2D(1.0,0.0));
		rays[1] = new Ray(new Point(400.0,400.0), new Vector2D(-1.0,-1.0));
		rays[2] = new Ray(new Point(80.0,400.0), new Vector2D(0.0,-1.0));
		for (int i=0; i<rays.length; ++i) {
			boundsChecks[i] = boundingBox.check(rays[i]);
			System.out.println(boundsChecks[i]);
			display.add(rays[i]);
			if (boundsChecks[i].isHit()) {
				System.out.printf("Hit ray %d!\n", i);
				rays[i].addIntersectionAt(boundsChecks[i].tEnter);
				rays[i].addIntersectionAt(boundsChecks[i].tLeave);
			}
		}
		display.start();
	}
}

