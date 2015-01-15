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

package es.deusto.weblab.client.experiments.ledrgb.ui;

import com.google.gwt.json.client.JSONObject;
import com.google.gwt.json.client.JSONParser;
import com.google.gwt.json.client.JSONValue;
import com.google.gwt.user.client.ui.VerticalPanel;

import es.deusto.weblab.client.configuration.IConfigurationRetriever;
import es.deusto.weblab.client.lab.experiments.IBoardBaseController;
import es.deusto.weblab.client.lab.experiments.UIExperimentBase;
import es.deusto.weblab.client.ui.widgets.WlTimer;
import es.deusto.weblab.client.ui.widgets.WlWebcam;

public class LEDRGBExperiment extends UIExperimentBase{

	public LEDRGBExperiment(IConfigurationRetriever configurationRetriever,
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
    	
		final MainPanel mainPanel = new MainPanel();
    	
		// 
		// Configure the camera
		final WlWebcam camera = mainPanel.getWebcam();
		camera.setUrl("http://weblabduino.pucsp.br/webcam/ledrgb/image.jpg");
		camera.setStreamingUrl("http://weblabduino.pucsp.br/webcam/ledrgb/video.mjpeg",320,240);
		camera.configureWebcam(obj);
		camera.start();
		addDisposableWidgets(camera);
		
		//Grafico gerado no Xively para o sensor de luz
		final WlWebcam graficoPNGVermelho = mainPanel.getGraficoVermelho();
		graficoPNGVermelho.setUrl("https://api.cosm.com/v2/feeds/107050970/datastreams/sensor_de_luz.png");
		graficoPNGVermelho.configureWebcam(obj);
		graficoPNGVermelho.start();
		addDisposableWidgets(graficoPNGVermelho);

		//Grafico gerado no Xively para o sensor de luz
		final WlWebcam graficoPNGVerde = mainPanel.getGraficoVerde();
		graficoPNGVerde.setUrl("https://api.cosm.com/v2/feeds/107050970/datastreams/sensor_de_luz.png");
		graficoPNGVerde.configureWebcam(obj);
		graficoPNGVerde.start();
		addDisposableWidgets(graficoPNGVerde);
		

		//Grafico gerado no Xively para o sensor de luz
		final WlWebcam graficoPNGAzul= mainPanel.getGraficoAzul();
		graficoPNGAzul.setUrl("https://api.cosm.com/v2/feeds/107050970/datastreams/sensor_de_luz.png");
		graficoPNGAzul.configureWebcam(obj);
		graficoPNGAzul.start();
		addDisposableWidgets(graficoPNGAzul);
		
		//
		// Configure the timer
		final WlTimer timer = mainPanel.getTimer();
		timer.updateTime(time);
		addDisposableWidgets(timer);
		
		
		this.putWidget(mainPanel);
	}

	
}

/* Useful commands
 * 
 *  boardController.sendCommand
 *  
 *  putWidget
 *  addDisposableWidgets
 * */
 