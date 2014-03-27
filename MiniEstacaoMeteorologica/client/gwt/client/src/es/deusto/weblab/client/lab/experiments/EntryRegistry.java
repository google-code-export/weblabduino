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

import es.deusto.weblab.client.experiments.aquarium.AquariumCreatorFactory;
import es.deusto.weblab.client.experiments.binary.BinaryCreatorFactory;
import es.deusto.weblab.client.experiments.controlapp.ControlAppCreatorFactory;
import es.deusto.weblab.client.experiments.corponegro.CorpoNegroCreatorFactory;
import es.deusto.weblab.client.experiments.redirect.RedirectCreatorFactory;
import es.deusto.weblab.client.experiments.robot_movement.RobotMovementCreatorFactory;
import es.deusto.weblab.client.experiments.robot_proglist.RobotProglistCreatorFactory;
import es.deusto.weblab.client.experiments.robot_standard.RobotStandardCreatorFactory;
import es.deusto.weblab.client.experiments.robotarm.RobotArmCreatorFactory;
import es.deusto.weblab.client.experiments.submarine.SubmarineCreatorFactory;
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
		new BinaryCreatorFactory(),
		new RobotStandardCreatorFactory(),
		new RobotMovementCreatorFactory(),
		new RobotProglistCreatorFactory(),
		new RobotArmCreatorFactory(),
		new SubmarineCreatorFactory(),
		new ControlAppCreatorFactory(),
		new AquariumCreatorFactory(),
		new RedirectCreatorFactory(),
		new CorpoNegroCreatorFactory(),
	};
	
	static final List<ExperimentEntry> entries = new Vector<ExperimentEntry>();
}
