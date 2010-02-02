/*
 * DashedStroke.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.BasicStroke;




/**
 * A dashed stroke for outlines.
 */
public class DashedStroke extends BasicStroke {
	
	
	
	/**
	 * Creates a new %DashedStroke.
	 */
	public DashedStroke() {
		
		super(1.0f,
		      BasicStroke.CAP_BUTT,
		      BasicStroke.JOIN_BEVEL,
		      0.0f,
		      new float[]{3, 5},
		      0.0f);
	}
}

