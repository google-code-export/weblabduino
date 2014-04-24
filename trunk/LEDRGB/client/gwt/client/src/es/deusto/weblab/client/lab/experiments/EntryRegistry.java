/*
* Copyright (C) 2005 onwards University of Deusto
* All rights reserved.
*
* This software is licensed as described in the file COPYING, which
* you should have received as part of this distribution.
*
* This software consists of contributions made by many individuals, 
* listed below:
*
* Author: Pablo Orduña <pablo@ordunya.com>
*
*/

package es.deusto.weblab.client.lab.experiments;

import java.util.List;
import java.util.Vector;

import es.deusto.weblab.client.experiments.ledrgb.LEDRGBCreatorFactory;
import es.deusto.weblab.client.lab.experiments.util.applets.flash.FlashAppCreatorFactory;
import es.deusto.weblab.client.lab.experiments.util.applets.java.JavaAppletCreatorFactory;
import es.deusto.weblab.client.lab.experiments.util.applets.js.JSAppCreatorFactory;

/**
 * This class acts as a registry of all the available entries for the currently known experiments.
 * In order to add a new experiment, just add another element to the list as the sample one (the one commented)
 */
class EntryRegistry {
	
	static final IExperimentCreatorFactory [] creatorFactories = new IExperimentCreatorFactory[]{

		new FlashAppCreatorFactory(),
		new JavaAppletCreatorFactory(),
		new JSAppCreatorFactory(),
		new LEDRGBCreatorFactory(),

	};
	
	static final List<ExperimentEntry> entries = new Vector<ExperimentEntry>();
}
