/*
 * JNumberSpinner.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;



/**
 * JSpinner 
 */
public class JNumberSpinner extends JSpinner {
	
	private static final int DEFAULT_WIDTH=60;
	private static final int INTEGER_TYPE=0;
	private static final int DOUBLE_TYPE=1;
	
	private SpinnerNumberModel numberModel;
	private Object defaultValue;
	private int numberType;
	
	
	
	public JNumberSpinner(int value,
	                      int minimum,
	                      int maximum,
	                      int stepSize) {
		
		super(new SpinnerNumberModel(value, minimum, maximum, stepSize));
		defaultValue = value;
		numberType = INTEGER_TYPE;
	}
	
	
	public JNumberSpinner(double value,
	                      double minimum,
	                      double maximum,
	                      double stepSize) {
		
		super(new SpinnerNumberModel(value, minimum, maximum, stepSize));
		defaultValue = value;
		numberType = DOUBLE_TYPE;
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
	
	
	public void setValue(Object value) {
		
		switch (numberType) {
			case INTEGER_TYPE:
				super.setValue(((Number)value).intValue());
				break;
			case DOUBLE_TYPE:
				super.setValue(((Number)value).doubleValue());
				break;
		}
	}
	
	
	public static void main(String[] args) {
		
		Box box;
		JButton button;
		JFrame frame;
		final JNumberSpinner spinner;
		
		// Box
		box = new Box(BoxLayout.PAGE_AXIS);
		
		// Spinner
		spinner = new JNumberSpinner(0, -100, 100, 1);
		box.add(spinner);
		spinner.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent event) {
				System.out.println("Changed!");
			}
		});
		
		// Button
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

