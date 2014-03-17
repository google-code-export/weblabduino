/*
Os devices deverão ser conectados no relé e são acionados com as frequencias pré definidas de 100Hz e 250Hz
*/



int device_1 = 13;  //ligar device_1 no pino 13
int device_2 = 7;  //ligar device_2 no pino 7
int ledVermelho = 2;
int ledVerde = 3;
int ledAzul = 4;
int sensorValue;

byte com = 0; // Receber os dados do modulo Voice

// Leitura de estado dos DEVICES conectados
int deviceState_1 = 0;         // Variavel de estado do DEVICE 1 
int deviceState_2 = 0;         // Variavel de estado do DEVICE 2


void setup() 
{ 
  
    Serial.begin(9600);
    pinMode(device_1, OUTPUT);	// Configuração do pino do DEVICE 1 como saída de dados
    pinMode(device_2, OUTPUT);	// Configuração do pino do DEVICE 2 como saída de dados

    pinMode(ledVermelho, OUTPUT);
    pinMode(ledVerde, OUTPUT);     
    pinMode(ledAzul, OUTPUT);    

    digitalWrite(device_1,LOW); //Configuração inicial do estado do DEVICE 1
    digitalWrite(device_2,LOW); //Configuração inicial do estado do DEVICE 2

    delay(2000);
    
    Serial.write(0xAA); // envia comando head para o modulo voice
    Serial.write(0x37); // envia comando de configuracao para o modulo voice: switch to compact mode 
    
    delay(1000);
    
    Serial.write(0xAA); // envia comando head para o modulo voice
    Serial.write(0x21);// envia comando para importar o segundo grupo de menssagens pré gravadas no modulo voice
    
    
    
} 

void loop()	
{ 

  while(Serial.available())
  {
      // Verificação do estado dos devices
      deviceState_1 = digitalRead(device_1);
      deviceState_2 = digitalRead(device_2);
   
      com = Serial.read(); // Atribui a variavel "com" dados recebidos pela serial 
      
      switch(com)
      {
        
            //Controle do DEVICE_1 - Comando de acionamento por voz: lampada
            case 0x11:
            
            if (deviceState_1 == HIGH) {     
              // Desliga device_1    
              digitalWrite(device_1, LOW);  
            } 
            else {
              // Liga device_1
              digitalWrite(device_1, HIGH); 
            }
            break;
            
            //Controle DEVICE_2 - Comando de acionamento por voz: piscar
            case 0x12:

            if (deviceState_2 == HIGH) {     
              // Desliga device_2    
              digitalWrite(device_2, LOW);  
            } 
            else {
              // Liga device_2
              digitalWrite(device_2, HIGH); 
            }
            break;
            
            //Controle LED - Comando de acionamento por voz: Vermelho
            case 0x13:
          
          //Leitura ledVermelho  
          digitalWrite(ledVermelho, HIGH);
          delay(500);  
          
          sensorValue = analogRead(A0); 
          
          Serial.println("Vermelho");
          Serial.println(sensorValue);
        
          digitalWrite(ledVermelho, LOW);
          delay(500);
     
            break;
            
            //Controle LED - Comando de acionamento por voz: Verde
            case 0x14:
          
          digitalWrite(ledVerde, HIGH);
          delay(500);  
          
          sensorValue = analogRead(A0); 
          
          Serial.println("Verde");
          Serial.println(sensorValue);
        
          digitalWrite(ledVerde, LOW);
          delay(500);

            break;
            
            //Controle LED - Comando de acionamento por voz: Azul
            case 0x15:
          
           //Leitura ledAzul
          digitalWrite(ledAzul, HIGH);
          delay(500);  
          
          sensorValue = analogRead(A0); 
          
          Serial.println("Azul");
          Serial.println(sensorValue);
        
          digitalWrite(ledAzul, LOW);
          delay(500);    
         

          break;
  
        }
   }
}


