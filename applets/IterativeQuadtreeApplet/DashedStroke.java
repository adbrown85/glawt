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
	
	
	public DashedStroke() {
		
		super(1.0f,
		      BasicStroke.CAP_BUTT,
		      BasicStroke.JOIN_BEVEL,
		      0.0f,
		      new float[]{3, 5},
		      0.0f);
	}
	
	
	public DashedStroke(double width) {
		
		super((float)width,
		      BasicStroke.CAP_BUTT,
		      BasicStroke.JOIN_BEVEL,
		      0.0f,
		      new float[]{(float)width*2, (float)width*4},
		      0.0f);
	}
}

