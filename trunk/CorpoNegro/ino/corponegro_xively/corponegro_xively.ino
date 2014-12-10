#include <SPI.h>
#include <Ethernet.h>
#include <HttpClient.h>
#include <Xively.h>

// MAC address for your Ethernet shield
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

// Your Xively key to let you upload data
char xivelyKey[] = "";

// Analog pin which we're monitoring (0 and 1 are used by the Ethernet shield)
int sensorPin = 0;
int sensorPin1 = 1;

// Define the strings for our datastream IDs
char sensorId[] = "calota_branca";
char sensorId1[] = "calota_preta";

XivelyDatastream datastreams[] = {
XivelyDatastream(sensorId, strlen(sensorId), DATASTREAM_FLOAT),
XivelyDatastream(sensorId1, strlen(sensorId1), DATASTREAM_FLOAT),
};
// Finally, wrap the datastreams into a feed
XivelyFeed feed(, datastreams, 2 /* number of datastreams */);

EthernetClient client;
XivelyClient xivelyclient(client);

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);

Serial.println("Starting multiple datastream upload to Xively...");
Serial.println();

while (Ethernet.begin(mac) != 1)
{
Serial.println("Error getting IP address via DHCP, trying again...");
delay(15000);
}
system("/etc/init.d/networking restart");
}

void loop() {
int sensorValue = analogRead(sensorPin);
int sensorValue1 = analogRead(sensorPin1);


datastreams[0].setFloat(5*sensorValue*100/1023);
Serial.print("Read sensor value ");
Serial.println(datastreams[0].getFloat());

datastreams[1].setFloat(5*sensorValue1*100/1023);
Serial.print("Read sensor value ");
Serial.println(datastreams[1].getFloat());

Serial.println("Uploading it to Xively");
int ret = xivelyclient.put(feed, xivelyKey);
Serial.print("xivelyclient.put returned ");
Serial.println(ret);

Serial.println();
delay(500);
}


