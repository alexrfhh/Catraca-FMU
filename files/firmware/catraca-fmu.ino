#include <MFRC522.h>            //https://github.com/miguelbalboa/rfid
#include <SPI.h>
#include <arduino-timer.h>      //https://github.com/contrem/arduino-timer/tree/master


/* ---------------------------------------------DEFINES PINOS---------------------------------------------------*/
#define PINO_RST 5
#define PINO_SDA 10
MFRC522 rfid(PINO_SDA, PINO_RST);
/*  RFID 
3,3V - 3.3V
RST - 5 
GND - GND
IRQ - X
MISO - 12
MOSI - 11
SCK - 13
SDA - 10 

*/

#define RELE_IN 4 
#define RELE_OUT 3
/* SOLENOIDE CATRACA  

 RELÉ pino  4 ENTRADA  IN 
 RELÉ pino 3 SAÍDA OUT

*/


#define VERM A2      
#define VERD A1
#define AZUL A0
/* LEDS CATRACA

VERM pino A2
VERD pino A1
AZUL pino A0

*/

#define S_IND1 7
#define S_IND2 6
/* SENSOR INDUTIVO

S_IND1 pino 7
S_IND2 pino 6

*/
/* ---------------------------------------------DEFINES PINOS---------------------------------------------------*/


#define T_LIB 10000   //10 segundos
#define T_BLOCK 3000  //3 segundos

bool tempo_expirado = false;
auto timer = timer_create_default();  // timer com estouro a cada 1 us

bool temp_exp(void *) {
  tempo_expirado = true; //
  return true; // keep timer active? true
}

void setup() 
{
 
  pinMode(VERM,OUTPUT); // LED VERMELHO 
  digitalWrite(VERM,LOW);
  pinMode(VERD,OUTPUT); // LED VERDE
  digitalWrite(VERD,LOW);
  pinMode(AZUL,OUTPUT); // LED AZUL
  digitalWrite(AZUL,HIGH);


  pinMode(RELE_IN,OUTPUT); // RELE SOL ENTRADA
  digitalWrite(RELE_IN,HIGH);
  pinMode(RELE_OUT,OUTPUT); // RELE SOL SAÍDA
  digitalWrite(RELE_OUT,LOW);


  pinMode(S_IND1,INPUT);    // SENSOR INDUTIVO 1
  pinMode(S_IND2,INPUT);    // SENSOR INDUTIVO 2


  SPI.begin();      // Inicia  SPI bus
  rfid.PCD_Init();

  Serial.begin(9600);
  delay(200);
  Serial.println("SW init \n");
  
  Serial.println("Aproxime a sua tag \n");
}

void loop() 
{
  
  //Procura nova tag
  if (!rfid.PICC_IsNewCardPresent()) 
  {
    return;
  }
  
  // Seleciona uma tag
  if (!rfid.PICC_ReadCardSerial()) 
  {
    return;
  }
  
  //Mostra UID na serial
  String conteudo= "";

  for (byte i = 0; i < rfid.uid.size; i++)      
  {
     conteudo.concat(String(rfid.uid.uidByte[i] < HEX ? " 0" : " ")); 
     conteudo.concat(String(rfid.uid.uidByte[i], HEX)); 
  }
  
  Serial.print("UID RFID: ");
  Serial.println(conteudo);

  
  if (conteudo.substring(1) == "57 c2 f2 86" ) //UID 1 - Chaveiro || "09 77 7e 00"
  {
    Serial.println("Acesso Liberado - chaveiro");

    digitalWrite(AZUL,LOW);
    digitalWrite(VERD,HIGH);
    digitalWrite(RELE_IN,LOW);

    timer.in(T_LIB, temp_exp); //configura o timer a cada 10segundos e função de callback
    tempo_expirado = false;
   
    bool s_ind1 = false;
    bool s_ind2 = false;

    while (!tempo_expirado)
    {
      if (digitalRead(S_IND1)== HIGH)
      {
        s_ind1 = true;
        Serial.println("sens1");
      }
      if (digitalRead(S_IND2)== HIGH)
      {
        s_ind2 = true;
        Serial.println("sens2");
      }

      if (s_ind1 && s_ind2)
      {
        Serial.println("Passagem detectada - catraca travada");
        delay(1500);
        timer.cancel();     
        timer.in(T_LIB, temp_exp);
        break;
      }
    timer.tick();       //inicia um estouro 

    }
    
    digitalWrite(RELE_IN,HIGH);
    digitalWrite(VERD,LOW);
    digitalWrite(AZUL,HIGH);
    Serial.println("Acesso Travado");

    
  }

  if (!(conteudo.substring(1) == "57 c2 f2 86")) //UID 1 - Chaveiro || "09 77 7e 00"
  {
    
    Serial.println("Não registrada");
    digitalWrite(AZUL,LOW);
    digitalWrite(VERM,HIGH);
    delay(T_BLOCK);
    digitalWrite(VERM,LOW);
    digitalWrite(AZUL,HIGH);
    
  }
}
