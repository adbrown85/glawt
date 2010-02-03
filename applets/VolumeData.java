/*
 * VolumeData.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;



/**
 * Stores volumetric data.
 */
public class VolumeData implements DataSource {
	
	private double pitch;
	private double[][] data;
	private int size;
	private String filename;
	
	
	public VolumeData(String filename)
	                  throws FileNotFoundException {
		
		this.filename = filename;
		load();
	}
	
	
	public double getPitch() {
		
		return pitch;
	}
	
	
	public double getSample(Point point) {
		
		int x, y;
		
		x = (int)(point.x * size - 0.5);
		y = (int)(point.y * size - 0.5);
		return data[y][x];
	}
	
	
	public int getSize() {
		
		return size;
	}
	
	
	private void load()
	                  throws FileNotFoundException {
		
		Scanner scanner;
		
		// Open and set size and pitch
		scanner = new Scanner(new File(filename));
		size = scanner.nextInt();
		pitch = 1.0 / size;
		
		// Load data
		data = new double[size][size];
		for (int i=size-1; i>=0; --i) {
			for (int j=0; j<size; ++j) {
				data[i][j] = scanner.nextDouble();
			}
		}
	}
	
	
	public void print() {
		
		System.out.printf("Size: %d\n", size);
		for (int i=size-1; i>=0; --i) {
			for (int j=0; j<size; ++j) {
				System.out.print(data[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	
	public static void main(String[] args) {
		
		double data, halfPitch, pitch;
		VolumeData volumeData;
		
		try {
			
			// Load and print
			volumeData = new VolumeData("volume.dat");
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
		}
		catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}

