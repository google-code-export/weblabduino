#include <SPI.h>
#include <Ethernet.h>

//Atribua um endereco MAC para o shield Ethernet
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a };
char leitura;
unsigned long tempo = millis();

//Pino de controle da lampada
int lampada = 9;
int statusLampada;

// Acesso ao shield ethernet pela porta 80
EthernetServer server(80);

void setup() {
 
  // Inicia-se a comunicaço serial e aguarda uma resposta
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonrdo only
  }

  // Inicia-se o shield ethernet com o MAC configurado anteriormente
  Ethernet.begin(mac);
  server.begin();
  
  Serial.print("IP: ");
  Serial.println(Ethernet.localIP());
  
  pinMode(lampada,OUTPUT);
  digitalWrite(lampada,LOW);
    
}


void loop() {
   // listen for incoming clients, and process request.
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
          
          if(clientMsg = "1"){
            statusLampada = digitalRead(lampada);
            
            if(statusLampada){
              digitalWrite(lampada,HIGH);
            }else{
              digitalWrite(lampada,LOW);
            }
            
            
          }else{
              client.stop(); // close the connection:

          }
          

      }
    }

    delay(1); // give the web browser time to receive the data
    client.stop(); // close the connection:

  } 

}


void temperaturaMediaCalotas(){
  int i;
  int branco = A0;
  int pretaval = A1;

  //Coleta 5 amostas
    for (i = 0; i < 5; i++){
      brancoval = brancoval + analogRead(A0);
      pretaval = pretaval + analogRead(A1); 
    }
    
    
   //Media das 5 amostras
   brancoval = brancoval/5;   
   pretaval = pretaval/5;     
   
   float temperaturaBranca=(5*brancoval*100)/1023;
   float temperaturaPreta=(5*pretaval*100)/1023;
   
   Serial.print(temperaturaPreta);
   Serial.print("   ");
   Serial.print(temperaturaBranca);
   Serial.print("   ");
   Serial.println(tempo);
   delay(100);
     
}
