/* Cosm Arduino sensor client example.
 *
`` * This sketch demonstrates connecting an Arduino to Cosm (https://cosm.com),
 * using the new Arduino library to send and receive data.

/**
DHT11 temp and humidity sensor added to the COSM example code
**/

#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Xively.h>
#include <dht11.h>

//DHT11*********************************************************************
dht11 DHT11;
#define DHT11PIN 7//pin DHT11 sensor is connected to
//DHT11*********************************************************************


#define API_KEY "    " // Chave Xively
#define FEED_ID // ID Xively

// MAC address for your Ethernet shield
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
int LDR = A1;
int CO=A0;
int som=A2;

unsigned long lastConnectionTime = 0;                // last time we connected to Cosm
const unsigned long connectionInterval = 1500;      // delay between connecting to Cosm in milliseconds

// Initialize the Cosm library

// Define the string for our datastream ID
char sensorId[] = "sensor_de_luz";
char sensorId2[] = "sensor_humidade";
char sensorId3[] = "sensor_temperatura";
char sensorId4[]= "sensor_sonoro";
char sensorId5[]= "sensor_monoxido_de_carbono";

XivelyDatastream datastreams[] = {
  XivelyDatastream(sensorId, strlen(sensorId), DATASTREAM_FLOAT),
  XivelyDatastream(sensorId2, strlen(sensorId2), DATASTREAM_FLOAT),
  XivelyDatastream(sensorId3, strlen(sensorId3), DATASTREAM_FLOAT),
  XivelyDatastream(sensorId4, strlen(sensorId4), DATASTREAM_FLOAT),
  XivelyDatastream(sensorId5, strlen(sensorId5), DATASTREAM_FLOAT),
};

// Wrap the datastream into a feed
XivelyFeed feed(FEED_ID, datastreams, 5 /* number of datastreams */);

EthernetClient client;
XivelyClient xivelyclient(client);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.println("Cosm Sensor Client Example");
  Serial.println("==========================");

  Serial.println("Initializing network");
  while (Ethernet.begin(mac) != 1) {
    Serial.println("Error getting IP address via DHCP, trying again...");
    delay(500);
  }

  Serial.println("Network initialized");
  Serial.println();
}

void loop() {
  // main program loop
  if (millis() - lastConnectionTime > connectionInterval) {

//check DHT11 sensor is working OK    
    int chk = DHT11.read(DHT11PIN);
    Serial.print("Read DHT11 sensor: ");
  switch (chk)
  {
    case 0: Serial.println("OK"); break;
    case -1: Serial.println("Checksum error"); break;
    case -2: Serial.println("Time out error"); break;
    default: Serial.println("Unknown error"); break;
  }

    sendData(); // send data to Cosm
    getData(); // read the datastream back from Cosm
    lastConnectionTime = millis(); // update connection time so we wait before connecting again
  }
}

// send the supplied values to Cosm, printing some debug information as we go
void sendData() {
  int sensorValue = analogRead(LDR);
  int humidityDHT11 = ((float)DHT11.humidity);
  int tempDHT11 = ((float)DHT11.temperature);
  int CO=analogRead(CO);
  int som=analogRead(som);
  
  datastreams[0].setFloat(sensorValue);
  datastreams[1].setFloat(humidityDHT11); //DHT11 humidity value*******
  datastreams[2].setFloat(tempDHT11); //DHT11 temp value********
  datastreams[3].setFloat(som);
  datastreams[4].setFloat(CO);
  
  Serial.print("Read sensor value ");
  Serial.println(datastreams[0].getFloat());
  Serial.print("Read DHT11 humidity sensor value ");
  Serial.println(datastreams[1].getFloat());
  Serial.print("Read DHT11 temperature sensor value ");
  Serial.println(datastreams[2].getFloat());
  Serial.print("Read sonoro sensor value ");
  Serial.println(datastreams[3].getFloat());
  Serial.print("Read CO sensor value ");
  Serial.println(datastreams[4].getFloat());

  Serial.println("Uploading to Xively");
  int ret = xivelyclient.put(feed, API_KEY);
  Serial.print("xivelyclient.put returned");
  Serial.println(ret);

  Serial.println();
}

// get the value of the datastream from Cosm, printing out the value we received
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

