#include <SPI.h>
#include <Ethernet.h>

//Endereco MAC para o shield Ethernet
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a };
unsigned long tempo = millis();

//Pino de controle da lampada
int lampada = 6;
int statusLampada;

//Mensagem enviada pela comunicacao ethernet para controlar o experimento
char c = 0;
char command = 0;

//Comando recebido com sucesso
boolean runCommand = false;


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

// Verificar clients e receber comandos via ethernet.
checkForCommands();

if(runCommand){

runCommand = false;
  
Serial.print("Executando comando [");
Serial.print(command);
Serial.println("] enviado...");

switch(command){

case 'l':
controlarLampada(command);
break;

case '9':
controlarLampada(command);
break;

default:
Serial.println("Nenhum comando executado");
break;

}

}

}

void checkForCommands(){

//Gets a client that is connected to the server and has data available for reading
EthernetClient client = server.available();

//Verifica se existe um cliente conectado
if (client) {

Serial.println("Cliente Conectado");

//Verifica se existem dados remanescentes do cliente, conectado ou nao
if (client.connected()) {

c = client.read();//Faz a leitura de um caracter
Serial.print("Caracter recebido [");
Serial.print(c);
Serial.println("]");

if ( c >= 0 & c <= 127 ){// Testa se o caracter é valido. (client.read irá enviar -1 para sinalizar que não existem mais dados)

Serial.println("Caracter valido");

}else{

Serial.println("Caracter nao reconhecido na tabela ASCII, finalizando conexao");
client.flush(); //Exclusao de qualquer dado remanescente dos clients
client.stop(); // Fechar qualquer conexao

}

//checar sinalizacao do final do comando
if(c == 13 || c == 10 || c== -1){
Serial.println("Caracter de finalização detectado, encerrando conexao");
client.flush(); //Exclusao de qualquer dado remanescente dos clients
client.stop(); // Fechar qualquer conexao
}

command = c ;
Serial.print("Caracter [");
Serial.print(command);
Serial.println("] armazenado");
runCommand = true;

client.flush(); //Exclusao de qualquer dado remanescente dos clients
client.stop(); // Fechar qualquer conexao


}

}

}

void temperaturaMediaCalotas(){

int i;
int calotaBrancaAnalog = A0;
int calotaPretaAnalog = A1;

//Coleta 5 amostas
for (i = 0; i < 5; i++){
calotaBrancaAnalog = calotaBrancaAnalog + analogRead(A0);
calotaPretaAnalog = calotaPretaAnalog + analogRead(A1);
}


//Media das 5 amostras
calotaBrancaAnalog = calotaBrancaAnalog/5;
calotaPretaAnalog = calotaPretaAnalog/5;

float temperaturaCalotaBranca=(5*calotaBrancaAnalog*100)/1023;
float temperaturaCalotaPreta=(5*calotaPretaAnalog*100)/1023;

Serial.print(temperaturaCalotaPreta);
Serial.print(" ");
Serial.print(temperaturaCalotaBranca);
Serial.print(" ");
Serial.println(tempo);
delay(100);
}

void controlarLampada(char command){

statusLampada = digitalRead(lampada);
 
if(statusLampada == 1){
  Serial.println("Desligando lampada...");
  digitalWrite(lampada,LOW);
}else{
  Serial.println("Ligando lampada...");
  digitalWrite(lampada,HIGH);
}

}