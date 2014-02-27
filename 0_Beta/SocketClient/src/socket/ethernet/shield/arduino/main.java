package socket.ethernet.shield.arduino;

public class main {

	/**
	 * @param args
	 * @throws Exception 
	 */
	public static void main(String[] args) throws Exception {

		ArduinoEthernetComm aec = new ArduinoEthernetComm();
		
		System.out.println("Dados Arduino => " + aec.ArduinoEthernetComm("192.168.1.177", 80, "2"));
		
		
	}

}
