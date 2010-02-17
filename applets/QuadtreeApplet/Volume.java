/*
 * Volume.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;
import java.io.FileNotFoundException;
import java.io.InputStream;
import javax.swing.*;



/**
 * Instance of volume data in scene that can be sampled.
 */
public class Volume extends Shape {
	
	public VolumeData volumeData;
	public Quadtree quadtree;
	
	
	public Volume(double size,
	              Point center,
	              String filename)
	              throws FileNotFoundException {
		
		super(size, center);
		init(new VolumeData(filename));
	}
	
	
	public Volume(double size,
	              Point center,
	              InputStream stream) {
		
		super(size, center);
		init(new VolumeData(stream));
	}
	
	
	public Volume(double size,
	              Point center,
	              VolumeData volumeData) {
		
		super(size, center);
		init(volumeData);
	}
	
	
	public void addActionListener(ActionListener listener) {
		
		quadtree.addActionListener(listener);
	}
	
	
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		super.draw(graphic, dimension);
		volumeData.setBoundingBox(getBoundingBox());
		volumeData.draw(graphic, dimension);
		quadtree.draw(graphic, dimension);
	}
	
	
	private void init(VolumeData volumeData) {
		
		this.volumeData = volumeData;
		this.quadtree = new Quadtree(volumeData);
	}
	
	
	public double sample(Ray ray) {
		
		return quadtree.sample(ray, this);
	}
	
	
	public static void main(String[] args) {
		
		DisplayFrame display;
		Volume volume;
		Ray ray;
		
		try {
			
			// Start
			volume = new Volume(200, new Point(200,200), "volume.dat");
			ray = new Ray(new Point(100,80), new Vector2D(1.0,1.0));
			display = new DisplayFrame("Volume");
			display.add(volume);
			display.add(ray);
			display.start();
			
			// Test
			volume.sample(ray);
		}
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}

