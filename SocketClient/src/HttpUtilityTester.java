
import java.io.*;
import java.net.*;

class Client
{
	//Ip Adress and Port, where the Arduino Server is running on
	private static final String serverIP="192.168.1.177";
	private static final int serverPort=80;

	 public static void main(String argv[]) throws Exception
	 {
		  String msgToServer;//Message that will be sent to Arduino
		  String msgFromServer;//recieved message will be stored here

		  Socket clientSocket = new Socket(serverIP, serverPort);//making the socket connection
		  System.out.println("Connected to:"+serverIP+" on port:"+serverPort);//debug
		  //OutputStream to Arduino-Server
		  DataOutputStream outToServer = new DataOutputStream(clientSocket.getOutputStream());
		  //BufferedReader from Arduino-Server
		  BufferedReader inFromServer = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));//

		  msgToServer = "2";//Message tha will be sent
		  outToServer.writeBytes(msgToServer+'\n');//sending the message
		  System.out.println("sending to Arduino-Server: "+msgToServer);//debug
		  msgFromServer = inFromServer.readLine();//recieving the answer
		  System.out.println("recieved from Arduino-Server: " + msgFromServer);//print the answer

		  clientSocket.close();//close the socket
		  //don't do this if you want to keep the connection
	 }
}