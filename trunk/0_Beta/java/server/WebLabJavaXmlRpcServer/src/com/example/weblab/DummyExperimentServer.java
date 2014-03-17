package com.example.weblab;

import java.io.File;


import es.deusto.weblab.experimentservers.ExperimentServer;
import es.deusto.weblab.experimentservers.exceptions.ExperimentServerInstantiationException;
import es.deusto.weblab.experimentservers.exceptions.WebLabException;

public class DummyExperimentServer extends ExperimentServer {

	public DummyExperimentServer()
			throws ExperimentServerInstantiationException {
		super();
	}

	public void startExperiment() throws WebLabException {
		System.out.println("I'm at startExperiment");
	}

	public String sendFile(File file, String fileInfo)  throws WebLabException {
		System.out.println("I'm at send_program: " + file.getAbsolutePath() + "; fileInfo: " + fileInfo);
		return "ok";
	}
	
	public String sendCommand(String command)  throws WebLabException {
		System.out.println("I'm at send_command: " + command);
		

		ArduinoEthernetComm aec = new ArduinoEthernetComm();
		
		try {
			System.out.println("Dados Arduino => " + aec.ArduinoEthernetComm("192.168.1.177", 80, "2"));
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		return "ok";
	}
	
	public void dispose() {
		System.out.println("I'm at dispose");
	}
	
	/* Optional methods (Override, Java 1.4 compatible...) */
	
	public boolean isUpAndRunning() {
		return false;
	}
}
