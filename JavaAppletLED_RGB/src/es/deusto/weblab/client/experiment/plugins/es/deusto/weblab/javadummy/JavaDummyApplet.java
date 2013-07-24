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

import es.deusto.weblab.client.experiment.plugins.java.ConfigurationManager;
import es.deusto.weblab.client.experiment.plugins.java.WebLabApplet;

import org.asteriskjava.iax.ui.BeanCan;
import org.asteriskjava.iax.ui.BeanCanApplet;

public class JavaDummyApplet extends WebLabApplet implements ActionListener {
	private static final long serialVersionUID = 1L;

	public static final String WEBCAM_IMAGE_URL_PROPERTY_NAME = "webcam.image";
	public static final String DEFAULT_WEBCAM_IMAGE_URL       = "/img/webcam/espectrofotometro_01.jpg";
	
	private final JPanel webcamPanel;
	public final JLabel timeLabel;
	private Timer webcamTimer = null;
	private Timer expirationTimer = null;
	public final JLabel messages;
	private final JPanel experimentPanel;
	
	BeanCan bc;
	
	
	public JavaDummyApplet(){
		
		this.experimentPanel = new JPanel();
		this.experimentPanel.setLayout(new BoxLayout(this.experimentPanel, BoxLayout.Y_AXIS));
		
		this.webcamPanel = new JPanel();
		this.experimentPanel.add(this.webcamPanel);
		
		final JPanel messagesPanel = new JPanel();
		messagesPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		this.experimentPanel.add(messagesPanel);
		
		this.timeLabel = new JLabel("<time>");
		this.timeLabel.setForeground(Color.red);
		
		this.messages = new JLabel();
		this.messages.setForeground(Color.blue);
		
		messagesPanel.add(this.timeLabel);
		messagesPanel.add(this.messages);
		
		final JPanel buttonsPanel = new JPanel();
		buttonsPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		this.experimentPanel.add(buttonsPanel);
		
		JButton button = new JButton("Voz !");
		buttonsPanel.add(button);	
		button.addActionListener(this);


		final JPanel textPanel = new JPanel();
		textPanel.setLayout(new FlowLayout(FlowLayout.CENTER));
		textPanel.add(new JLabel("Este é um JavaApplet"));
		textPanel.add(new JLabel("Número aleatório para saber que o applet não foi reiniciado:"));
		textPanel.add(new JLabel("" + new Random().nextInt()));
		this.getContentPane().add(textPanel);
	}
	
	public void actionPerformed(ActionEvent e) {
		
		JavaDummyApplet.this.timeLabel.setText("Comando de voz iniciado !!!!!");
		bc.main(null);

	}

	private void startWebcam(){
		final TimerTask timerTask = new TimerTask(){
			public void run() {
				final String moduleURL = JavaDummyApplet.this.getConfigurationManager().getProperty(ConfigurationManager.GWT_MODULE_BASE_URL);
				final String path = moduleURL + JavaDummyApplet.this.getConfigurationManager().getProperty(JavaDummyApplet.WEBCAM_IMAGE_URL_PROPERTY_NAME, JavaDummyApplet.DEFAULT_WEBCAM_IMAGE_URL);
				final ImageIcon image = JavaDummyApplet.this.loadImage(path);
				
				JavaDummyApplet.this.webcamPanel.removeAll();
				JavaDummyApplet.this.webcamPanel.add(new JLabel(image));
				JavaDummyApplet.this.webcamPanel.repaint();
				//JavaDummyApplet.this.messages.setText("<imagem atualizada>");
			}
		};
		this.webcamTimer = new Timer();
		this.webcamTimer.schedule(timerTask, 0, 3000);
	}
	
	private ImageIcon loadImage(final String path) {
	    final int MAX_IMAGE_SIZE = 1024 * 1024;
	    
	    final URL url;
	    try {
			url = new URL(path);
		} catch (MalformedURLException e) {
            System.err.println("Malformed URL Exception: " + e.getMessage());
            e.printStackTrace();
			return null;
		}
		
	    final BufferedInputStream imgStream;
		try {
			imgStream = new BufferedInputStream(url.openStream());
		} catch (IOException e) {
            System.err.println("Couldn't open stream: " + e.getMessage());
            e.printStackTrace();
			return null;
		}
	    
        final byte buf[] = new byte[MAX_IMAGE_SIZE];
        try {
            imgStream.read(buf);
            imgStream.close();
        } catch (java.io.IOException ioe) {
            System.err.println("Couldn't read stream from file: " + ioe.getMessage());
            ioe.printStackTrace();
            return null;
        }
        return new ImageIcon(Toolkit.getDefaultToolkit().createImage(buf));
	}
		
	public void startInteraction() {
		this.getContentPane().add(this.experimentPanel);
		this.startWebcam();
		this.messages.setText("Interação iniciada !");
		this.repaint();

	}
	
	public void setTime(int time) {
		this.timeLabel.setText("" + time);
		
		final TimerTask timerTask = new TimerTask(){
			public void run() {
				final int current = Integer.parseInt(JavaDummyApplet.this.timeLabel.getText());
				if(current == 0)
					JavaDummyApplet.this.getBoardController().onClean();
				JavaDummyApplet.this.timeLabel.setText("" + (current - 1));
			}
		};
		this.expirationTimer = new Timer();
		this.expirationTimer.schedule(timerTask, 0, 1000);
	}
	
	public void end() {
		if(this.webcamTimer != null)
			this.webcamTimer.cancel();
		if(this.expirationTimer != null)
			this.expirationTimer.cancel();
	}

}
