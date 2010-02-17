/*
 * VolumeData.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;



/**
 * Stores volumetric data.
 */
public class VolumeData implements DataSource,
                                   Drawable {
	
	private double pitch, threshold;
	private double[][] data;
	private int size;
	private String filename;
	
	private BoundingBox box;
	
	
	public VolumeData(String filename)
	                  throws FileNotFoundException {
		
		this.filename = filename;
		load();
	}
	
	
	public void addActionListener(ActionListener listener) {
		
	}
	
	
	public void draw(Graphics2D graphic,
	                 Dimension dimension) {
		
		double halfPitch, halfSize;
		int ovalSize, ovalX, ovalY, sample;
		
		halfPitch = pitch * 0.5;
		ovalSize = (int)(box.size / size * 0.8);
		halfSize = ovalSize * 0.5;
		for (double y=halfPitch; y<1.0; y+=pitch) {
			for (double x=halfPitch; x<1.0; x+=pitch) {
				sample = (int)(getSample(new Point(x, y)) * 255);
				ovalX = (int)(box.lower.x + box.size * x - halfSize);
				ovalY = (int)(box.lower.y + box.size * y - halfSize);
				ovalY = dimension.height - ovalY - ovalSize;
				graphic.setColor(new Color(sample,sample,sample));
				graphic.fillOval(ovalX, ovalY, ovalSize, ovalSize);
				graphic.setColor(Color.BLACK);
				graphic.drawOval(ovalX, ovalY, ovalSize, ovalSize);
			}
		}
	}
	
	
	/**
	 * Returns the space between samples in the data.
	 * 
	 * Pitch is measured in unit coordinates where the left and bottom edges 
	 * are zero and the right and top edges are one.  Officially pitch is 
	 * the inverse of size.
	 */
	public double getPitch() {
		
		return pitch;
	}
	
	
	/**
	 * Samples the data.
	 * 
	 * @param point
	 *     Spot in the data measured in unit coordinates from 0-1.
	 */
	public double getSample(Point point) {
		
		int x, y;
		
		x = (int)(point.x * size - 0.5);
		y = (int)(point.y * size - 0.5);
		return data[y][x];
	}
	
	
	/**
	 * Returns the size of the data.
	 * 
	 * Since the data is assumed to be square, the size is the number of 
	 * samples in both directions.  In other words, if the data has four row 
	 * and four columns of samples, for a total of sixteen samples, the size 
	 * is defined to be four.
	 */
	public int getSize() {
		
		return size;
	}
	
	
	public double getThreshold() {
		
		return threshold;
	}
	
	
	/**
	 * Loads all the samples from a file.
	 * 
	 * First sets the size to the first value in the file, setting the pitch 
	 * accordingly, and the threshold to the second value.  Then loads all the 
	 * samples by putting the values in earlier lines at the top of the data.  
	 * That way the values should look the same in your text editor as they do 
	 * on screen.
	 */
	private void load()
	                  throws FileNotFoundException {
		
		Scanner scanner;
		
		// Open and set size and pitch
		scanner = new Scanner(new File(filename));
		size = scanner.nextInt();
		pitch = 1.0 / size;
		threshold = scanner.nextDouble();
		
		// Load data
		data = new double[size][size];
		for (int i=size-1; i>=0; --i) {
			for (int j=0; j<size; ++j) {
				data[i][j] = scanner.nextDouble();
			}
		}
	}
	
	
	/**
	 * Prints all of the samples from top to bottom.
	 */
	public void print() {
		
		System.out.printf("Size: %d\n", size);
		for (int i=size-1; i>=0; --i) {
			for (int j=0; j<size; ++j) {
				System.out.print(data[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	
	public void setBoundingBox(BoundingBox boundingBox) {
		
		this.box = new BoundingBox(boundingBox);
	}
	
	
	public static void main(String[] args) {
		
		DisplayFrame display;
		double data, halfPitch, pitch;
		VolumeData volumeData;
		
		try {
			
			// Load and print
			volumeData = new VolumeData("volume.dat");
			volumeData.setBoundingBox(new BoundingBox(200, new Point(300,300)));
			volumeData.print();
			
			// getSample and getPitch
			System.out.println();
			pitch = volumeData.getPitch();
			halfPitch = pitch * 0.5;
			for (double y=1.0-halfPitch; y>0.0; y-=pitch) {
				for (double x=halfPitch; x<1.0; x+=pitch) {
					data = volumeData.getSample(new Point(x, y));
					System.out.print(data + " ");
				}
				System.out.println();
			}
			
			// Display
			display = new DisplayFrame("VolumeData");
			display.add(volumeData);
			display.start();
		}
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}

