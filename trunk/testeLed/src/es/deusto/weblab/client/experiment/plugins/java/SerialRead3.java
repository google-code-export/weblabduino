package es.deusto.weblab.client.experiment.plugins.java;

import jssc.SerialPort;
import jssc.SerialPortException;

public class SerialRead3 {

    public void SerialRead3() {
        SerialPort serialPort = new SerialPort("COM3");
        try {
            serialPort.openPort();//Open serial port
            serialPort.setParams(9600, 8, 1, 0);//Set params.
            
            boolean b = true;
            
            while (b=true){
            	
            	byte[] buffer = serialPort.readBytes(100);//Read 10 bytes from serial port
            	String source2 = new String(buffer);
                System.out.println(source2);
                
            	
            }
            serialPort.closePort();//Close serial port
        }
        catch (SerialPortException ex) {
            System.out.println(ex);
        }
    }
    
    public static void main(String[]args){
    	SerialRead3 sr3 = new SerialRead3();
    	sr3.SerialRead3();
    }
}