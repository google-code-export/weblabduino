//ARDUINO 1.0+ ONLY
//ARDUINO 1.0+ ONLY


#include <Ethernet.h>
#include <SPI.h>
boolean reading = false;

////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
  byte ip[] = { 192, 168, 1, 54 };   //Manual setup only
  //byte gateway[] = { 192, 168, 0, 1 }; //Manual setup only
  //byte subnet[] = { 255, 255, 255, 0 }; //Manual setup only

  // if need to change the MAC address (Very Rare)
  byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x2a };

  EthernetServer server = EthernetServer(80); //port 80
////////////////////////////////////////////////////////////////////////

void setup(){
  Serial.begin(9600);

  //Pins 10,11,12 & 13 are used by the ethernet shield

  pinMode(2, OUTPUT);

  Ethernet.begin(mac,ip);
  //Ethernet.begin(mac, ip, gateway, subnet); //for manual setup

  server.begin();
  Serial.println(Ethernet.localIP());

}

void loop(){

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
            case '2':
              //add code here to trigger on 2
              blinkPin(13, client);
              client.stop(); // close the connection:
              break;
              
            case '3':
            //add code here to trigger on 3
              readPin(0, client);
              readPin(1, client);
              readPin(2, client);
              readPin(3, client);
              readPin(4, client);
              readPin(5, client);
              client.stop(); // close the connection:
              break;
            
            default:
              client.stop(); // close the connection:
          }


        

      }
    }

    delay(1); // give the web browser time to receive the data
    client.stop(); // close the connection:

  } 

}

void blinkPin(int pin, EthernetClient client){
//blink a pin - Client needed just for HTML output purposes.  
  
  client.print("Blinking on pin ");
  client.println(pin);

  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
  delay(250);

}

void onPin(int pin, EthernetClient client){
//on a pin - Client needed just for HTML output purposes.  
  client.print("Turning on pin ");
  client.println(pin);

  digitalWrite(pin, HIGH);
  delay(10);

}

void offPin(int pin, EthernetClient client){
//off a pin - Client needed just for HTML output purposes.  
  client.print("Turning off pin ");
  client.println(pin);

  digitalWrite(pin, LOW);
  delay(10);

}

void readPin(int pin, EthernetClient client){
//read a pin - Client needed just for HTML output purposes.  
    //client.print("analog input ");
    //client.print(pin);
    //client.print(" is ");
    client.print(analogRead(pin));
    client.print(";");
    delay(1000);
}
