package org.asteriskjava.iax.ui;

import org.asteriskjava.iax.audio.javasound.AudioProperties;
import org.asteriskjava.iax.protocol.Call;
import org.asteriskjava.iax.protocol.Friend;
import org.asteriskjava.iax.protocol.Log;
import org.asteriskjava.iax.protocol.ProtocolControlFrame;

public class main {

	/**
	 * @param args
	 */
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		 
	    AudioProperties.loadFromFile("audio.properties");
		
		BeanCanFrameManager bcfm = new BeanCanFrameManager(false,Log.DEBUG,"");
	
		if(bcfm != null){
			
			bcfm.set_host("192.168.30.177");
			bcfm.set_username("1003");
			bcfm.set_password("12345");
			bcfm.register();
			bcfm.act.doClick();
		}

	}

}
