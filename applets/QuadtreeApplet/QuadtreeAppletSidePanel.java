/*
 * QuadtreeAppletSidePanel.java
 * 
 * Author
 *     Andrew Brown <andrew@andrewdbrown.com>
 */
import java.awt.*;
import java.awt.event.*;
import java.io.FileNotFoundException;
import java.util.Vector;
import javax.swing.*;



/**
 * Side panel for manipulating the ray and volume in the applet.
 */
public class QuadtreeAppletSidePanel extends JPanel
                                     implements ActionListener {
	
	ButtonPanel buttonPanel;
	InputPanel rayPanel, volumePanel;
	QuadtreeAppletScene scene;
	Vector<InputPanel> inputPanels;
	
	
	public QuadtreeAppletSidePanel(QuadtreeAppletScene scene) {
		
		super();
		setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
		init(scene);
	}
	
	
	public void actionPerformed(ActionEvent event) {
		
		String command;
		
		command = event.getActionCommand();
		if (command.equals("Sample")) {
			handleSample();
		} else if (command.equals("Update")) {
			handleUpdate();
		}
	}
	
	
	public void handleSample() {
		
		SwingWorker worker;
		
		// First update
		handleUpdate();
		
		// Do sample
		worker = new SwingWorker<Void,Void>() {
			public Void doInBackground() {
				
				double value;
				
				value = scene.volume.sample(scene.ray);
				System.out.printf("%.2f", value);
				return null;
			}
		};
		worker.execute();
	}
	
	
	public void handleUpdate() {
		
		double size;
		Point center;
		
		// Ray, volume, then confirm
		scene.ray.setOrigin(rayPanel.getValuesFrom("Origin"));
		scene.ray.setDirection(rayPanel.getValuesFrom("Direction"));
		
		// Volume
		size = ((Number)volumePanel.getValueFrom("Size")).doubleValue();
		center = new Point(volumePanel.getValuesFrom("Center"));
		scene.volume.set(size, center);
		
		// Confirm
		updateFields();
		scene.fireUpdateEvent();
	}
	
	
	private void init(QuadtreeAppletScene scene) {
		
		// Fields
		this.scene = scene;
		this.inputPanels = new Vector<InputPanel>();
		
		// Add components
		initRayPanel();
		initVolumePanel();
		add(Box.createVerticalGlue());
		initButtonPanel();
		
		// Finish
		InputPanel.setLabelWidths(inputPanels);
		updateFields();
	}
	
	
	private void initButtonPanel() {
		
		buttonPanel = new ButtonPanel();
		buttonPanel.addButton("Sample");
		buttonPanel.addButton("Update");
		buttonPanel.addActionListener(this);
		buttonPanel.lockHeight();
		add(buttonPanel);
	}
	
	
	private void initRayPanel() {
		
		rayPanel = new InputPanel("Ray");
		rayPanel.addInput("Origin", new JArraySpinner(2,0,0,512,1));
		rayPanel.addInput("Direction", new JArraySpinner(2,0.0,-1.0,1.0,0.1));
		rayPanel.lockHeight();
		add(rayPanel);
		inputPanels.add(rayPanel);
	}
	
	
	private void initVolumePanel() {
		
		volumePanel = new InputPanel("Volume");
		volumePanel.addInput("Size", new JNumberSpinner(50,1,500,1));
		volumePanel.addInput("Center", new JArraySpinner(2,0,0,640,1));
		volumePanel.lockHeight();
		add(volumePanel);
		inputPanels.add(volumePanel);
	}
	
	
	public void updateFields() {
		
		// Ray
		rayPanel.setValuesIn("Origin", scene.ray.origin.toArray());
		rayPanel.setValuesIn("Direction", scene.ray.direction.toArray());
		
		// Volume
		volumePanel.setValueIn("Size", scene.volume.size);
		volumePanel.setValuesIn("Center", scene.volume.center.toArray());
	}
	
	
	public static void main(String[] args)
	                        throws FileNotFoundException {
		
		JFrame frame;
		QuadtreeAppletSidePanel panel;
		QuadtreeAppletScene scene;
		
		// Make scene
		scene = new QuadtreeAppletScene();
		scene.ray = new Ray(new Point(10,10), new Vector2D(1.0,1.0));
		scene.volume = new Volume(60, new Point(100,100), "volume.dat");
		
		// Show in frame
		panel = new QuadtreeAppletSidePanel(scene);
		frame = new JFrame("QuadtreeAppletSidePanel");
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.add(panel);
		frame.pack();
		frame.setVisible(true);
	}
}

