/*
 * JNumberSpinner.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;



/**
 * JSpinner 
 */
public class JNumberSpinner extends JSpinner {
	
	private static final int DEFAULT_WIDTH=60;
	
	private SpinnerNumberModel numberModel;
	private Object defaultValue;
	
	
	
	public JNumberSpinner(int value,
	                      int minimum,
	                      int maximum,
	                      int stepSize) {
		
		super(new SpinnerNumberModel(value, minimum, maximum, stepSize));
		defaultValue = value;
	}
	
	
	public JNumberSpinner(double value,
	                      double minimum,
	                      double maximum,
	                      double stepSize) {
		
		super(new SpinnerNumberModel(value, minimum, maximum, stepSize));
		defaultValue = value;
	}
	
	
	public void reset() {
		
		setValue(defaultValue);
	}
	
	
	public Dimension getPreferredSize() {
		
		Dimension size;
		
		size = super.getPreferredSize();
		size.width = DEFAULT_WIDTH;
		return size;
	}
	
	
	public static void main(String[] args) {
		
		Box box;
		JButton button;
		JFrame frame;
		final JNumberSpinner spinner;
		
		// Components
		box = new Box(BoxLayout.PAGE_AXIS);
		spinner = new JNumberSpinner(0, -100, 100, 1);
		box.add(spinner);
		button = new JButton("Reset");
		box.add(button);
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				spinner.reset();
			}
		});
		
		// Show
		frame = new JFrame("JNumberSpinner");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setContentPane(box);
		frame.pack();
		frame.setVisible(true);
	}
}

