// NAME
//      $RCSfile: BeanCanFrame.java,v $
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
import java.awt.event.*;
import javax.swing.*;
import java.security.AccessControlException;

/**
 * Swing phone UI
 * @author <a href="mailto:thp@westhawk.co.uk">Tim Panton</a>
 * @version $Revision$ $Date$
 *
 */
public class BeanCanFrame extends JFrame {
    private static final String version_id =
            "@(#)$Id$ Copyright Mexuar Technologies Ltd";

  JPanel contentPane;
  JPanel jPanel1 = new JPanel();
  JPanel jPanel2 = new JPanel();
  JPanel jPanel4 = new JPanel();

  
  JMenuBar jMenuBar = new JMenuBar();
  JMenu jMenuFile = new JMenu();
  JMenuItem jMenuFileExit = new JMenuItem();
  JMenu jMenuHelp = new JMenu();
  JMenuItem jMenuHelpAbout = new JMenuItem();
  
  BorderLayout borderLayout1 = new BorderLayout();
  BorderLayout borderLayout2 = new BorderLayout();
  BorderLayout borderLayout3 = new BorderLayout();

  JTextField dialString = new JTextField();
  
  GridLayout gridLayout1 = new GridLayout();
  GridLayout gridLayout2 = new GridLayout();

  JLabel status = new JLabel();
  JButton act = new JButton();
  JButton clear = new JButton();
 
  private JDialog _about;

  //Construct the frame
  public BeanCanFrame() {
    enableEvents(AWTEvent.WINDOW_EVENT_MASK);
    try {
      jbInit();
    }
    catch(Exception e) {
      e.printStackTrace();
    }
  }

  //Component initialization
  private void jbInit() throws Exception  {
	  
    contentPane = (JPanel) this.getContentPane();
    contentPane.setLayout(borderLayout1);
    
    this.setSize(new Dimension(319, 311));
    
    this.setTitle("Cliente Remoto de Voz");
    
    jMenuFile.setText("Arquivo");
    jMenuFileExit.setText("Sair");
    jMenuFileExit.addActionListener(new BeanCanFrame_jMenuFileExit_ActionAdapter(this));
    
    jMenuHelp.setText("Ajuda");
    jMenuHelpAbout.setText("Sobre");
    jMenuHelpAbout.addActionListener(new BeanCanFrame_jMenuHelpAbout_ActionAdapter(this));
    
    jMenuFile.add(jMenuFileExit);
    jMenuHelp.add(jMenuHelpAbout);
    jMenuBar.add(jMenuFile);
    jMenuBar.add(jMenuHelp);
    this.setJMenuBar(jMenuBar);
    
    jPanel1.setLayout(borderLayout2);
    dialString.setText("1003");
    dialString.addActionListener(new BeanCanFrame_dialString_actionAdapter(this));
    
    jPanel2.setLayout(borderLayout3);
    status.setText("não conectado");
    
    act.setText("Chamar");
    act.addActionListener(new BeanCanFrame_act_actionAdapter(this));
    contentPane.setActionMap(null);
    
    clear.setText("Limpar");
    clear.addActionListener(new BeanCanFrame_clear_actionAdapter(this));
    
    contentPane.add(jPanel1, BorderLayout.CENTER);
    jPanel1.add(jPanel2, BorderLayout.NORTH); 
    jPanel2.add(dialString, BorderLayout.CENTER); //caixa de texto para chamar

    contentPane.add(jPanel4, BorderLayout.SOUTH);
    jPanel4.add(status, BorderLayout.CENTER); //status do programa

    jPanel2.add(act, BorderLayout.EAST);
    jPanel2.add(clear,  BorderLayout.WEST);
    
  }

  //File | Exit action performed
  public void jMenuFileExit_actionPerformed(ActionEvent e) {
    try {
      System.exit(0);
    } catch (AccessControlException ace){
      // cope with applets....
      this.hide();
    }
  }

  //Help | About action performed
  public void jMenuHelpAbout_actionPerformed(ActionEvent e) {
    if (_about == null){
      _about = new AboutDialog(this, this.version_id, false);
    }
    _about.show();
  }

  //Overridden so we can exit when window is closed
  protected void processWindowEvent(WindowEvent e) {
    super.processWindowEvent(e);
    if (e.getID() == WindowEvent.WINDOW_CLOSING) {
      jMenuFileExit_actionPerformed(null);
    }
  }


  void button_action(ActionEvent e) {
    String t = e.getActionCommand();
    String s = this.dialString.getText();
    s = s+t;
    dialString.setText(s);
  }

  void dialString_actionPerformed(ActionEvent e) {
     String num = dialString.getText();
     status.setText("Dialing: "+num);
  }

  void clear_actionPerformed(ActionEvent e) {
    dialString.setText("");
  }

  void act_actionPerformed(ActionEvent e) {
    dialString_actionPerformed(e);
  }

}

class BeanCanFrame_jMenuFileExit_ActionAdapter implements ActionListener {
  BeanCanFrame adaptee;

  BeanCanFrame_jMenuFileExit_ActionAdapter(BeanCanFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jMenuFileExit_actionPerformed(e);
  }
}

class BeanCanFrame_jMenuHelpAbout_ActionAdapter implements ActionListener {
  BeanCanFrame adaptee;

  BeanCanFrame_jMenuHelpAbout_ActionAdapter(BeanCanFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.jMenuHelpAbout_actionPerformed(e);
  }
}

class BeanCanFrame_dialString_actionAdapter implements java.awt.event.ActionListener {
  BeanCanFrame adaptee;

  BeanCanFrame_dialString_actionAdapter(BeanCanFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.dialString_actionPerformed(e);
  }
}

class BeanCanFrame_clear_actionAdapter implements java.awt.event.ActionListener {
  BeanCanFrame adaptee;

  BeanCanFrame_clear_actionAdapter(BeanCanFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.clear_actionPerformed(e);
  }
}

class BeanCanFrame_act_actionAdapter implements java.awt.event.ActionListener {
  BeanCanFrame adaptee;

  BeanCanFrame_act_actionAdapter(BeanCanFrame adaptee) {
    this.adaptee = adaptee;
  }
  public void actionPerformed(ActionEvent e) {
    adaptee.act_actionPerformed(e);
  }
}


