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
	
	double[][] data;
	int size;
	String filename;
	
	
	public VolumeData(String filename)
	                  throws FileNotFoundException {
		
		this.filename = filename;
		load();
	}
	
	
	public double getData() {
		
		
	}
	
	
	private void load()
	                  throws FileNotFoundException {
		
		Scanner scanner;
		
		// Open and get number of lines
		scanner = new Scanner(new File(filename));
		size = scanner.nextInt();
		
		// Load data
		data = new double[size][size];
		for (int i=0; i<size; ++i) {
			for (int j=0; j<size; ++j) {
				data[i][j] = scanner.nextDouble();
			}
		}
	}
	
	
	public void print() {
		
		System.out.printf("Size: %d\n", size);
		for (int i=0; i<size; ++i) {
			for (int j=0; j<size; ++j) {
				System.out.print(data[i][j] + " ");
			}
			System.out.println();
		}
	}
	
	
	public static void main(String[] args) {
		
		VolumeData volumeData;
		
		// Start
		System.out.println();
		System.out.println("****************************************");
		System.out.println("VolumeData");
		System.out.println("****************************************");
		System.out.println();
		
		// Test
		try {
			volumeData = new VolumeData("volume.dat");
			volumeData.print();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		// Finish
		System.out.println();
		System.out.println("****************************************");
		System.out.println("VolumeData");
		System.out.println("****************************************");
		System.out.println();
	}
}

