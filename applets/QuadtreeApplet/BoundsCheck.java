/*
 * BoundsCheck.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.util.Arrays;



/**
 * Stores intersection values.
 */
public class BoundsCheck {
	
	public double[] t0, t1, th;
	
	
	public BoundsCheck() {
		
		t0 = new double[2];
		t1 = new double[2];
		th = new double[2];
	}
	
	
	public RayTimePair getIntersectionTimes() {
		
		double[] tMin, tMax;
		RayTimePair pair;
		
		// Find min and max
		tMin = new double[2];
		tMax = new double[2];
		for (int i=0; i<2; ++i) {
			tMin[i] = Math.min(t0[i], t1[i]);
			tMax[i] = Math.max(t0[i], t1[i]);
		}
		
		// Get times where it enters and exits
		pair = new RayTimePair();
		pair.first = Math.max(tMin[0], tMin[1]);
		pair.second = Math.min(tMax[0], tMax[1]);
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
		
		return String.format("t0=%s, t1=%s, th=%s",
		                     toString(t0), toString(t1), toString(th));
	}
	
	
	public String toString(double[] array) {
		
		return String.format("[%.1f,%.1f]", array[0], array[1]);
	}
	
	
	public static void main(String[] args) {
		
		BoundsCheck BoundsCheck;
		
		// Test
		BoundsCheck = new BoundsCheck();
		System.out.println(BoundsCheck);
		System.out.println("isHit: " + BoundsCheck.isHit());
	}
}

