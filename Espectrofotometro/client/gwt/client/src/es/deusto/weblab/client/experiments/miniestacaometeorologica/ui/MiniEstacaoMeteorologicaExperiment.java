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

package es.deusto.weblab.client.experiments.miniestacaometeorologica.ui;

import com.google.gwt.json.client.JSONObject;
import com.google.gwt.json.client.JSONParser;
import com.google.gwt.json.client.JSONValue;
import com.google.gwt.user.client.ui.VerticalPanel;

import es.deusto.weblab.client.configuration.IConfigurationRetriever;
import es.deusto.weblab.client.lab.experiments.IBoardBaseController;
import es.deusto.weblab.client.lab.experiments.UIExperimentBase;
import es.deusto.weblab.client.ui.widgets.WlTimer;
import es.deusto.weblab.client.ui.widgets.WlWebcam;

public class MiniEstacaoMeteorologicaExperiment extends UIExperimentBase{

	public MiniEstacaoMeteorologicaExperiment(IConfigurationRetriever configurationRetriever,
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
		camera.setUrl("http://weblabduino.pucsp.br/webcam/mem/image.jpg");
		camera.setStreamingUrl("http://weblabduino.pucsp.br/webcam/mem/video.mjpeg",320,240);
		camera.configureWebcam(obj);
		camera.start();
		addDisposableWidgets(camera);
		
		//Grafico gerado no Xively para o sensor de monoxido de carbono 
		final WlWebcam graficoPNGCO2 = mainPanel.getGraficoCO2();
		graficoPNGCO2.setUrl("https://api.cosm.com/v2/feeds/107050970/datastreams/sensor_monoxido_de_carbono.png?t=CO%C2%B2&l=0-1023&s=5&b=true&g=true&w=550&h=250&duration=120minutes&timezone=Brasilia");
		graficoPNGCO2.configureWebcam(obj);
		graficoPNGCO2.start();
		addDisposableWidgets(graficoPNGCO2);
		
		//Grafico gerado no Xively para o sensor de temperatura
		final WlWebcam graficoPNGTemperatura = mainPanel.getGraficoTemperatura();
		graficoPNGTemperatura.setUrl("https://api.cosm.com/v2/feeds/107050970/datastreams/sensor_temperatura.png?t=Temperatura&l=%C2%B0C&s=5&b=true&g=true&w=550&h=250&duration=120minutes&timezone=Brasilia");
		graficoPNGTemperatura.configureWebcam(obj);
		graficoPNGTemperatura.start();
		addDisposableWidgets(graficoPNGTemperatura);
		
		//Grafico gerado no Xively para o sensor de humidade
		final WlWebcam graficoPNGHumidade = mainPanel.getGraficoHumidade();
		graficoPNGHumidade.setUrl("https://api.cosm.com/v2/feeds/107050970/datastreams/sensor_humidade.png?t=Humidade&l=/100&s=5&b=true&g=true&w=550&h=250&duration=120minutes&timezone=Brasilia");
		graficoPNGHumidade.configureWebcam(obj);
		graficoPNGHumidade.start();
		addDisposableWidgets(graficoPNGHumidade);
		
		//Grafico gerado no Xively para o sensor de luz
		final WlWebcam graficoPNGLuz = mainPanel.getGraficoLuz();
		graficoPNGLuz.setUrl("https://api.cosm.com/v2/feeds/107050970/datastreams/sensor_de_luz.png?t=Luminosidade&l=lumens&s=5&b=true&g=true&w=550&h=250&duration=120minutes&timezone=Brasilia");
		graficoPNGLuz.configureWebcam(obj);
		graficoPNGLuz.start();
		addDisposableWidgets(graficoPNGLuz);
		
		//Grafico gerado no Xively para o sensor de som
		final WlWebcam graficoPNGSom = mainPanel.getGraficoSom();
		graficoPNGSom.setUrl("https://api.cosm.com/v2/feeds/107050970/datastreams/sensor_sonoro.png?t=Som&l=0-1023&s=5&b=true&g=true&w=550&h=250&duration=120minutes&timezone=Brasilia");
		graficoPNGSom.configureWebcam(obj);
		graficoPNGSom.start();
		addDisposableWidgets(graficoPNGSom);
		

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
 