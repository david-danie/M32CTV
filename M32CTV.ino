#include <LiquidCrystal.h>
#include <Wire.h>
#include <EEPROM.h>

#include <SoftwareSerial.h>
SoftwareSerial mySerial(0, 1); // RX, TX

#define dsDir 0x68

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 24, en = 25, d4 = 26, d5 = 27, d6 = 28, d7 = 29;

byte vtime[9];
byte segundo, minuto, hora, dSem, dia, mes, ano;

byte v_verde, v_rojo, v_azul;
byte fotope;
byte dia_cre;
byte sem_cre;
byte pag_config0;
bool b_config0;
byte dato [20];

byte sem_ctv;
byte dia_ctv;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7); // 24,25,26,27,28,29,30

void setup() {
  
  Wire.begin();
  Serial.begin(9600);
  Serial.setTimeout(1);
  mySerial.begin(9600);
  lcd.begin(20, 4);
  
  segundo = 55;              // se configura la fecha y la hora default
  minuto = 20;              // 21 de mayo de 1936
  hora = 4;                 // 04:20:30
  dSem = 6;
  dia = 21;
  mes = 05;
  ano = 36;

  fotope = 0;
  pag_config0 = 0;
  b_config0 = 0;

  write_ds3231();
  
  while(b_config0 == 0){
    lcd_m1(); 
  }
}

void loop() {
  read_ds3231();
  delay(1000);
  
  lcd_m1();
  manda_inf();
  
}

void manda_inf(){
  Serial.print("D: ");
  if (hora < 10){ Serial.print("0"); }
  Serial.print(hora);
  Serial.print(":");
  if (minuto < 10){ Serial.print("0"); }
  Serial.print(minuto);
  Serial.print(":");
  if (segundo < 10){ Serial.print("0"); }
  Serial.print(segundo);
  Serial.print(' ');
  if (dia < 10){ Serial.print("0"); }
  Serial.print(dia);
  Serial.print("/");
  if (mes < 10){ Serial.print("0"); }
  Serial.print(mes);
  Serial.print("/");
  if (ano < 10){ Serial.print("0"); }
  Serial.println(ano);
  
  Serial.println(); 
}

void lcd_m1() {
  lcd.setCursor(0,0); 
  lcd.print("Nivel:");   
  lcd.print(" ");

  
  lcd.setCursor(0,1);                                 // Se imprime la información del segundo renglon en LCD
  lcd.print("A:");
  lcd.print(100); 
  lcd.print("%");
  lcd.print(" ");
  lcd.print("Fp:");
  lcd.print(12);
  lcd.print(" "); 
  lcd.print("a:");
  if (sem_ctv < 10){ lcd.print("0"); }
  lcd.print(sem_ctv); 
  lcd.print("/");
  if (dia_ctv < 10){ lcd.print("0"); }
  lcd.print(dia_ctv);

  lcd.setCursor(0,2);                                     // Se imprime la información del tercer renglon en LCD
  lcd.print("R:");
  lcd.print(100); 
  lcd.print("%");
  lcd.print(" ");
  lcd.setCursor(15,2);  
  if (hora < 10){ lcd.print("0"); }                  // Se imprime la información del primer renglon en LCD
  lcd.print(hora); lcd.print(":");
  if (minuto < 10){ lcd.print("0"); }
  lcd.print(minuto);
  //lcd.print(" ");
 
  lcd.setCursor(0,3);                                   // Se imprime la información del cuarto renglon en LCD
  lcd.print("V:");
  lcd.print(100); 
  lcd.print("%");
  lcd.print(" ");
  lcd.print("T:");
  lcd.print(20);
  lcd.print((char)223);
  lcd.print("C"); 
  lcd.print(" H:100%");
}

void lcd_m0() {
  lcd.clear();
  delay(500);
  lcd.setCursor(4, 1);
  lcd.print('D');
  delay(400);
  lcd.setCursor(3,1);
  lcd.print('I');
  delay(400);
  lcd.setCursor(5,1);
  lcd.print('A');
  delay(400);
  lcd.setCursor(6,1);
  lcd.print('N');
  delay(250);
  lcd.setCursor(6,1);
  lcd.print('M');
  delay(150);
  lcd.setCursor(7,1);
  lcd.print('A');
  delay(400);
  lcd.setCursor(8,1);
  lcd.print('R');
  delay(400);
  lcd.setCursor(9,1);
  lcd.print('H');
  delay(1000);
  lcd.setCursor(3,1);
  lcd.print("IDAMARH V. 1.6");
  delay(1000);
  lcd.clear();
}

// ==========================================================================================
// ============================ FUNCIÓN PARA LEER EL DS3132 =================================
// ==========================================================================================
bool read_ds3231() {
  Wire.beginTransmission(dsDir);    // Inicia el protocolo en modo lectura.
  Wire.write(0x00);                 // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
    if(Wire.endTransmission() != 0) // Terminamos la escritura y verificamos si el DS1307 respondio
      return false;                 // Escribir la dirección del segundero
  Wire.requestFrom(dsDir, 7);       // Si el DS1307 esta presente, comenzar la lectura de 8 bytes
  
  segundo = bcd2bin(Wire.read());   // Recibimos el byte del registro 0x00 y lo convertimos a binario
  minuto = bcd2bin(Wire.read());    // Continuamos recibiendo cada uno de los registros
  hora = bcd2bin(Wire.read());
  dSem = bcd2bin(Wire.read());
  dia = bcd2bin(Wire.read());
  mes = bcd2bin(Wire.read());
  ano = bcd2bin(Wire.read());
  //ctrl = Wire.read();  
  return true;
  }                                 // Recibir los datos del registro de control en la dirección 0x07
// ==========================================================================================
// ============================ FUNCIÓN PARA ESCRIBIR EL DS3132 =============================
// ==========================================================================================
bool write_ds3231(){
  // Iniciar el intercambio de información con el DS1307 (0x68)
  Wire.beginTransmission(dsDir);  // 1° Byte = Dirección del chip ds
  Wire.write(0x00);               // 2° Byte = Dirección del registro de segundos
  Wire.write(bin2bcd(segundo)); // Escribir valores en los registros, nos aseguramos que el bit clock halt
  //Wire.write(bin2bcd(second & 0x7F));
  Wire.write(bin2bcd(minuto));        // Del registro del segundero este desactivado
  Wire.write(bin2bcd(hora));
  Wire.write(bin2bcd(dSem));
  //Wire.write(bin2bcd(dSem) && 0x6F);
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
// ==========================================================================================
// ====================== Imprime la fecha por puerto serial ==========================
// ==========================================================================================
