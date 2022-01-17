#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h> 

#define dsDir 0x68
#define pcfDir 0x4E
//
#define bomba_o 5
#define ventilador_o 6 
#define luz_o 7
#define out_3 8
#define out_4 12
#define out_5 13

byte segundo, minuto, hora, dSem, dia, mes, ano, ctrl;

OneWire ourWire(1);                                      // Se establece el pin 4  como bus OneWire
DallasTemperature sensors(&ourWire); 

//LiquidCrystal_I2C lcd(0x40,20,4);
LiquidCrystal_I2C lcd(0x38, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //lcd.begin(20,4);
  pinMode(bomba_o, OUTPUT);
  pinMode(ventilador_o, OUTPUT);
  pinMode(luz_o, OUTPUT);
  pinMode(out_4, OUTPUT);
  pinMode(out_5, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  Serial.setTimeout(1);
  sensors.begin();


      segundo = 55;
      minuto = 20;
      hora = 4;
      dia = 21;
      mes = 5;
      ano = 36;
  
//  write_ds3231();
//  lcd.begin(20,4);
  
}

void loop() {

  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print (" FORUM - fm   ");

//  if (Serial.available() > 0) { 
//    r_data(); 
//    }

  digitalWrite(bomba_o, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(ventilador_o, HIGH);
  digitalWrite(luz_o, HIGH);
  digitalWrite(out_4, HIGH);
  digitalWrite(out_5, HIGH);
  Serial.println("led encendido");
  delay(1000);                       // wait for a second
  digitalWrite(bomba_o, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(ventilador_o, LOW);
  digitalWrite(luz_o, LOW);
  digitalWrite(out_4, LOW);
  digitalWrite(out_5, LOW);
  //read_ds3231();
  
  Serial.println("led apagado");
  Serial.print("Hora:");
  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);
  Serial.print(":");
  Serial.println(segundo);
  delay(1000);                       // wait for a second
}

bool read_ds3231() {
  Wire.beginTransmission(dsDir);    // Inicia el protocolo en modo lectura.
  Wire.write(0x00);                 // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
    if(Wire.endTransmission() != 0) // Terminamos la escritura y verificamos si el DS1307 respondio
      return false;                 // Escribir la dirección del segundero
  Wire.requestFrom(dsDir, 7);       // Si el DS1307 esta presente, comenzar la lectura de 8 bytes
  
//  for (int cont = 1; cont <= 7; cont ++){
//    vtime[cont] = bcd2bin(Wire.read());
//  } 
  
  segundo = bcd2bin(Wire.read());   // Recibimos el byte del registro 0x00 y lo convertimos a binario
  minuto = bcd2bin(Wire.read());    // Continuamos recibiendo cada uno de los registros
  hora = bcd2bin(Wire.read());
  dSem = bcd2bin(Wire.read());
  dia = bcd2bin(Wire.read());
  mes = bcd2bin(Wire.read());
  ano = bcd2bin(Wire.read());
  ctrl = Wire.read(); 
  return true;
  
  }                                 // Recibir los datos del registro de control en la dirección 0x07
// ==========================================================================================
// ============================ FUNCIÓN PARA ESCRIBIR EL DS3132 =============================
// ==========================================================================================
bool write_ds3231(){
  // Iniciar el intercambio de información con el DS1307 (0x68)
  Wire.beginTransmission(dsDir);  // 1° Byte = Dirección del chip ds1307
  Wire.write(0x00);               // 2° Byte = Dirección del registro de segundos
  Wire.write(bin2bcd(segundo)); // Escribir valores en los registros, nos aseguramos que el bit clock halt
  //Wire.write(bin2bcd(second & 0x7F));
  Wire.write(bin2bcd(minuto));        // Del registro del segundero este desactivado
  Wire.write(bin2bcd(hora));
  Wire.write(bin2bcd(dSem) && 0x6F);
  Wire.write(bin2bcd(dia));
  Wire.write(bin2bcd(mes));
  Wire.write(bin2bcd(ano));
  
//  for (int cont = 1; cont <= 7; cont ++){
//    Wire.write(bin2bcd(vtime[cont]));
//  }

  if (Wire.endTransmission() != 0); // Terminamos la escritura y verificamos si el DS1307 respondio
    return false; }                 // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
    
// ==========================================================================================
// ====================== Conversiones bcd a binario/binario a bcd ==========================
// ==========================================================================================
byte bcd2bin(byte bcd) {
  return (bcd / 16 * 10) + (bcd % 16); } // Convertir decenas y luego unidades a un numero binario
// =============================================================================================
byte bin2bcd(byte bin){
  return (bin / 10 * 16) + (bin % 10); }
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DallasTemperature.h> 

#define dsDir 0x68
#define pcfDir 0x4E
//
#define bomba_o 5
#define ventilador_o 6 
#define luz_o 7
#define out_3 8
#define out_4 12
#define out_5 13

byte segundo, minuto, hora, dSem, dia, mes, ano, ctrl;

OneWire ourWire(1);                                      // Se establece el pin 4  como bus OneWire
DallasTemperature sensors(&ourWire); 

//LiquidCrystal_I2C lcd(0x40,20,4);
LiquidCrystal_I2C lcd(0x38, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  //lcd.begin(20,4);
  pinMode(bomba_o, OUTPUT);
  pinMode(ventilador_o, OUTPUT);
  pinMode(luz_o, OUTPUT);
  pinMode(out_4, OUTPUT);
  pinMode(out_5, OUTPUT);
  Wire.begin();
  Serial.begin(9600);
  Serial.setTimeout(1);
  sensors.begin();


      segundo = 55;
      minuto = 20;
      hora = 4;
      dia = 21;
      mes = 5;
      ano = 36;
  
//  write_ds3231();
//  lcd.begin(20,4);
  
}

void loop() {

  lcd.setCursor ( 0, 1 );        // go to the next line
  lcd.print (" FORUM - fm   ");

//  if (Serial.available() > 0) { 
//    r_data(); 
//    }

  digitalWrite(bomba_o, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(ventilador_o, HIGH);
  digitalWrite(luz_o, HIGH);
  digitalWrite(out_4, HIGH);
  digitalWrite(out_5, HIGH);
  Serial.println("led encendido");
  delay(1000);                       // wait for a second
  digitalWrite(bomba_o, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(ventilador_o, LOW);
  digitalWrite(luz_o, LOW);
  digitalWrite(out_4, LOW);
  digitalWrite(out_5, LOW);
  //read_ds3231();
  
  Serial.println("led apagado");
  Serial.print("Hora:");
  Serial.print(hora);
  Serial.print(":");
  Serial.print(minuto);
  Serial.print(":");
  Serial.println(segundo);
  delay(1000);                       // wait for a second
}

bool read_ds3231() {
  Wire.beginTransmission(dsDir);    // Inicia el protocolo en modo lectura.
  Wire.write(0x00);                 // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
    if(Wire.endTransmission() != 0) // Terminamos la escritura y verificamos si el DS1307 respondio
      return false;                 // Escribir la dirección del segundero
  Wire.requestFrom(dsDir, 7);       // Si el DS1307 esta presente, comenzar la lectura de 8 bytes
  
//  for (int cont = 1; cont <= 7; cont ++){
//    vtime[cont] = bcd2bin(Wire.read());
//  } 
  
  segundo = bcd2bin(Wire.read());   // Recibimos el byte del registro 0x00 y lo convertimos a binario
  minuto = bcd2bin(Wire.read());    // Continuamos recibiendo cada uno de los registros
  hora = bcd2bin(Wire.read());
  dSem = bcd2bin(Wire.read());
  dia = bcd2bin(Wire.read());
  mes = bcd2bin(Wire.read());
  ano = bcd2bin(Wire.read());
  ctrl = Wire.read(); 
  return true;
  
  }                                 // Recibir los datos del registro de control en la dirección 0x07
// ==========================================================================================
// ============================ FUNCIÓN PARA ESCRIBIR EL DS3132 =============================
// ==========================================================================================
bool write_ds3231(){
  // Iniciar el intercambio de información con el DS1307 (0x68)
  Wire.beginTransmission(dsDir);  // 1° Byte = Dirección del chip ds1307
  Wire.write(0x00);               // 2° Byte = Dirección del registro de segundos
  Wire.write(bin2bcd(segundo)); // Escribir valores en los registros, nos aseguramos que el bit clock halt
  //Wire.write(bin2bcd(second & 0x7F));
  Wire.write(bin2bcd(minuto));        // Del registro del segundero este desactivado
  Wire.write(bin2bcd(hora));
  Wire.write(bin2bcd(dSem) && 0x6F);
  Wire.write(bin2bcd(dia));
  Wire.write(bin2bcd(mes));
  Wire.write(bin2bcd(ano));
  
//  for (int cont = 1; cont <= 7; cont ++){
//    Wire.write(bin2bcd(vtime[cont]));
//  }

  if (Wire.endTransmission() != 0); // Terminamos la escritura y verificamos si el DS1307 respondio
    return false; }                 // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
    
// ==========================================================================================
// ====================== Conversiones bcd a binario/binario a bcd ==========================
// ==========================================================================================
byte bcd2bin(byte bcd) {
  return (bcd / 16 * 10) + (bcd % 16); } // Convertir decenas y luego unidades a un numero binario
// =============================================================================================
byte bin2bcd(byte bin){
  return (bin / 10 * 16) + (bin % 10); }
