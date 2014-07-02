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
import com.google.gwt.uibinder.client.UiBinder;
import com.google.gwt.user.client.ui.Composite;
import com.google.gwt.user.client.ui.HorizontalPanel;
import com.google.gwt.user.client.ui.Image;
import com.google.gwt.user.client.ui.RootPanel;
import com.google.gwt.user.client.ui.Widget;
import com.google.gwt.uibinder.client.UiField;

import es.deusto.weblab.client.ui.widgets.WlWebcam;
import es.deusto.weblab.client.ui.widgets.WlTimer;

import com.google.gwt.user.client.ui.VerticalPanel;

import es.deusto.weblab.client.ui.widgets.WlWebcamSafariBased;

import com.google.gwt.uibinder.client.UiHandler;
import com.google.gwt.event.logical.shared.AttachEvent;
import com.google.gwt.user.cellview.client.CellTable;
import com.google.gwt.user.client.ui.TabPanel;

import es.deusto.weblab.client.ui.widgets.WlButton;
import es.deusto.weblab.client.ui.widgets.WlSwitch.SwitchEvent;
import es.deusto.weblab.client.ui.widgets.WlSwitch;
import es.deusto.weblab.client.ui.widgets.WlStreamImage;
import com.google.gwt.user.client.ui.DecoratedStackPanel;

public class MainPanel extends Composite {

	private static MainPanelUiBinder uiBinder = GWT
			.create(MainPanelUiBinder.class);

	@UiField WlTimer timer;
	@UiField VerticalPanel widget;
	@UiField(provided = true) WlWebcam camera;
	@UiField WlSwitch ControlarLampada;
	@UiField WlStreamImage GraficoTemperatura;



	interface MainPanelUiBinder extends UiBinder<Widget, MainPanel> {
	}

	public MainPanel() {
		this.ControlarLampada = GWT.create(WlSwitch.class);
		this.camera = GWT.create(WlWebcam.class);
		this.GraficoTemperatura = GWT.create(WlStreamImage.class);
		initWidget(uiBinder.createAndBindUi(this));

	}

	public WlWebcam getWebcam() {
		return this.camera;
	}
	
	public WlStreamImage getGraficoTemperatura() {
		return this.GraficoTemperatura;
	}
	
	public WlSwitch getControlarLampada(){
		return this.ControlarLampada;
	}
	
	public WlTimer getTimer(){
		return this.timer;
	}
	

}
