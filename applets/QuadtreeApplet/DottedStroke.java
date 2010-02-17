/*
 * DottedStroke.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.BasicStroke;




/**
 * A dotted stroke for outlines.
 */
public class DottedStroke extends BasicStroke {
	
	
	
	/**
	 * Creates a new %DottedStroke.
	 */
	public DottedStroke() {
		
		super(1.0f,
		      BasicStroke.CAP_BUTT,
		      BasicStroke.JOIN_BEVEL,
		      0.0f,
		      new float[]{2, 2, 2},
		      0.0f);
	}
}

