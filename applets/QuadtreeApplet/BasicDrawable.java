/*
 * BasicDrawable.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;



/**
 * Provides basic implementations of the required methods.
 */
public class BasicDrawable implements Drawable {
	
	protected ArrayList<ActionListener> actionListeners;
	protected ArrayList<Drawable> accessories;
	protected Color color;
	protected Stroke stroke;
	
	
	public BasicDrawable(Color color,
	                     Stroke stroke) {
		
		this.actionListeners = new ArrayList<ActionListener>();
		this.accessories = new ArrayList<Drawable>();
		this.color = color;
		this.stroke = stroke;
	}
	
	
	public void addAccessory(Drawable accessory) {
		
		accessories.add(accessory);
	}
	
	
	public void addActionListener(ActionListener listener) {
		
		actionListeners.add(listener);
	}
	
	
	public void clearAccessories() {
		
		accessories.clear();
	}
	
	
	protected void fireUpdateEvent() {
		
		ActionEvent event;
		
		event = new ActionEvent(this, 0, "Update");
		for (ActionListener listener : actionListeners) {
			listener.actionPerformed(event);
		}
	}
	
	
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		for (Drawable accessory : accessories) {
			accessory.draw(graphic, dimension);
		}
	}
	
	
	public void setColor(Color color) {
		
		this.color = new Color(color.getRGB());
	}
}

