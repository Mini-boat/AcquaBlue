
//EC
String inputstring_EC = "";                              // uma string para conter os dados de entrada do PC
String sensorstring_EC = "";                             // uma string para conter os dados do produto Atlas Scientific
boolean input_string_EC_complete = false;                // recebemos todos os dados do PC
boolean sensor_string_EC_complete = false;               // recebemos todos os dados do produto Atlas Scientific

//DO
String inputstring_DO = "";                              // uma string para conter os dados de entrada do PC
String sensorstring_DO = "";                             // uma string para conter os dados do produto Atlas Scientific
boolean input_string_DO_complete = false;                // recebemos todos os dados do PC
boolean sensor_string_DO_complete = false;               // recebemos todos os dados do produto Atlas Scientific
float DO;                                             // usado para manter um número de ponto flutuante que é o DO

// pH
String inputstring_pH = "";                              //a string to hold incoming data from the PC
String sensorstring_pH = "";                             //a string to hold the data from the Atlas Scientific product
boolean input_string_pH_complete = false;                //have we received all the data from the PC
boolean sensor_string_pH_complete = false;               //have we received all the data from the Atlas Scientific product
float pH;                                              //used to hold a floating point number that is the pH


void setup() {                                        //configurar o hardware
  Serial.begin(9600);                                 //definir a taxa de transmissão para a porta serial do hardware_0 a 9600
  Serial1.begin(9600);                                // define a taxa de transmissão para a porta serial do software_1 para 9600
  Serial2.begin(9600);                                // define a taxa de transmissão para a porta serial do software_2 para 9600
  Serial3.begin(9600);                                // define a taxa de transmissão para a porta serial do software_3 para 9600
  
  inputstring_EC.reserve(10);                            // reserve alguns bytes para receber dados do PC
  sensorstring_EC.reserve(30);                           // reserve alguns bytes para receber dados do produto Atlas Scientific
  
  inputstring_DO.reserve(10);                            // reserve alguns bytes para receber dados do PC
  sensorstring_DO.reserve(30);                           // reserve alguns bytes para receber dados do produto Atlas Scientific
  
  inputstring_pH.reserve(10);                            // reserve alguns bytes para receber dados do PC
  sensorstring_pH.reserve(30);                           // reserve alguns bytes para receber dados do produto Atlas Scientific

}

void serialEvent() {  

  if (Serial1.available()){
    char inChar = (char)Serial.read(); 
    inputstring_EC += inChar;
    //inputstring_EC = Serial.readStringUntil(13);   
    //input_string_EC_complete = true; 
  }
  if (Serial2.available()){
     char inChar = (char)Serial.read(); 
     inputstring_DO += inChar;
     //inputstring_DO = Serial.readStringUntil(13);   
      //input_string_DO_complete = true; 
  }
  if (Serial3.available()){
     char inChar = (char)Serial.read(); 
      inputstring_pH += inChar;
      //inputstring_pH = Serial.readStringUntil(13);           
      //input_string_pH_complete = true;
  }
}
void serialEvent1() {                                 // se a porta serial do hardware_1 receber um caractere
  sensorstring_EC = Serial1.readStringUntil(13);         // leia a string até que vejamos um <CR>
  sensor_string_EC_complete = true;                      // define o sinalizador usado para dizer se recebemos uma string completa do PC
}


void serialEvent2() {                                 // se a porta serial do hardware_2 receber um caractere
  sensorstring_DO = Serial2.readStringUntil(13);         // leia a string até que vejamos um <CR>
  sensor_string_DO_complete = true;                      // define o sinalizador usado para dizer se recebemos uma string completa do PC
}


void serialEvent3() {                                 // se a porta serial do hardware_3 receber um caractere
  sensorstring_pH = Serial3.readStringUntil(13);         // leia a string até que vejamos um <CR>
  sensor_string_pH_complete = true;                      //define o sinalizador usado para dizer se recebemos uma string completa do PC
}


void loop() {
  if (input_string_EC_complete == true) {                
    Serial3.print(inputstring_EC);                       
    Serial3.print('\r');                              
    inputstring_EC = "";                                 
    input_string_EC_complete = false;                    
  }

  if (sensor_string_EC_complete == true) {               // se uma string do produto Atlas Scientific foi recebida em sua totalidade
    if (isdigit(sensorstring_EC[0]) == false) {          // se o primeiro caractere da string for um dígito
      Serial.println(sensorstring_EC);                   // envia aquela string para o monitor serial do PC
    }
    else                                              // se o primeiro caractere da string NÃO for um dígito
    {
      print_EC_data();                                // então chame esta função
    }
    sensorstring_EC = "";                                // limpar a string
    sensor_string_EC_complete = false;                   // redefine o sinalizador usado para saber se recebemos uma string completa do produto Atlas Scientific
  }
  
if (input_string_DO_complete == true) {                // se uma string do PC foi recebida em sua totalidade
    Serial3.print(inputstring_DO);                       // envie essa string para o produto Atlas Scientific
    Serial3.print('\r');                              // adiciona um <CR> ao final da string
    inputstring_DO = "";                                 //limpar a string
    input_string_DO_complete = false;                    // redefine o sinalizador usado para dizer se recebemos uma string completa do PC
  }
  
if (sensor_string_DO_complete == true) {               // se uma string do produto Atlas Scientific foi recebida em sua totalidade
    Serial.println(sensorstring_DO);                     // envia aquela string para o monitor serial do PC
   /*                                                 // descomente esta seção para ver como converter o D.O. lendo de uma corda para um flutuador
    if (isdigit(sensorstring_DO[0])) {                   /// se o primeiro caractere da string for um dígito
      DO = sensorstring_DO.toFloat();                    // converte a string em um número de ponto flutuante para que possa ser avaliada pelo Arduino
      if (DO >= 6.0) {                                // se o DO for maior ou igual a 6,0
        Serial.println("high");                       // imprima "high" isso está demonstrando que o Arduino está avaliando o DO como um número e não como uma string
      }
      if (DO <= 5.99) {                               // se o DO for menor ou igual a 5,99
        Serial.println("low");                        // imprime "baixo" isso está demonstrando que o Arduino está avaliando o DO como um número e não como uma string
      }
    }
  */
}
  sensorstring_DO = "";                                  //limpar a string:
  sensor_string_DO_complete = false;                     // redefine o sinalizador usado para saber se recebemos uma string completa do produto Atlas Scientific


 if (input_string_pH_complete == true) {                //if a string from the PC has been received in its entirety
    Serial3.print(inputstring_pH);                       //send that string to the Atlas Scientific product
    Serial3.print('\r');                              //add a <CR> to the end of the string
    inputstring_pH = "";                                 //clear the string
    input_string_pH_complete = false;                    //reset the flag used to tell if we have received a completed string from the PC
  }


  if (sensor_string_pH_complete == true) {               //if a string from the Atlas Scientific product has been received in its entirety
    Serial.println(sensorstring_pH);                     //send that string to the PC's serial monitor
   /*                                                 //uncomment this section to see how to convert the pH reading from a string to a float 
    if (isdigit(sensorstring_pH[0])) {                   //if the first character in the string is a digit
      pH = sensorstring_pH.toFloat();                    //convert the string to a floating point number so it can be evaluated by the Arduino
      if (pH >= 7.0) {                                //if the pH is greater than or equal to 7.0
        Serial.println("high");                       //print "high" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
      if (pH <= 6.99) {                               //if the pH is less than or equal to 6.99
        Serial.println("low");                        //print "low" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
    }
  */
  }
  sensorstring_pH = "";                                  //clear the string:
  sensor_string_pH_complete = false;                     //reset the flag used to tell if we have received a completed string from the Atlas Scientific product
}

void print_EC_data(void) {                            /// esta função irá analisar a string

  char sensorstring_EC_array[30];                        // fazemos um array de char
  char *EC;                                           // ponteiro char usado na análise de string
  char *TDS;                                          // ponteiro char usado na análise de string
  char *SAL;                                          // ponteiro char usado na análise de string
  char *GRAV;                                         // ponteiro char usado na análise de string
  float f_ec;                                         // usado para conter um número de ponto flutuante que é o ECEC

  sensorstring_EC.toCharArray(sensorstring_EC_array, 30);   // converte a string em um array de char
  EC = strtok(sensorstring_EC_array, ",");               // vamos analisar a matriz em cada vírgula
  TDS = strtok(NULL, ",");                            // vamos analisar a matriz em cada vírgula
  SAL = strtok(NULL, ",");                            // vamos analisar a matriz em cada vírgula
  GRAV = strtok(NULL, ",");                           // vamos analisar a matriz em cada vírgula

  Serial.print("EC:");                                // agora imprimimos cada valor que analisamos separadamente
  Serial.println(EC);                                 // este é o valor EC

  Serial.print("TDS:");                               // agora imprimimos cada valor que analisamos separadamente
  Serial.println(TDS);                                // este é o valor EC

  Serial.print("SAL:");                               // agora imprimimos cada valor que analisamos separadamente
  Serial.println(SAL);                                // este é o valor EC

  Serial.print("GRAV:");                              // agora imprimimos cada valor que analisamos separadamente
  Serial.println(GRAV);                               // esta é a gravidade específica
  Serial.println();                                   // isso apenas torna a saída mais fácil de ler

//f_ec= atof(EC);                                     // descomente esta linha para converter o char em um float
}
