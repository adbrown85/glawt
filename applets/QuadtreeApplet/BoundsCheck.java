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
	
	public double tEnter, tLeave;
	public double[] t0, t1, th, tMin, tMax;
	
	
	public BoundsCheck() {
		
		t0 = new double[2];
		t1 = new double[2];
		th = new double[2];
		tMin = new double[2];
		tMax = new double[2];
	}
	
	
	public boolean isHit() {
		
		// Set min and max
		for (int i=0; i<2; ++i) {
			tMin[i] = Math.min(t0[i], t1[i]);
			tMax[i] = Math.max(t0[i], t1[i]);
		}
		
		// Check enter and leave
		tEnter = Math.max(tMin[0], tMin[1]);
		tLeave = Math.min(tMax[0], tMax[1]);
		if (tLeave < 0) {
			return false;
		} else {
			return tEnter < tLeave;
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

