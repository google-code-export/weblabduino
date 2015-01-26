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

package es.deusto.weblab.client;

import com.google.gwt.user.client.ui.RootPanel;
import es.deusto.weblab.client.experiments.corponegro.CorpoNegroCreatorFactory;
import es.deusto.weblab.client.experiments.corponegro.ui.MainPanel;

public class Weblabteste extends WebLabClient{

	MainPanel mp = new MainPanel();
	CorpoNegroCreatorFactory ccc = new CorpoNegroCreatorFactory();
	
	@Override
	public void onModuleLoad() {
		this.loadApplication();
		// TODO Auto-generated method stub


	}

	@Override
	public void loadApplication() {
		// TODO Auto-generated method stub
		ccc.createExperimentCreator(Weblabteste.this.configurationManager);
		RootPanel.get().add(mp);
		
	}


}
