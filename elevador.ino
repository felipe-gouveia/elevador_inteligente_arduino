#include <Keypad.h>

#define MOTORDIR01 2 //definimos que a porta 2 será o bit 1 da ponte H do motor direito (0x)  
#define MOTORDIR02 3 //definimos que a porta 3 será o bit 2 da ponte H do motor direito (x0)  
#define MOTORESQ01 4 //definimos que a porta 4 será o bit 1 da ponte H do motor esquerdo(0x)  
#define MOTORESQ02 5 //definimos que a porta 5 será o bit 2 da ponte H do motor esquerdo(x0)  

//a ponte H funciona da seguinte maneira: (MOTORDIR01,MOTORDIR02,MOTORESQ01,MOTORESQ02)  
// (0,1,0,1) Anda pra frente  
// (1,0,1,0) Anda pra trás  
// (0,0,0,0) Parado  
boolean defeito_elevador2 = 0;
boolean defeito_elevador1 = 0;
const byte ROWS = 3; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 8, 7, 6 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 12, 11, 10, 9 }; 

#define ALARME  0
// Create the Keypad
Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

int andar_elevador1 = 1;
int andar_elevador2 = 1;

void setup()
{
  ////Serial.begin(9600);
  pinMode(ALARME, OUTPUT);
  // OUTPUT  
  pinMode(MOTORDIR01, OUTPUT);  
  pinMode(MOTORDIR02, OUTPUT);  
  pinMode(MOTORESQ01, OUTPUT);  
  pinMode(MOTORESQ02, OUTPUT);  
}

void loop()
{
  //Serial.println("Comecei o loop");
  digitalWrite(ALARME, LOW);
    if (defeito_elevador1 and defeito_elevador2) {
    //Serial.println(defeito_elevador1);
    //Serial.println(defeito_ele  vador2);
      digitalWrite(ALARME, HIGH);
  }
  
  char key = kpd.getKey();
  if(key)  // Check for a valid key.
  {
   //Serial.println(key);
    switch (key)
    {
      case '9':
      
        //Serial.println("Mandando o elevador para o primeiro andar.");
        calcula_elevador(1);
        break;
      case '8':
      //Serial.println("Mandando o elevador para o segundo andar.");
        
        calcula_elevador(2);
        break;
      case '7':
      //Serial.println("Mandando o elevador para o terceiro andar.");
        calcula_elevador(3);
        break;
      case '6':
        calcula_elevador(4);
        break;
      case '5':
        calcula_elevador(5);
        break;
      case '4':
        defeito_ambos();
        break;
      case '1':
        randomiza();
        break;
      case '2':
        reseta();
        break;
      case '3':
        defeito();
        break;
      default:
        break;
    }
  }
}

/********** Movimentação do Elevador ****************/
 void calcula_elevador(int andar_atual){

    //Serial.print("Usuário chamou o elevador do andar: ");
    //Serial.println(andar_atual);
    int resultado_diferenca1 = andar_atual - andar_elevador1;
    int resultado_diferenca2 = andar_atual - andar_elevador2;

    //Serial.print("Distância do elevador 1: ");
    //Serial.println(resultado_diferenca1);
    //Serial.print("Distância do elevador 2: ");
    //Serial.println(resultado_diferenca2);
    //Serial.print("Distância do elevador 1 em ABS: ");
    //Serial.println(abs(resultado_diferenca1));
    //Serial.print("Distância do elevador 2 em ABS: ");
    //Serial.println(abs(resultado_diferenca2));


    //Se estiver com defeito no elevador2, então só utiliza o elevador 1
    if (!defeito_elevador2) {
      
    //Se a distancia do andar atual para o elevador 1 for menor que a distancia ao elevador 2
    if (abs(resultado_diferenca1) < abs(resultado_diferenca2)){

      //Se o elevador 1 está abaixo do andar atual, elevador 1 sobe
      if (resultado_diferenca1 > 0) {
        cima1(abs(resultado_diferenca1)*830);
        andar_elevador1 = andar_atual;

      //Se não, elevador desce
      } else {
        baixo1(abs(resultado_diferenca1)*830);
        andar_elevador1 = andar_atual;
      }

    //Se a distancia do andar atual para o elevador 2 for menor que a distancia ao elevador 1
    } else if (abs(resultado_diferenca2) < abs(resultado_diferenca1)){

      //Se o elevador 2 está abaixo do andar atual, elevador 1 sobe
      if (resultado_diferenca2 > 0) {
        cima2(abs(resultado_diferenca2)*830);
        andar_elevador2 = andar_atual;

      //Se não, elevador desce  
      } else {
        baixo2(abs(resultado_diferenca2)*830);
        andar_elevador2 = andar_atual;
      }
    }
    else {
      
        //Se o elevador 1 está abaixo do andar atual, elevador 1 sobe
      if (resultado_diferenca1 > 0) {
        cima1(abs(resultado_diferenca1)*830);
        andar_elevador1 = andar_atual;

      //Se não, elevador desce
      } else {
        baixo1(abs(resultado_diferenca1)*830);
        andar_elevador1 = andar_atual;
      }
      
    }
   }
   else {
    
    if (resultado_diferenca1 > 0) {
        cima1(abs(resultado_diferenca1)*830);
        andar_elevador1 = andar_atual;

      //Se não, elevador desce
      } else {
        baixo1(abs(resultado_diferenca1)*830);
        andar_elevador1 = andar_atual;
      }
    
    
   }
 }

 void cima1(int tempo){ 
    //Serial.println("Estou girando o motor 1");
    digitalWrite(MOTORDIR01, LOW);  
    digitalWrite(MOTORDIR02, HIGH);
  delay(tempo);
  parado1();
 }
 void cima2(int tempo){ 
    //Serial.println("estoy aqui");
    digitalWrite(MOTORESQ01, LOW);  
    digitalWrite(MOTORESQ02, HIGH);
  delay(tempo);
  parado2();
 }
   
  void baixo1(int tempo){  
      digitalWrite(MOTORDIR01, HIGH);  
      digitalWrite(MOTORDIR02, LOW);  
    
    delay(tempo);
    parado1();
  }

   void baixo2(int tempo){  
      digitalWrite(MOTORESQ01, HIGH);  
      digitalWrite(MOTORESQ02, LOW);
    delay(tempo);
    parado2();
  }
  void parado1(){
      //Serial.println("Parei o elevador 1");
      digitalWrite(MOTORDIR01, LOW);  
      digitalWrite(MOTORDIR02, LOW);  
  }
  void parado2(){
      //Serial.println("Parei o elevador 2");
      digitalWrite(MOTORESQ01, LOW);  
      digitalWrite(MOTORESQ02, LOW); 
  }

  void randomiza(){
    int random1 = random(1,5);
    int random2 = random(1,5);
    //Serial.println("Gerei os números, vou mandar os elevadores agora:");
    cima1( random1*830);
    delay(1000);
    cima2( random2*830);
  }

   void reseta(){

    //Desce o elevador 1 até o 1º andar
    digitalWrite(MOTORDIR01, HIGH);  
    digitalWrite(MOTORDIR02, LOW);
    delay(andar_elevador1*830 - 830);
    digitalWrite(MOTORDIR01, LOW);  
    digitalWrite(MOTORDIR02, LOW);
    andar_elevador1 = 1;

    //Desce o elevador 2 até o 1º andar
    digitalWrite(MOTORESQ01, HIGH);  
    digitalWrite(MOTORESQ02, LOW); 
    delay(andar_elevador2*830 - 830);
    digitalWrite(MOTORESQ01, LOW);  
    digitalWrite(MOTORESQ02, LOW);
    andar_elevador2 = 1;
  }

  void defeito(){
    defeito_elevador2 = !defeito_elevador2;    
  }
  
  void defeito_ambos(){
    defeito_elevador2 = !defeito_elevador2;
    defeito_elevador1 = !defeito_elevador1;
  }

