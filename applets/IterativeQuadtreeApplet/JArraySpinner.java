/*
 * JArraySpinner.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import javax.swing.*;
import javax.swing.event.*;



/**
 * 
 */
public class JArraySpinner extends Box
                           implements ChangeListener {
	
	private JNumberSpinner[] spinners;
	private ArrayList<ChangeListener> changeListeners;
	
	
	public JArraySpinner(int length,
	                     int value,
	                     int minimum,
	                     int maximum,
	                     int stepSize) {
		
		super(BoxLayout.LINE_AXIS);
		
		// Listeners
		initListeners();
		
		// Spinners
		spinners = new JNumberSpinner[length];
		for (int i=0; i<spinners.length; ++i) {
			spinners[i] = new JNumberSpinner(value, minimum, maximum, stepSize);
		}
		addSpinners();
	}
	
	
	public JArraySpinner(int length,
	                     double value,
	                     double minimum,
	                     double maximum,
	                     double stepSize) {
		
		super(BoxLayout.LINE_AXIS);
		
		// Listeners
		initListeners();
		
		// Spinners
		spinners = new JNumberSpinner[length];
		for (int i=0; i<spinners.length; ++i) {
			spinners[i] = new JNumberSpinner(value, minimum, maximum, stepSize);
		}
		addSpinners();
	}
	
	
	public void addChangeListener(ChangeListener listener) {
		
		changeListeners.add(listener);
	}
	
	
	private void addSpinner(JNumberSpinner spinner) {
		
		add(spinner);
		spinner.addChangeListener(this);
	}
	
	
	private void addSpinners() {
		
		if (spinners.length == 0)
			return;
		
		addSpinner(spinners[0]);
		for (int i=1; i<spinners.length; ++i) {
			add(Box.createRigidArea(new Dimension(4,1)));
			addSpinner(spinners[i]);
		}
	}
	
	
	public int getLength() {
		
		return spinners.length;
	}
	
	
	public Object[] getValues() {
		
		Object[] values;
		
		values = new Object[getLength()];
		for (int i=0; i<getLength(); ++i) {
			values[i] = spinners[i].getValue();
		}
		return values;
	}
	
	
	private void initListeners() {
		
		changeListeners = new ArrayList<ChangeListener>();
	}
	
	
	public void reset() {
		
		for (JNumberSpinner spinner : spinners) {
			spinner.reset();
		}
	}
	
	
	public void setValues(Object[] values) {
		
		for (int i=0; i<getLength(); ++i) {
			spinners[i].setValue(values[i]);
		}
	}
	
	
	public void stateChanged(ChangeEvent event) {
		
		for (ChangeListener listener : changeListeners) {
			listener.stateChanged(event);
		}
	}
	
	
	public static void main(String[] args) {
		
		Box box;
		final JArraySpinner spinner;
		JButton button;
		JFrame frame;
		Object[] values;
		
		// Spinner
		box = new Box(BoxLayout.PAGE_AXIS);
		spinner = new JArraySpinner(2, 0, 0, 100, 1);
		box.add(spinner);
		spinner.addChangeListener(new ChangeListener() {
			public void stateChanged(ChangeEvent event) {
				System.out.println("Changed!");
			}
		});
		
		// Print button
		button = new JButton("Print");
		box.add(button);
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				Object[] values;
				values = spinner.getValues();
				for (Object value : values) {
					System.out.print(value + " ");
				}
				System.out.println();
			}
		});
		
		// Reset button
		button = new JButton("Reset");
		box.add(button);
		button.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent event) {
				spinner.reset();
			}
		});
		
		// Show
		frame = new JFrame("JArraySpinner");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setContentPane(box);
		frame.pack();
		frame.setVisible(true);
		
		// Set values
		values = new Object[2];
		values[0] = 20;
		values[1] = 30;
		spinner.setValues(values);
	}
}

