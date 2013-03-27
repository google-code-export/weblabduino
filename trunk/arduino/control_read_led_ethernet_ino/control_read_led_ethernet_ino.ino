//ARDUINO 1.0+ ONLY
//ARDUINO 1.0+ ONLY


#include <Ethernet.h>
#include <SPI.h>
boolean reading = false;

////////////////////////////////////////////////////////////////////////
//CONFIGURE
////////////////////////////////////////////////////////////////////////
  byte ip[] = { 192, 168, 1, 177 };   //Manual setup only
  //byte gateway[] = { 192, 168, 0, 1 }; //Manual setup only
  //byte subnet[] = { 255, 255, 255, 0 }; //Manual setup only

  // if need to change the MAC address (Very Rare)
  byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

  EthernetServer server = EthernetServer(80); //port 80
////////////////////////////////////////////////////////////////////////

void setup(){
  Serial.begin(9600);

  //Pins 10,11,12 & 13 are used by the ethernet shield

  pinMode(2, OUTPUT);

  Ethernet.begin(mac, ip);
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


    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    boolean sentHeader = false;

    while (client.connected()) {
      if (client.available()) {

        if(!sentHeader){
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println();
          sentHeader = true;
          reading = true ;
        }
        
        
        char c = client.read();
        Serial.println(c);
        
        if(c != "2" | "3"){
        client.close();
        }
        
        
        clientMsg+=c;//store the recieved chracters in a string


        if(reading){
          Serial.println(clientMsg);

           switch (c) {
            case '2':
              //add code here to trigger on 2
              triggerPin(2, client);
              client.println("fim");
              client.stop(); // close the connection:
              break;
              
            case '3':
            //add code here to trigger on 3
              readPin(3, client);
              client.println("fim");
              client.stop(); // close the connection:
              break;
              
          }


        }


      }
    }

    delay(1); // give the web browser time to receive the data
    client.stop(); // close the connection:

  } 

}

void triggerPin(int pin, EthernetClient client){
//blink a pin - Client needed just for HTML output purposes.  
  client.print("Turning on pin ");
  client.println(pin);

  digitalWrite(pin, HIGH);
  delay(250);
  digitalWrite(pin, LOW);
  delay(250);

}

void readPin(int pin, EthernetClient client){
//blink a pin - Client needed just for HTML output purposes.  
    client.print("analog input ");
    client.print(pin);
    client.print(" is ");
    client.println(analogRead(pin));

}
