#include <OneWire.h>
#include <DallasTemperature.h>
#include <ThingerESP32.h>

#define THINGER_SERIAL_DEBUG
#define USERNAME ""
#define DEVICE_ID ""
#define DEVICE_CREDENTIAL ""

#define SSID "troque por sua rede WiFi"
#define SSID_PASSWORD "troque por sua senha WiFi"

ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

#define ONE_WIRE_BUS 4

#define sensorUmid1 32
#define sensorUmid2 35
#define sensorUmid3 34

#define bomba1 13
#define bomba2 12
#define bomba3 14

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

// Variáveis dos sensores:
float tempC;
float umid1, umid2, umid3;

String statusBomba1, statusBomba2, statusBomba3;

void setup()
{
  // Inicializa porta serial a 115200 bits/s
  Serial.begin(115200);

  // Inicializa sensor DS18B20
  sensors.begin();

  // Configura pinos dos relés das bombas como OUTPUT
  pinMode(bomba1, OUTPUT);
  pinMode(bomba2, OUTPUT);
  pinMode(bomba3, OUTPUT);

  // Mantém bombas desativadas na inicialização
  digitalWrite(bomba1, HIGH);
  digitalWrite(bomba2, HIGH);
  digitalWrite(bomba3, HIGH);

}

void loop()
{ 
  leituraUmid(); 
  delay(500);
  leituraTemp();
  delay(500);
  enviarDados();
  delay(4000);
}

void enviarDados(){
  thing.add_wifi(SSID, SSID_PASSWORD);
  delay(2000);

  thing["temp"] >> outputValue(tempC);

  thing["umid1"] >> outputValue(umid1);
  thing["umid2"] >> outputValue(umid2);
  thing["umid3"] >> outputValue(umid3);

  thing["statusB1"] >> outputValue(statusBomba1);
  thing["statusB2"] >> outputValue(statusBomba2);
  thing["statusB3"] >> outputValue(statusBomba3);

  thing.handle();
}



void leituraTemp(){
  tempC = sensors.getTempCByIndex(0);

  if(tempC != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Temperatura: ");
    Serial.println(tempC);
   
  } 
  else
  {
    Serial.println("Error");
  }
}

void leituraUmid(){
umid1 = map(analogRead(sensorUmid1), 0, 4095, 100, 0);
delay(100);
Serial.print("Umidade Sensor 1: ");
Serial.print(umid1);
Serial.println(" %");
if(umid1 < 30) 
  {
    digitalWrite(bomba1, LOW);
    statusBomba1 = "ON";
    Serial.print("Bomba 1: ");
    Serial.println(statusBomba1);
    Serial.println("");
  }
  else 
  {
    digitalWrite(bomba1, HIGH);
    statusBomba1 = "OFF";
    Serial.print("Bomba 1: ");
    Serial.println(statusBomba1);
    Serial.println("");
  }

umid2 = map(analogRead(sensorUmid2), 0, 4095, 100, 0);
delay(100);
Serial.print("Umidade Sensor 2: ");
Serial.print(umid2);
Serial.println(" %");
if(umid2 < 30) 
  {
    digitalWrite(bomba2, LOW);
    statusBomba2 = "ON";
    Serial.print("Bomba 2: ");
    Serial.println(statusBomba2);
    Serial.println("");
  }
  else 
  {
    digitalWrite(bomba2, HIGH);
    statusBomba2 = "OFF";
    Serial.print("Bomba 2: ");
    Serial.println(statusBomba2);
    Serial.println("");
  }

umid3 = map(analogRead(sensorUmid3), 0, 4095, 100, 0);
delay(100);
Serial.print("Umidade Sensor 3: ");
Serial.print(umid3);
Serial.println(" %");
if(umid3 < 30) 
  {
    digitalWrite(bomba3, LOW);
    statusBomba3 = "ON";
    Serial.print("Bomba 3: ");
    Serial.println(statusBomba3);
    Serial.println("");
  }
  else 
  {
    digitalWrite(bomba3, HIGH);
    statusBomba3 = "OFF";
    Serial.print("Bomba 3: ");
    Serial.println(statusBomba3);
    Serial.println("");
  }
}




