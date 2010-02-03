/*
 * DataSource.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */



/**
 * Interface for a container holding data that can be retrieved.
 */
public interface DataSource {
	
	
	public double getPitch();
	
	public double getSample(Point point);
	
	public int getSize();
}

