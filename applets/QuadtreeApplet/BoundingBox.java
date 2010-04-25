/*
 * BoundingBox.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;



/**
 * Axis-aligned box around a shape.
 */
public class BoundingBox extends BasicDrawable
                         implements Drawable {
	
	public double size;
	public Point center, lower, upper;
	
	
	public BoundingBox(double size,
	                   Point center) {
		
		super(Color.BLACK, new BasicStroke());
		
		this.size = size;
		this.center = center;
		this.lower = Point.subtract(center, size*0.5);
		this.upper = Point.add(center, size*0.5);
	}
	
	
	public BoundingBox(BoundingBox other) {
		
		super(Color.BLACK, new BasicStroke());
		
		this.size = other.size;
		this.center = other.center;
		this.lower = other.lower;
		this.upper = other.upper;
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
			bc.t0.set(i, ray.getTimeAt(i,lower.get(i)));
			bc.t1.set(i, ray.getTimeAt(i,upper.get(i)));
/*
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
*/
		}
		return bc;
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
		RayTimePair intersectionTimes;
		DisplayFrame display;
		
		// Start
		boundingBox = new BoundingBox(40.0, new Point(80.0,90.0));
		System.out.println(boundingBox);
		display = new DisplayFrame("Bounding Box");
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
				intersectionTimes = boundsChecks[i].getIntersectionTimes();
				rays[i].addIntersectionAt(intersectionTimes.first);
				rays[i].addIntersectionAt(intersectionTimes.second);
			}
		}
		display.start();
	}
}

