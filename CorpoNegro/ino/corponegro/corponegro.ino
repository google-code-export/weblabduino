#include <SPI.h>
#include <Ethernet.h>

//Endereco MAC para o shield Ethernet
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a };
unsigned long tempo = millis();

//Pino de controle da lampada
int lampada = 9;
int statusLampada;

//Mensagem enviada pela comunicacao ethernet para controlar o experimento
String clientMsg ="";

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

// listen for incoming clients, and read data from them.
checkForCommands();

if(clientMsg != ""){
Serial.print("Executando comando:");
Serial.println(clientMsg);
execCommand(clientMsg);
}

}

void checkForCommands(){

//Gets a client that is connected to the server and has data available for reading
EthernetClient client = server.available();

clientMsg ="";

//Verifica se existe um cliente conectado
if (client == true) {

Serial.println("Cliente Conectado");

//Verifica se existem dados remanescentes do cliente, conectado ou nao
while (client.connected()) {

char c = client.read();//Faz a leitura de um caracter

//checar sinalizacao do final do comando
if(c == 13 || c == 10){
Serial.println("Final do comando atingido, finalizando conexao");  
client.flush(); //Exclusao de qualquer dado remanescente dos clients
client.stop(); // Fechar qualquer conexao
}

//checar o tamanho da String clientMsg para nao travar o hardware
if(clientMsg.length() > 20 ){
Serial.println("O comando excedeu seu tamanho limite, finalizando conexao");  
client.flush(); //Exclusao de qualquer dado remanescente dos clients
client.stop(); // Fechar qualquer conexao
}


if ( c <= 127 & c>= 0 ){// Testa se o caracter é valido. (client.read irá enviar -1 para sinalizar que não existem mais dados)

clientMsg+=c;//Armazena os dados numa cadeia de caracteres (string)

}else{

Serial.println("Caracter nao reconhecido na tabela ASCII, finalizando conexao");  
client.flush(); //Exclusao de qualquer dado remanescente dos clients
client.stop(); // Fechar qualquer conexao

}

}

}
 
client.flush(); //Exclusao de qualquer dado remanescente dos clients
client.stop(); // Fechar qualquer conexao

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

void execCommand(String clientMsg){

Serial.print("Comando [");
Serial.print(clientMsg);
Serial.println("] executado com sucesso.");

}