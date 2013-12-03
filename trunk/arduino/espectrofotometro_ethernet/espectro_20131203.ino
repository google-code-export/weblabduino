////ARDUINO 1.0+ apenas

////ARDUINO 1.0+ apenas

    //Nomes                       |Abreviações

    //____________________________|_____________

    //AcionarAlinhamentoCabeca    |   AC

    //VerificarEstadoExperimento  |   VEx

    //RodarColetaDados            |   RCD

    //Botao                       |   B

    //EstadoExperimento           |   EEx

#include <Stepper.h>

#include <OneWire.h>

#include <Ethernet.h>

#include <SPI.h>

#define TSL235R = 2; //define pino 22 do MEGA como sendo do conversor de frequencia.

/////////////CONFIGURAÇÕES DA ETHERNET////////////////////////////////////

boolean reading = false;



/////////////////ETHERNET//////////////////////////////////////////////

 // byte ip[] = { 192, 168, 1, 129 };   //setup manual apenas

 // byte gateway[] = { 192, 168, 0, 1 }; //setup manual apenas

 // byte subnet[] = { 255, 255, 255, 0 }; // setup manual apenas



  // Caso seja necessário mudar o valor do endereço MAC (muito raro)//

  byte mac[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x1a };



  EthernetServer server = EthernetServer(80); //porta '80'

  EthernetClient client;

  //obs:  Pinos 10,11,12 & 13 sáo usados pela ethernet shield  



// Agora, crio uma cadeia de caracteres (String) para retornar o estado do experimento;

  char EEx[56]; //Todas as saídas de Client.print serão adicionadas nesta variável, assim o usuário irá realizar a leitura do estado e agir conforme o necessário



////////////////////////////////////////////////////////////////////////



//motores acionamento

const int stepsPerRevolution = 48; // change this to fit the number of steps per revolutions for your motor

Stepper myStepper(stepsPerRevolution, 4,5,6,7); // initialize the stepper library on pins 8 through 11.



  int ColetaDadosExp=36; // se alto corre para a direita e faz leitura

  int AjustePosicao=38; // se alto varre para a esquerda

  int LED=24; // acende o led quando a varredura direita ocorre

  int movimentacaoCabeca = 0;



//motores contagem distância

  int cont=0; //declara a VARIÁVEL "cont" inteira e igual a 0

  int stepCount=0; //declara a VARIÁVEL "stepCount" inteira e igual a 0

  float Dmenor; //declara a VARIÁVEL "Dmenor" flutuante. Esta variável é o diametro da engrenagem menor

  float cnt;

  int intervaloIda = 10; //define a VARIÁVEL "intervaloIda" igual a 10, pode ser alterado pelo usuario, representa o intervalo de passos do motor para cada captura de dados

  int velocidadeIda = 40; //define a VARIÁVEL "velocidadeIda" igual a 100. Esta variável é a velocidade da varredura do sensor na Ida, pode ser alterada pelo usuario



//Comprimento de Onda///////////////////////

  int D = 87; //declara a constante D igualao comprimento do carro do scanner, em mm

  int d = 1762; //declara a constante d, a distancia entre os sulcos da rede de difração (CD), igual a 1660 linhas/nm (issopara o compdeonda ser em nm). 

  float senq; //declara a VARIAVEL senq, oseno do angulo formado entre cursoremX e a hipotenusa. 

  float n; //declara a VARIÁVEL "N" flutuante. Esta variável será especificada na próxima seção. 

  float compdeonda; // declara a VARIÁVEL referente ao comprimento de onda, podendo flutuar (variando as casas decimais, para maior precisão)

  float cursoremX; //declara a VARIÁVEL "cursoremX" flutuante. Esta variável será a responsável pela distância em X percorrida, e será o limite percorrido pelo motor.



//irradiancia////

  

  int ReleLiga=30; //rele aciona se estiver alto no pino 7, ligando a lâmpada (ou seja, rele acionado, liga a lâmpa quando varredura direita ocorre)

  int period = 1000; // Miliseconds of each light frecuency measurement

  int ScalingFactor = 1; // Scaling factor of this sensor

  float area = 0.0092;

  unsigned long counter = 0; // Counter of measurements during the test

  unsigned long currentTime = millis(); 

  unsigned long startTime = currentTime; 

  volatile long pulses = 0; // Counter of measurements of the TSL235R

  unsigned long frequency; // Read the frequency from the digital pin (pulses/second)

  float irradiance;



// Pinagem para a medição do US//

  int echoPinUS = 42; //eco - recebe

  int trigPinUS = 44; // trigger - envia

  float cm; // Esta condição coloca que serão armazenados os dados de distância de aproximação do objeto em rel. ao ultrassom ("float" indica que são dados considerando as casas decimais);

  double tempo; // Definir a variável de tempo,lembrando que o tempo vem dobrado porque é o tempo de ida e volta do ultrassom 

  unsigned long time;





//////Definioções booleanas////////////////////

boolean AC; // Acionar coleta

boolean RCD; // Receber coleta



///////////////////////////////SETUP///////////////////////////////

void setup(void) {

  pinMode(AjustePosicao, INPUT); // pino 5 = Ajuste de Posição

  pinMode(ColetaDadosExp,INPUT); // pino 4 = Coleta de Dados da Experiência

  pinMode(LED,OUTPUT); // pino3 = pino de verificação do LED

  myStepper.setSpeed(100); //ajuste de velocidade dos passos

  Serial.begin(9600); // initialize the serial port

  

  pinMode(echoPinUS, INPUT); // define o pino 12 como entrada (recebe) 

  pinMode(trigPinUS, OUTPUT); // define o pino 13 como saida (envia)

  pinMode(ReleLiga, OUTPUT); // pino 7 = definido como entrada, se estiver em ALTO, aciona o rele, que ligará a lâmpada.

  //pinMode(OneWire, INPUT); //temp. como entrada

  //pinMode(TSL235R, INPUT);



  AC = true;

  RCD = false;

  

  ///////ETHERNET//////////////

  Ethernet.begin(mac); //Ethernet.begin(mac, ip, gateway, subnet); //for manual setup

  server.begin();

  Serial.println(Ethernet.localIP()); 

}





/////////////////////////LOOP///////////////////////////////////// 

void loop(void) {

  ////////////////PARA SCANNER E DISTANCIAS COMANDOS///////

  if(AC==true) AjustarPosicao();

  // Verificamos se o Cliente esta conectado e inicia a coleta caso o Cliente envie um comando de iniciar coleta

  client = client.available();

    if (client){

        if (client.available()) {

          char c = client.read();

          Serial.println(c);

          if(c=='i') { // Testamos se os bytes que vieram do Client conectado sao para uma nova coleta

            IniciarColeta();       

        }

      }


    }

  if(RCD==true) ColetaDados();

  }

//////VERIFICAÇÃO DE ESTADO DO EXPERIMENTO//////////////////////////////////

//Retorna o valor da variável EEx

// void VEx(EthernetClient Client){

   //Client.print(" O experimento está ");

   //Client.print(EEx);

// }

//////////////////////////AJUSTE DE POSIÇÃO COMANDOS////////////////////////

 void AjustarPosicao(){//"Entrou Na Função de Posicionamento da Cabeça"); 

    float CM = ObterCM();//1) Obter valor CM

    if (CM > 18.10){ //2) Se CM < xx, cabeça de leitura frente

      movimentacaoCabeca = 1; // CONFIGURA MOVIMENTAÇ]AO DA CABEÇA PARA FRENTE

    }else //até que cm < yy, cabeça movimenta para trás

      if (CM < 17.90){ 

        movimentacaoCabeca = 2; }// CONFIGURA MOVIMENTAÇ]AO DA CABEÇA PARA TRÁS

/////Foi definido a Movimentação da Cabeça e Entra no Loop Infinito;

      if ((CM <= 18.10) && (CM > 17.90)) { // Enquanto não obtemos a posição ideal verificamos se foi encontrado a posição ideal 

        movimentacaoCabeca = 0;} //CONFIGURA "PARADA" DE CABEÇA DE IMPRESSÃO

      CM = ObterCM(); // Movimenta a cabeça

      MoverCabeca();

      }// Aqui paramos a movimentação da cabeça seja ela para frente ou para trás.////



///////////INSTRUÇÕES DE MOVIMENTO DA CABEÇA DE LEITURA///////////////////////////////

void MoverCabeca() { 

  // Caso seja para frente devemos configurar a cabeça a movimentação no pino 3

  if(movimentacaoCabeca == 1) {

    digitalWrite(ColetaDadosExp, HIGH); // o pino4 vai para alto e o motor gira para a direita

    delay(2);

    digitalWrite(ReleLiga, LOW);//rele acionado, em estado baixo, liga a lâmpada

    digitalWrite(LED,HIGH); // o led acende indicando que para este sentido será efetuada medida

    Serial.println("Ajuste de Posicao Frente");

    myStepper.step(-stepsPerRevolution);//"Ajuste de Posicao Frente";

  }

  if(movimentacaoCabeca == 2) {

    digitalWrite(AjustePosicao, HIGH); // o pino 5 vai para alto, motor gira para a esquerda

    delay(10);

    digitalWrite(ReleLiga, LOW);//rele acionado, em estado baixo, liga a lâmpada

    digitalWrite(LED,LOW); // led apaga e o motorgira para a esquerda

    Serial.println("Ajuste de Posicao Tras");

    myStepper.step(+stepsPerRevolution); //"Ajuste de Posicao Tras";

  }  

  if(movimentacaoCabeca == 0){

    digitalWrite(AjustePosicao, LOW);

    digitalWrite(ColetaDadosExp, LOW);

      RCD = false; 

      AC = false;

    digitalWrite(ReleLiga, HIGH);//rele acionado, em estado alto, liga a lâmpada

    Serial.print("Pare aqui: encontramos a fenda!");


    myStepper.step(-stepsPerRevolution);

  }

}





////////////Iniício de Coleta de Dados COMANDOS////////////////////////////

void IniciarColeta() {

      digitalWrite(ColetaDadosExp,HIGH); // motor gira para a direita

        delay(10);

      digitalWrite(ReleLiga, HIGH);//rele acionado, em estado alto, liga a lâmpada

      digitalWrite(LED,HIGH); // led apaga e o motor gira para a esquerda

        RCD = true;

        AC = false;

      Serial.println("Coleta de Dados do Experimento");


      myStepper.step(-stepsPerRevolution);

      }    

/////////////DADOS DISTANCIA ULTRSSOM COMANDOS////////////////////////// 

  float ObterCM() { 

    digitalWrite(trigPinUS, LOW); //seta o pino 12 com um pulso baixo "LOW" ou desligado ou ainda 0 

    delayMicroseconds(2); // delay de 2 microssegundos 

    digitalWrite(trigPinUS, HIGH); //seta o pino 12 com pulso alto "HIGH" ou ligado ou ainda 1

    delayMicroseconds(10); //delay de 10 microssegundos 

    digitalWrite(trigPinUS, LOW); //seta o pino 12 com pulso baixo novamente

    unsigned long duration = pulseIn(echoPinUS,HIGH); //pulseInt lê o tempo entre a chamada e o pino entrar em high. Esse calculo é baseado em s = v . t.

    cm = duration/58;  // equação para a distância ser calculada em cm.

    time= micros(); // a base de tempo tem que estar em micro para o funcionamento adequado do US

    tempo = time/1000; // deve-se obter distancia vs tempo, entao deve converter a função "time" p/ ms

    

   // client.print(cm,2);

    

   return cm;

  }

  

void PulseCount(){

  pulses++;

} 



void ColetaDados(){ 

  ObterCM();

  if (cm <= 18.01){

     digitalWrite(ReleLiga, HIGH);//rele acionado, em estado alto, liga a lâmpada.

      stepCount++; //soma-se 1 à variável stepCount, equivalente a "stepCount=StepCount+1"

      cont = stepCount; // declara a variável "cont" igual ao valor contido na variável "stepCount"

      n = cont*intervaloIda/48.000; //declara a variável "N" igual a "cont x intervalodeIda / 48 , com 3 casas decimais", ou seja, N é o produto do numero de volta do motor, durante o intervalo de ida, em razão das voltas do motor

      Dmenor = 13.5;

      cursoremX = Dmenor * (n/4) * 3.14159; //declara a variável cursoremX, ou o quanto o motor faz o carro se deslocar em X, levando-se em consid. o diâmetro da engrenagem menor ("engrenagem-motora")e o númerode voltas

      senq=(cursoremX)/sqrt((cursoremX*cursoremX)+(D*D));

      compdeonda = d * senq;

      Serial.println("Coleta de Dados Frente");

      myStepper.step(-stepsPerRevolution); //aciona o motor

      

///////Conversor de Frequência COMANDOS///////////////////

     attachInterrupt(0, PulseCount, RISING);{

       counter++; // Increase the number of measurement

       noInterrupts();

       frequency = pulses /(period/1000); // Calculate the frequency (pulses/second)

       interrupts(); // Request to measure the frequency

         irradiance = (frequency * 0.01) / area;  // Calculate Irradiance (uW/cm2)

         pulses = 0; // resetthe pulses counter

      delay (100); // wait 4 seconds until the next measurement

    }

   }

////////Funcionamento Cabeça de Impressão - COMANDOS////////////////// 

   if ((cm <= 9.69)&&(cm > 8.69)){

      digitalWrite(ReleLiga, LOW);//rele desacionado, em estado baixo, desliga a lâmpada.

          AC = true;

          RCD = false;

          Serial.println("Parou Coleta De Dados"); 


      myStepper.step(+stepsPerRevolution);}



///////IMPRESSÃO DOS DADOS//////////////////

    client.print(irradiance); // print the frequenc(pulses/second)

    client.print(";"); // Imprime em caracteres ASCII " "

    client.print(compdeonda, 3); //Imprime em caracteres ASCII a variável "compdeonda"

    delay (100); // wait 4 seconds until the next measurement

  }
