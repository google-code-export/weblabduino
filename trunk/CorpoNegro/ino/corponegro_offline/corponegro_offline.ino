char leitura;
unsigned long time,time2;

void setup() {
  
    Serial.begin(9600);
    pinMode(9,OUTPUT);
    DesligarLampada();
}

void loop() {
   time=millis();
   leitura=Serial.read();
   if (leitura=='L') {
       time2=millis();
       LigarLampada();
       int n;
       
    for (n = 0; n < 200; n++)
    { 
       time=millis()-time2;
       media_temperatura_calotas();
    }
       DesligarLampada();
     }
   }
            
void media_temperatura_calotas(){
  int i;
  int brancoval = A0;
  int pretaval=A1;

  for (i = 0; i < 5; i++){
    brancoval = brancoval + analogRead(A0);     // sensor na porta analógica 0
    pretaval = pretaval + analogRead(A1); 
  }

    brancoval = brancoval/5;   
    pretaval = pretaval/5;     // média
    float temperaturabranca=(5*brancoval*100)/1024;
    float temperaturapreta=(5*pretaval*100)/1024;
     Serial.print(temperaturapreta);
     Serial.print("   ");
     Serial.print(temperaturabranca);
     Serial.print("   ");
     Serial.println(time);
     delay(100);
     
}
      

 
void LigarLampada(){
       digitalWrite(9,HIGH);
   }

 
 void DesligarLampada(){
        digitalWrite(9,LOW);
   }
 

   
 
 
