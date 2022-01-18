#include <Wire.h>
#include <LiquidCrystal.h>
//#include <OneWire.h>                  // Librería para usar el protocolo OneWire
//#include <DallasTemperature.h>        // Librería para comunicarse con el sensor DS18B20

#define DS3231_DIR 0x68

#define RS 12
#define EN 13
#define D4 14
#define D5 15
#define D6 16
#define D7 17

#define DS18B20 11

#define LAMP 10
#define BOMBA 8
#define VENTX 7
#define VALVULA 4
#define BUZZER 3

#define LED_B 5
#define LED_R 6
#define LED_A 9

byte edo_CTV;
byte semana_CTV;
byte dia_CTV;
byte datoGEN [20];

byte fotoperiodo;
byte tHr_bomba;
bool edo_BOMBA;
byte tMin_bomba;
byte tMin_vent;
bool edo_VENT;

byte vled_Blanco;
byte vled_Rojo;
byte vled_Azul;
bool edo_LUM;

byte temperatura;
byte humedad;

byte segundo, minuto, hora, d_sem, dia, mes, ano, ctrl;

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

void setup() {
  
  lcd.begin(20, 4);
  Serial.begin(9600);   // Configurar la comunicacion a 9600 baudios
  Wire.begin();         // Preparar la librería Wire (I2C)

  pinMode(LAMP, OUTPUT);
  pinMode(BOMBA, OUTPUT);
  pinMode(VENTX, OUTPUT);
  pinMode(VALVULA, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  
  pinMode(LED_B, OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(LED_A, OUTPUT);

  digitalWrite(LAMP, LOW);
  digitalWrite(BOMBA, LOW);
  digitalWrite(VENTX, LOW);
  digitalWrite(VALVULA, LOW);
  digitalWrite(BUZZER, LOW);
  
  analogWrite(LED_B, 0);
  analogWrite(LED_R, 0);
  analogWrite(LED_A, 0);

  segundo = 35;
  minuto = 20;
  hora = 4;
  d_sem = 5;
  dia = 21;
  mes = 5;
  ano = 36;

  vled_Blanco = 0;
  vled_Rojo = 0;
  vled_Azul = 0;
  edo_LUM = 0;

  fotoperiodo = 0;
  tMin_vent = 0;
  edo_VENT = 0;
  tHr_bomba = 0;
  tMin_bomba = 0;
  edo_BOMBA = 0;

  temperatura = 23;
  humedad = 86;
  
  edo_CTV = 'x';
  write_ds1307();

  escribe_LCD();
  
}

void loop() 
{
  recibe_info();

  if (edo_CTV == 'D')
  {
    delay(1000); 
    if (read_ds1307() == 1) 
    {
    escribe_LCD();
    //print_time();
    } 
    else 
    {
    Serial.println("Error 1: RTC No disponible");
    }
  }
  else
  {
    //Serial.println("Cultivo desactivado");
    escribe_LCD();
    delay(1000);
  }
  
}

void recibe_info()
{
  if (Serial.available()) 
  { 
    Serial.readBytes(datoGEN, 22);
    if (datoGEN[0] == 'z' && datoGEN[11] == '-' && datoGEN[19] == 'z')
      {
        segundo = datoGEN[1] - '0';
        minuto = datoGEN[2] - '0';
        hora = datoGEN[3] - '0';
        d_sem = datoGEN[4] - '0';
        dia = datoGEN[5] - '0';
        mes = datoGEN[6] - '0';
        ano = datoGEN[7] - '0';
        write_ds1307();

        vled_Blanco = datoGEN[8] - '0';
        vled_Rojo = datoGEN[9] - '0';
        vled_Azul = datoGEN[10] - '0';
        
        fotoperiodo = datoGEN[12] - '0';
        tMin_vent = datoGEN[13] - '0';
        tHr_bomba = datoGEN[14] - '0';
        tMin_bomba = datoGEN[15] - '0';

        edo_CTV = datoGEN[18];
        escribe_LCD();
        if (edo_CTV == 'D')
        {
          digitalWrite(BUZZER, HIGH);
          delay(30);
          digitalWrite(BUZZER, LOW);
          delay(30);
          digitalWrite(BUZZER, HIGH);
          delay(30);
          digitalWrite(BUZZER, LOW);
          delay(30);
          digitalWrite(BUZZER, HIGH);
          delay(30);
          digitalWrite(BUZZER, LOW);
        }
        else
        {
          digitalWrite(BUZZER, HIGH);
          delay(30);
          digitalWrite(BUZZER, LOW); 
        }     
      }
  }
}
// ==========================================================================================================
// ==========================================================================================================
void escribe_LCD()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  if (edo_CTV == 'D')
  {
  if (fotoperiodo <= 9)
  {
    lcd.print("0");
    lcd.print(fotoperiodo);
  }
  else
  {
    lcd.print(fotoperiodo);
  }
  lcd.print(" hrs");
  lcd.setCursor(8, 0);
  if (hora <= 9) 
  {
    lcd.print("0");
    lcd.print(hora);
  }
  else
  {
    lcd.print(hora);
  }
  lcd.print(":");
  if (minuto <= 9) 
  {
    lcd.print("0");
    lcd.print(minuto);
  }
  else
  {
    lcd.print(minuto);
  }
  lcd.setCursor(15, 0);
  if (semana_CTV <= 9)
  {
    lcd.print("0");
    lcd.print(semana_CTV);
  }
  else
  {
    lcd.print(semana_CTV);
  }
  lcd.print("/");
  lcd.print("0");
  lcd.print(dia_CTV);
  }
  else
  {
    lcd.print("Cultivo Desactivado");  
  }
  
  lcd.setCursor(0,1);
  if (edo_LUM == 1)
  {
    lcd.print("*");
  }
  else
  {
    lcd.print("-");
  }
  lcd.print(" B:");
  if (vled_Blanco <= 1){ lcd.print("  ");}
  else if (vled_Blanco < 20){ lcd.print(" ");}
  lcd.print(map(vled_Blanco, 0, 20, 0, 100)); 
  lcd.print(" % * ");
  lcd.setCursor(12,1);
  lcd.print("Tem:");
  if (edo_CTV == 'D')
  {
  lcd.print(temperatura);
  lcd.print((char)223);
  }
  
  lcd.setCursor(0,2);
  if (edo_LUM == 1)
  {
    lcd.print("*");
  }
  else
  {
    lcd.print("-");
  }
  lcd.print(" R:");
  if (vled_Rojo <= 1){ lcd.print("  ");}
  else if (vled_Rojo < 20){ lcd.print(" ");}
  lcd.print(map(vled_Rojo, 0, 20, 0, 100)); 
  lcd.print(" % * ");
  lcd.setCursor(12,2);
  lcd.print("Hum:");
  if (edo_CTV == 'D')
  {
  lcd.print(humedad);
  lcd.print("%");
  }
  
  lcd.setCursor(0,3);
    if (edo_LUM == 1)
  {
    lcd.print("*");
  }
  else
  {
    lcd.print("-");
  }
  lcd.print(" A:");
  if (vled_Azul <= 1){ lcd.print("  ");}
  else if (vled_Azul < 20){ lcd.print(" ");}
  lcd.print(map(vled_Azul, 0, 20, 0, 100)); 
  lcd.print(" % V:- B:+");
  
  
}
// ==========================================================================================================
// ==========================================================================================================
bool write_ds1307()
{
  Wire.beginTransmission(DS3231_DIR);   // Inicia la transmision (0x68)
  Wire.write(0x00);                     // Escribir la dirección del registro segundero
  Wire.write(bin2bcd(segundo & 0x7F));  // Se activa el bit 7 del registro del segundero
  Wire.write(bin2bcd(minuto));
  Wire.write(bin2bcd(hora));
  Wire.write(bin2bcd(d_sem));
  Wire.write(bin2bcd(dia));
  Wire.write(bin2bcd(mes));
  Wire.write(bin2bcd(ano));
  
  if (Wire.endTransmission() != 0)      // Terminamos la escritura y verificamos si el DS1307 respondio
    return false;                       // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
    
  return true;                          // Retornar verdadero si se escribio con exito
}
// ==========================================================================================================
// ==========================================================================================================
bool read_ds1307()
{ 
  Wire.beginTransmission(DS3231_DIR);   // Iniciamos la transmision
  Wire.write(0x00);                     // Escribimos la dirección del registro del segundero
  if (Wire.endTransmission() != 0)      // Terminamos la escritura y verificamos si el DS1307 respondio
    return false;                       // Si la escritura se llevo a cabo el metodo endTransmission retorna 0
  Wire.requestFrom(DS3231_DIR, 8);      // Si el DS1307 esta presente, comenzar la lectura de 8 byte
  segundo = bcd2bin(Wire.read());       // Recibimos el byte del registro 0x00 y lo convertimos a binario
  minuto = bcd2bin(Wire.read());        // Continuamos recibiendo cada uno de los registros
  hora = bcd2bin(Wire.read());
  d_sem = bcd2bin(Wire.read());
  dia = bcd2bin(Wire.read());
  mes = bcd2bin(Wire.read());
  ano = bcd2bin(Wire.read());
  ctrl = Wire.read();                   // Recibir los datos del registro de control en la dirección 0x07
  
  return true;                          // Operacion satisfactoria, retornamos verdadero
}
// ==========================================================================================================
// ==========================================================================================================
uint8_t bcd2bin(uint8_t bcd)
{ 
  return (bcd / 16 * 10) + (bcd % 16);  // Convertir decenas y luego unidades a un numero binario
}

uint8_t bin2bcd(uint8_t bin)
{
  return (bin / 10 * 16) + (bin % 10);
}
// ==========================================================================================================
// ==========================================================================================================
void act_salidas()
{
  if (fotoperiodo < hora)
  {
    digitalWrite(LAMP,HIGH);
    analogWrite(LED_B, map(vled_Blanco, 0, 20, 0, 255));
    analogWrite(LED_R, map(vled_Rojo, 0, 20, 0, 255));
    analogWrite(LED_A, map(vled_Azul, 0, 20, 0, 255));
    //edo_LUM = 1;
  }
  else 
  {
    digitalWrite(LAMP,LOW);
    analogWrite(LED_B, 0);
    analogWrite(LED_R, 0);
    analogWrite(LED_A, 0);
    //edo_LUM = 0;
  }
  if (tMin_vent < minuto)
  {
    digitalWrite(VENTX,HIGH);
    //edo_VENT = 1;
  }
  else 
  {
    digitalWrite(VENTX,LOW);
    //edo_VENT = 0;
  }
  if (tHr_bomba == hora && tMin_bomba < minuto)
  {
    digitalWrite(BOMBA,HIGH);
    //edo_BOMBA = 1;
  }
  else 
  {
    digitalWrite(BOMBA,LOW);
    //edo_BOMBA = 0;
  }
}
// ==========================================================================================================
// ==========================================================================================================
void print_time()
{
  Serial.print("Fecha: ");
  Serial.print(dia);
  Serial.print('/');
  Serial.print(mes);
  Serial.print('/');
  Serial.print(ano);

  Serial.print("  Hora: ");
  Serial.print(hora);
  Serial.print(':');
  Serial.print(minuto);
  Serial.print(':');
  Serial.print(segundo);

  Serial.println();
}
