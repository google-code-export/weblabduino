package es.deusto.weblab.client.experiment.plugins.java;

import javax.swing.JApplet;

import netscape.javascript.JSObject;

public abstract class WebLabApplet extends JApplet {
	private static final long serialVersionUID = -7383940394030524725L;
	
	private JSObject jsobject;

	
	public WebLabApplet(){
	}
	
	public void init(){
		
		
		this.jsobject = JSObject.getWindow(this);

		
	}
	

	// Methods that can be overridden
	
	public void setTime(int time) {}
	
	public void startInteraction() {}
	
	public void end() {}
	
}
