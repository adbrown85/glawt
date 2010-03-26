/*
 * Drawable.java
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
import java.awt.*;
import java.awt.event.*;




public interface Drawable {
	
	
	public void addAccessory(Drawable accessory);
	
	public void addActionListener(ActionListener listener);
	
	public void clearAccessories();
	
	public void draw(Graphics2D graphic,
	                 Dimension dimension);
	
	public void setColor(Color color);
}

