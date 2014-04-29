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
* Author: Bruno Stabile - brn.stabile@gmail.com
*
*/

package es.deusto.weblab.client.experiments.ledrgb;


import com.google.gwt.core.client.GWT;
import com.google.gwt.core.client.RunAsyncCallback;

import es.deusto.weblab.client.configuration.IConfigurationRetriever;
import es.deusto.weblab.client.experiments.ledrgb.ui.LEDRGBExperiment;
import es.deusto.weblab.client.lab.experiments.ExperimentCreator;
import es.deusto.weblab.client.lab.experiments.ExperimentFactory.IExperimentLoadedCallback;
import es.deusto.weblab.client.lab.experiments.ExperimentFactory.MobileSupport;
import es.deusto.weblab.client.lab.experiments.IBoardBaseController;
import es.deusto.weblab.client.lab.experiments.IExperimentCreatorFactory;

public class LEDRGBCreatorFactory implements IExperimentCreatorFactory{

	@Override
	public String getCodeName() {

		return "mini-estacao-meteorologica";
	}

	@Override
	public ExperimentCreator createExperimentCreator(
			final IConfigurationRetriever configurationRetriever) {
		
		return new ExperimentCreator(MobileSupport.limited, getCodeName()){
			
			@Override
			public void createWeb(final IBoardBaseController boardController, final IExperimentLoadedCallback callback) {
				GWT.runAsync(new RunAsyncCallback() {
					
					@Override
					public void onSuccess() {
						callback.onExperimentLoaded(new LEDRGBExperiment(
								configurationRetriever,
								boardController
							));
					}
					
					@Override
					public void onFailure(Throwable e){
						callback.onFailure(e);
					}
				});
			}
		};
	}
	
}
