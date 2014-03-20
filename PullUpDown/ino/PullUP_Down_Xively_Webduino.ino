/* Cosm Arduino sensor client example.
 *
`` * This sketch demonstrates connecting an Arduino to Cosm (https://cosm.com),
 * using the new Arduino library to send and receive data.

**/

#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Xively.h>
//**********************************************************


#define API_KEY "             " // Chave no Xively
#define FEED_ID  // ID no Xively

// MAC address for your Ethernet shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)


unsigned long lastConnectionTime = 0;                // ultimo instante de conexao no Xively
const unsigned long connectionInterval = 1000;      // delay para conexao no Xively milliseconds



// Define o mome que será exibido no grafico
char sensorId[] = "V_R_Pull_Down";  // para resistor em GND e LDR em +V
char sensorId2[] = "V_LDR_R_Pull_Up"; // para LDR em GND e Resistor em +V

XivelyDatastream datastreams[] = {
  XivelyDatastream(sensorId, strlen(sensorId), DATASTREAM_FLOAT),
  XivelyDatastream(sensorId2, strlen(sensorId2), DATASTREAM_FLOAT),
};

// numero de sensores que serão monitorados
XivelyFeed feed(FEED_ID, datastreams, 2 /* number of datastreams */);

EthernetClient client;
XivelyClient xivelyclient(client);

void setup() {
  
  pinMode(9,OUTPUT);   // pino em que está conectado o LED que vai piscar durante a coleta de dados
  Serial.begin(9600);

  Serial.println("Cosm Sensor Client Example");
  Serial.println("==========================");

  Serial.println("Initializing network");
  while (Ethernet.begin(mac) != 1) {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(100);
  }

  Serial.println("Network initialized");
  Serial.println();
}

void loop() {
  // Loop principal
 
  if (millis() - lastConnectionTime > connectionInterval) {


    digitalWrite(9,HIGH); // acende o led do pino 9 
    sendData(); // enviando dados para o Xively (led aceso)
    getData(); 
    digitalWrite(9,LOW); //apaga o led do pino 9
    sendData(); // enviando dados para o Xively LED apagado
    getData();// Lendo dados do Xively
    lastConnectionTime = millis(); // atualizar o tempo de conexão 
  }
}

// Envia os valores fornecidos para Cosm, imprimindo alguma informação de depuração à medida que avançamos
void sendData() {
  
  int ResistorPull_Down = analogRead(A0);
  int ResistorPull_Up = analogRead(A1);
  
  float V_ResistorPull_Down= (5.0*ResistorPull_Down)/1024;
  float V_LDR_ResistorPull_Up= 5.0-(5.0*ResistorPull_Down/1024);
  
  datastreams[0].setFloat(V_ResistorPull_Down);
  datastreams[1].setFloat(V_LDR_ResistorPull_Up); //DHT11 humidity value*******
 
  
  Serial.print("V_ResistorPull_Down value");
  Serial.println(datastreams[0].getFloat());
  Serial.print("V_LDR_ResistorPull_Up value");
  Serial.println(datastreams[1].getFloat());
  Serial.println("Uploading to Xively");
  int ret = xivelyclient.put(feed, API_KEY);
  Serial.print("xivelyclient.put returned");
  Serial.println(ret);

  Serial.println();
 
}

// Pega o valor do fluxo de dados de Cosm, imprimindo o valor que recebemos
void getData() {
  
    
  Serial.println("Reading data from Xively");
  int ret = xivelyclient.get(feed, API_KEY);
  Serial.print("xivelyclient.get returned ");
  Serial.println(ret);

  if (ret > 0) {
    Serial.print("Datastream is: ");
    Serial.println(feed[0]);
    Serial.print("Sensor value is: ");
    Serial.println(feed[0].getFloat());

    Serial.print("Datastream is: ");
    Serial.println(feed[1]);
    Serial.print("Sensor value is: ");
    Serial.println(feed[1].getFloat());

    Serial.print("Datastream is: ");
    Serial.println(feed[2]);
    Serial.print("Sensor value is: ");
    Serial.println(feed[2].getFloat());
    
   }

  Serial.println();
}



