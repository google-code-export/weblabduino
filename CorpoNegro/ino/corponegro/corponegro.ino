#include <SPI.h>
#include <Ethernet.h>

//Endereco MAC para o shield Ethernet
byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x3a };

//Pino de controle da lampada
int lampada = 6;
int statusLampada;

//Mensagem enviada pela comunicacao ethernet para controlar o experimento
char c = 0;
char command = 0;

//Comando recebido com sucesso
boolean runCommand = false;

//Gets a client that is connected to the server and has data available for reading
EthernetClient client;

// Acesso ao shield ethernet pela porta 80
EthernetServer server(80);

void setup() {

  // Inicia-se a comunicaço serial e aguarda uma resposta
  Serial.begin(9600);
  
  conectarRede();

  pinMode(lampada,OUTPUT);
  digitalWrite(lampada,LOW);

}


void loop() {
  
  client = server.available();
   
  // Verificar clients e receber comandos via ethernet.
  checkForCommands(client);
  
  if(runCommand){
  
  runCommand = false;
    
  Serial.print("Executando comando [");
  Serial.print(command);
  Serial.println("] enviado...");
  
    switch(command){
    
    case 'l':
    controlarLampada();
    client.flush(); //Exclusao de qualquer dado remanescente dos clients
    client.stop(); // Fechar qualquer conexao
    break;
    
    case 'd':
    temperaturaCalotas(client);
    client.flush(); //Exclusao de qualquer dado remanescente dos clients
    client.stop(); // Fechar qualquer conexao
    
    break;
    
    case '9':
    resetExperimento();
    client.flush(); //Exclusao de qualquer dado remanescente dos clients
    client.stop(); // Fechar qualquer conexao
    break;
    
    default:
    Serial.println("Comando nao cadastrado");
    client.flush(); //Exclusao de qualquer dado remanescente dos clients
    client.stop(); // Fechar qualquer conexao
    break;
    
    }
  
  }

}

void checkForCommands(EthernetClient client){
  

  //Verifica se existe um cliente conectado
  if (client) {
  
  Serial.println("Cliente Conectado");
  
  //Verifica se existem dados remanescentes do cliente, conectado ou nao
  if(client.connected()) {
  
    c = client.read();//Faz a leitura de um caracter
    command = c ;
    Serial.print("Caracter recebido [");
    Serial.print(c);
    Serial.println("]");

    runCommand = true;
    
    if ( c >= 0 & c <= 127 ){// Testa se o caracter é valido. (client.read irá enviar -1 para sinalizar que não existem mais dados)
    
    Serial.println("Caracter valido");
    
    }else{
    
    Serial.println("Caracter nao reconhecido na tabela ASCII, finalizando conexao");
    client.flush(); //Exclusao de qualquer dado remanescente dos clients
    client.stop(); // Fechar qualquer conexao
    runCommand = false; 
    }
    
    //checar sinalizacao do final do comando
    if(c == 13 || c == 10 || c== -1){
    Serial.println("Caracter de finalização detectado, encerrando conexao");
    client.flush(); //Exclusao de qualquer dado remanescente dos clients
    client.stop(); // Fechar qualquer conexao
    runCommand = false; 
    }
        
    }
  
  }

}

void temperaturaCalotas(EthernetClient client){

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

int a = 6;

while(a>0){
  a--;
  Serial.print(temperaturaCalotaPreta);
  Serial.print(";");
  Serial.println(temperaturaCalotaBranca);
  
  client.print(temperaturaCalotaPreta);
  client.print('-');
  client.println(temperaturaCalotaBranca);
  
  delay(1000);
}



}

void controlarLampada(){

statusLampada = digitalRead(lampada);
 
if(statusLampada == 1){
  Serial.println("Lampada ligada, desligando lampada...");
  digitalWrite(lampada,LOW);
}else{
  Serial.println("Lampada desligada, Ligando lampada...");
  digitalWrite(lampada,HIGH);
}
}

void conectarRede(){
  
  if(!Ethernet.begin(mac)){
    Serial.println("conectando com a rede...");
    Ethernet.begin(mac);
    delay(1000);
  }
  delay(200);
  system("/etc/init.d/networking restart");
  delay(200);
  server.begin();
  delay(200);
  Serial.print("IP: ");
  Serial.println(Ethernet.localIP());
  
}

void resetExperimento(){

  Serial.println("Reiniciando experimento...");
  conectarRede();
  digitalWrite(lampada,LOW);
  
}
