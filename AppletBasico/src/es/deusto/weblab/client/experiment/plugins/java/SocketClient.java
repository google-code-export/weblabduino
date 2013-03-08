package es.deusto.weblab.client.experiment.plugins.java;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;


public class SocketClient {

	public static void main(String[] args) throws IOException{
		Socket client = new Socket("192.169.1.201", 80);      

		DataInputStream in=new DataInputStream(client.getInputStream());
		DataOutputStream out=new DataOutputStream(client.getOutputStream());

		out.writeBytes("LigaLed13");       //enviando uma string

		String s = in.readUTF(); //Aguarda o recebimento de uma string.

		out.writeBytes("Obrigado!");      //enviando uma string

		System.out.println(s);      //imprimindo a string recebida

		//Fecha os canais de entrada e saída.
		in.close();
		out.close();
		//Fecha o socket.
		client.close();


	}

}