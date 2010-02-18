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
import javax.swing.event.*;



/**
 * Side panel for manipulating the ray and volume in the applet.
 */
public class QuadtreeAppletSidePanel extends JPanel
                                     implements ActionListener,
                                                ChangeListener {
	
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
		}
	}
	
	
	public void handleSample() {
		
		SwingWorker worker;
		
		// Do sample
		worker = new SwingWorker<Double,Void>() {
			public Double doInBackground() {
				return scene.volume.sample(scene.ray);
			}
		};
		worker.execute();
	}
	
	
	private void init(QuadtreeAppletScene scene) {
		
		// Fields
		this.scene = scene;
		this.inputPanels = new Vector<InputPanel>();
		
		// Add components
		initRayPanel();
		initVolumePanel();
		initButtonPanel();
		add(Box.createVerticalGlue());
		
		// Finish
		InputPanel.setLabelWidths(inputPanels);
	}
	
	
	private void initButtonPanel() {
		
		buttonPanel = new ButtonPanel();
		buttonPanel.addButton("Sample");
		buttonPanel.addActionListener(this);
		buttonPanel.lockHeight();
		add(buttonPanel);
	}
	
	
	private void initRayPanel() {
		
		// Create and add
		rayPanel = new InputPanel("Ray");
		rayPanel.addInput("Origin", new JArraySpinner(2,0,0,640,10));
		rayPanel.addInput("Direction", new JArraySpinner(2,0.0,-1.0,1.0,0.1));
		rayPanel.lockHeight();
		add(rayPanel);
		inputPanels.add(rayPanel);
		
		// Set values and add listener
		rayPanel.setValuesIn("Origin", scene.ray.origin.toArray());
		rayPanel.setValuesIn("Direction", scene.ray.direction.toArray());
		rayPanel.addChangeListener(this);
	}
	
	
	private void initVolumePanel() {
		
		// Create and add
		volumePanel = new InputPanel("Volume");
		volumePanel.addInput("Size", new JNumberSpinner(50,1,500,10));
		volumePanel.addInput("Center", new JArraySpinner(2,0,0,640,10));
		volumePanel.lockHeight();
		add(volumePanel);
		inputPanels.add(volumePanel);
		
		// Set values and add listener
		volumePanel.setValueIn("Size", scene.volume.size);
		volumePanel.setValuesIn("Center", scene.volume.center.toArray());
		volumePanel.addChangeListener(this);
	}
	
	
	public void stateChanged(ChangeEvent event) {
		
		double size;
		Point center;
		
		// Ray attributes
		scene.ray.setOrigin(rayPanel.getValuesFrom("Origin"));
		scene.ray.setDirection(rayPanel.getValuesFrom("Direction"));
		scene.ray.clearAccessories();
		
		// Volume attributes
		size = ((Number)volumePanel.getValueFrom("Size")).doubleValue();
		center = new Point(volumePanel.getValuesFrom("Center"));
		scene.volume.set(size, center);
		
		// Signal
		scene.fireUpdateEvent();
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

