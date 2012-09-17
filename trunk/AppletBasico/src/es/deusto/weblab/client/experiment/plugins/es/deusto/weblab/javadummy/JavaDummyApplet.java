package es.deusto.weblab.client.experiment.plugins.es.deusto.weblab.javadummy;

import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedInputStream;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.Random;
import java.util.Timer;
import java.util.TimerTask;

import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;

import es.deusto.weblab.client.experiment.plugins.es.deusto.weblab.javadummy.commands.PulseCommand;
import es.deusto.weblab.client.experiment.plugins.java.Command;
import es.deusto.weblab.client.experiment.plugins.java.ConfigurationManager;
import es.deusto.weblab.client.experiment.plugins.java.ICommandCallback;
import es.deusto.weblab.client.experiment.plugins.java.ResponseCommand;
import es.deusto.weblab.client.experiment.plugins.java.SerialRead3;
import es.deusto.weblab.client.experiment.plugins.java.SimpleRead2;
import es.deusto.weblab.client.experiment.plugins.java.WebLabApplet;
import jssc.SerialPort;
import jssc.SerialPortException;

public class JavaDummyApplet extends WebLabApplet {
	private static final long serialVersionUID = 1L;

	public static final String WEBCAM_IMAGE_URL_PROPERTY_NAME = "webcam.image";
	public static final String DEFAULT_WEBCAM_IMAGE_URL       = "/img/logo.png";
	
	private final JLabel timeLabel;
	private Timer expirationTimer = null;
	private final JLabel messages;
	private final JPanel experimentPanel;

	public JavaDummyApplet(){
		
		this.experimentPanel = new JPanel();
		this.experimentPanel.setLayout(new BoxLayout(this.experimentPanel, BoxLayout.Y_AXIS));
		
	
		final JPanel messagesPanel = new JPanel();
		messagesPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		this.experimentPanel.add(messagesPanel);
		
		this.timeLabel = new JLabel("<time>");
		this.timeLabel.setForeground(Color.green);
		
		this.messages = new JLabel();
		this.messages.setForeground(Color.blue);
		
		messagesPanel.add(this.timeLabel);
		messagesPanel.add(this.messages);
		
		final JPanel buttonsPanel = new JPanel();
        buttonsPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		this.experimentPanel.add(buttonsPanel);
		final JButton button = new JButton("Receber Dados");
		buttonsPanel.add(button);
		
		
		final JPanel textPanel = new JPanel();
		textPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		textPanel.add(new JLabel("Este é um Java applet"));
		this.getContentPane().add(textPanel);
	
	}
	


	
	public void SerialRead3() {
	
        SerialPort serialPort = new SerialPort("COM6");
        try {
            serialPort.openPort();//Open serial port
            serialPort.setParams(9600, 8, 1, 0);//Set params.
            
            boolean b = true;
            
            while (b=true){
            	
            	byte[] buffer = serialPort.readBytes(100);//Read 10 bytes from serial port
            	String source2 = new String(buffer);
                //System.out.println(source2);
            	JavaDummyApplet.this.messages.setText("Recebido:" + source2);
            	
            }
            serialPort.closePort();//Close serial port
        }
        catch (SerialPortException ex) {
            System.out.println(ex);
        }
        
    }
	
	
	public void startInteraction() {
		this.getContentPane().add(this.experimentPanel);
		this.messages.setText("Interaction started");
		this.repaint();
	}
	
	public void setTime(int time) {
		this.timeLabel.setText("" + time);
		
		final TimerTask timerTask = new TimerTask(){
			public void run() {
				final int current = Integer.parseInt(JavaDummyApplet.this.timeLabel.getText());
				if(current == 0)
					//JavaDummyApplet.this.getBoardController().onClean();
				JavaDummyApplet.this.timeLabel.setText("" + (current - 1));
			}
		};
		this.expirationTimer = new Timer();
		this.expirationTimer.schedule(timerTask, 0, 1000);
	}
	
	public void end() {
				if(this.expirationTimer != null)
			this.expirationTimer.cancel();
	}	
}
