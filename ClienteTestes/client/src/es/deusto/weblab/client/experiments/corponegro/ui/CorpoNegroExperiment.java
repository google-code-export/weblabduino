/*
* Copyright (C) 2012 onwards University of Deusto
* All rights reserved.
*
* This software is licensed as described in the file COPYING, which
* you should have received as part of this distribution.
*
* This software consists of contributions made by many individuals, 
* listed below:
*
* Author: FILLME
*
*/

package es.deusto.weblab.client.experiments.corponegro.ui;

import com.google.gwt.core.client.GWT;
import com.google.gwt.json.client.JSONObject;
import com.google.gwt.json.client.JSONParser;
import com.google.gwt.json.client.JSONValue;
import com.google.gwt.user.client.ui.VerticalPanel;

import es.deusto.weblab.client.configuration.IConfigurationRetriever;
import es.deusto.weblab.client.lab.experiments.IBoardBaseController;
import es.deusto.weblab.client.lab.experiments.UIExperimentBase;
import es.deusto.weblab.client.ui.widgets.WlTimer;
import es.deusto.weblab.client.ui.widgets.WlWebcam;

public class CorpoNegroExperiment extends UIExperimentBase{
	
	
	private static final String WEBCAM_REFRESH_TIME_PROPERTY   = "webcam.refresh.millis";
	private static final int    DEFAULT_WEBCAM_REFRESH_TIME    = 200;
	
	final MainPanel mainPanel = new MainPanel();
	WlWebcam camera = mainPanel.getWebcam();
	WlTimer timer = mainPanel.getTimer();


	public CorpoNegroExperiment(IConfigurationRetriever configurationRetriever,
			IBoardBaseController boardController) {
		super(configurationRetriever, boardController);
		// TODO Auto-generated constructor stub
	}

	
	@Override
	public void initialize(){
		putWidget(new VerticalPanel());
	}
	
	@Override
	public JSONValue getInitialData() {
		return null;

	}
	
	@Override
	public void queued(){
		putWidget(new VerticalPanel());
	}
	
    @Override
    public void start(int time, String initialConfiguration) {

    	final JSONValue value = JSONParser.parseStrict(initialConfiguration);
    	final JSONObject obj = (JSONObject)value;
    	

		addDisposableWidgets(timer);
		
	    this.camera.setUrl("http://192.168.42.102/image.jpg");
	    this.camera.setStreamingUrl("http://localhost/video.mjpeg", 320, 240);
		this.camera.setVisible(true);
	    this.camera.start();
    	
		putWidget(mainPanel);
    }

    
    private void createProvidedWidgets() {
		this.timer = new WlTimer(false);	
    	
		this.camera = GWT.create(WlWebcam.class);
		this.camera.setTime(this.getWebcamRefreshingTime());
	}
    
    private int getWebcamRefreshingTime() {
		return this.configurationRetriever.getIntProperty(
			CorpoNegroExperiment.WEBCAM_REFRESH_TIME_PROPERTY, 
			CorpoNegroExperiment.DEFAULT_WEBCAM_REFRESH_TIME
		);
	}	

	
}

/* Useful commands
 * 
 *  boardController.sendCommand
 *  
 *  putWidget
 *  addDisposableWidgets
 * */
 