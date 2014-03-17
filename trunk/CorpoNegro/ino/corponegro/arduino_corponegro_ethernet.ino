/*
  Web Server
 
 A simple web server that shows the value of the analog input pins.
 using an Arduino Wiznet Ethernet shield. 
 
 Circuit:
 * Ethernet shield attached to pins 10, 11, 12, 13
 * Analog inputs attached to pins A0 through A5 (optional)
 
 created 18 Dec 2009
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe
 
 */

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x3a };


// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() {
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
    
}


void loop() {
   // listen for incoming clients, and process qequest.
  checkForClient();
  
}

void checkForClient(){

  EthernetClient client = server.available();

  if (client) {
        Serial.println("Cliente Conectado");
        String clientMsg ="";

    while (client.connected()) {
      if (client.available()) {
        
        char c = client.read();
              
        clientMsg+=c;//store the recieved chracters in a string

          Serial.println(clientMsg);

           switch (c) {
            case '1':
              //add code here to trigger on 2
              blinkPin(5, client);
              client.println("fim");
              client.stop(); // close the connection:
              break;
          
            default:
              client.stop(); // close the connection:
              break;            
          }

      }
    }

    delay(1); // give the web browser time to receive the data
    client.stop(); // close the connection:

  } 

}

void blinkPin(int pin, EthernetClient client){
  
  client.print("Blinking on pin ");
  client.println(pin);

  pinMode(pin,OUTPUT);
  digitalWrite(pin, HIGH);
  delay(1000);
  digitalWrite(pin, LOW);
  delay(1000);

}

void onPin(int pin, EthernetClient client){
  
  client.print("Turning on pin ");
  client.println(pin);

  digitalWrite(pin, HIGH);
  delay(10);

}

void offPin(int pin, EthernetClient client){
  
  client.print("Turning off pin ");
  client.println(pin);

  digitalWrite(pin, LOW);
  delay(10);

}

void readPin(int pin, EthernetClient client){
    
    client.print("analog input ");
    client.print(pin);
    client.print(" is ");
    client.println(analogRead(pin));

}

