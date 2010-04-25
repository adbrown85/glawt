/*
 * BoundsCheck.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */



/**
 * Stores intersection values.
 */
public class BoundsCheck {
	
	public Vector2D t0, t1, th;
	
	
	public BoundsCheck() {
		
		t0 = new Vector2D();
		t1 = new Vector2D();
		th = new Vector2D();
	}
	
	
	public RayTimePair getIntersectionTimes() {
		
		RayTimePair pair;
		Vector2D tMin, tMax;
		
		// Initialize
		tMin = new Vector2D();
		tMax = new Vector2D();
		
		// Find min and max
		for (int i=0; i<2; ++i) {
			tMin.set(i, Math.min(t0.get(i), t1.get(i)));
			tMax.set(i, Math.max(t0.get(i), t1.get(i)));
		}
		
		// Get times where it enters and exits
		pair = new RayTimePair();
		pair.first = Math.max(tMin.x, tMin.y);
		pair.second = Math.min(tMax.x, tMax.y);
		return pair;
	}
	
	
	public boolean isHit() {
		
		RayTimePair pair;
		
		// Check enter and exit
		pair = getIntersectionTimes();
		if (pair.second < 0) {
			return false;
		} else {
			return pair.first < pair.second;
		}
	}
	
	
	public String toString() {
		
		return String.format("t0=%s, t1=%s, th=%s", t0, t1, th);
	}
	
	
/*
	public String toString(double[] array) {
		
		return String.format("[%.1f,%.1f]", array[0], array[1]);
	}
*/
	
	
	public static void main(String[] args) {
		
		BoundsCheck BoundsCheck;
		
		// Test
		BoundsCheck = new BoundsCheck();
		System.out.println(BoundsCheck);
		System.out.println("isHit: " + BoundsCheck.isHit());
	}
}

