// NAME
//      $RCSfile: BeanCan.java,v $
// DESCRIPTION
//      [given below in javadoc format]
// DELTA
//      $Revision$
// CREATED
//      $Date$
// COPYRIGHT
//      Mexuar Technologies Ltd
// TO DO
//
package org.asteriskjava.iax.ui;

import java.awt.*;

import org.asteriskjava.iax.protocol.Log;
import org.asteriskjava.iax.audio.javasound.AudioProperties;

/**
 * Swing phone implementation
 * @author <a href="mailto:thp@westhawk.co.uk">Tim Panton</a>
 * @version $Revision$ $Date$
 */
public class BeanCan {

	private static final String argU = "1003"; 
	private static final String argP = "12345"; 
	private static final String argH = "192.168.30.177"; 
	
	private static final String     version_id =
        "@(#)$Id$ Copyright Mexuar Technologies Ltd";

  boolean packFrame = false;

  //Construct the application
  public BeanCan(String uname,String pass, String host, int level) {
    BeanCanFrameManager frame = new BeanCanFrameManager(uname,pass,host,false,level);
    //Validate frames that have preset sizes
    //Pack frames that have useful preferred size info, e.g. from their layout
    if (packFrame) {
      frame.pack();
    }
    else {
      frame.validate();
    }
    //Center the window
    Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
    Dimension frameSize = frame.getSize();
    if (frameSize.height > screenSize.height) {
      frameSize.height = screenSize.height;
    }
    if (frameSize.width > screenSize.width) {
      frameSize.width = screenSize.width;
    }
    frame.setLocation((screenSize.width - frameSize.width) / 2, (screenSize.height - frameSize.height) / 2);
    frame.setVisible(true);
    frame.register();
  }

  //Main method
  public static void main(String[] argv) {

      AudioProperties.loadFromFile("audio.properties");
      
      //Registrar no asterisk utilizando os parametros abaixo
      //user, pass, host, LOG.LEVEL
      BeanCan bc = new BeanCan(argU, argP, argH, Log.NONE);
  }
}
