//transmitter connected throught the audrino uno and lora ra02 
//sensor - dht11,temperature sensor,lora ra02

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

#define DHTPIN A5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

//LoRa
#define ss 10
#define rst 9
#define dio0 2

String LoRaMessage = "";
int counter = 0;
//Motor Pump
int temppin = A2;
const int relayPinM = 4;
const int relayPinNPK = 5;

//NPK
int sensorValue = 0;
int n = 0;        
int p = 0;        
int k = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(relayPinM, OUTPUT);
  pinMode(relayPinNPK, OUTPUT);

  Serial.begin(9600);
  dht.begin();

  while (!Serial);
  Serial.println("LoRa Sender");
  LoRa.setPins(ss, rst, dio0);
    if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    delay(100);
    while (1);
  }
}


void loop() {
  // put your main code here, to run repeatedly:
  
  // MOISTURE
  float moisture = analogRead(A3);
  Serial.println("* SOIL PARAMETERS *");
  Serial.print("Moisture : ");
  Serial.println(moisture);

  // TEMPERATURE
  float tempr = analogRead(A2);
  float temperature = (tempr*50)/1023;
  Serial.print("Temperature : ");
  Serial.println(temperature);

  // NPK
  sensorValue = analogRead(A0)/2;    
   
  if(sensorValue>300)
  {
    n=sensorValue%20;
    p=sensorValue%40+2;
    k=sensorValue%30+7;
  }
  else
  {
    n=0;
    p=0;
    k=0;
  }
  Serial.print("Nitrogen: ");
  Serial.print(n);
  Serial.print(" mg/kg");
  Serial.println();
  Serial.print("Phosphorous: ");
  Serial.print(p);
  Serial.print(" mg/kg");
  Serial.println();
  Serial.print("Potassium: ");
  Serial.print(k);
  Serial.print(" mg/kg");
  Serial.println();

  Serial.println("");

  // HUMIDITY DHT11
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  float f=0;

  Serial.println("* FIELD PARAMETERS *");
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" g/m-3");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" ℃ ");


  Serial.println("");


  // water relay control
  int wpump;
  int nwpump;
  Serial.println("* PUMP STATUS *");
  if(moisture > 750){
    if(n < 18 || p < 18 || k < 18){
    digitalWrite(relayPinNPK, HIGH);
    nwpump = 1;
    wpump = 0;
    Serial.println("Water Pump : OFF");
    Serial.println("Nutrient Water Pump : ON");
    }else{
    digitalWrite(relayPinNPK, LOW);
    nwpump = 0;
    wpump = 1;
    digitalWrite(relayPinM, HIGH);
    Serial.println("Water Pump : ON");
    Serial.println("Nutrient Water Pump : OFF");
    }
    
    
  }else{
    digitalWrite(relayPinM, LOW);
    nwpump = 0;
    wpump = 0;
    Serial.println("Water Pump : OFF");
    Serial.println("Nutrient Water Pump : OFF");
    
  }
  /*
  Serial.print("Water Pump : ");
  Serial.println(wpump);
  Serial.print("Nutrient Water Pump : ");
  Serial.println(nwpump);*/

  Serial.print("Sending packet: ");
  Serial.println(counter);

  Serial.println("");
  Serial.println("");

  //LoRa
  LoRaMessage = String(counter) + "~" +
   String(moisture) + "!" + String(temperature) + "@" +
   String(n) + "#" + String(p) + "$" + String(k) + "%" + 
   String(h) + "^" + String(t) + "&" + String(f) + "-" + 
   String(wpump) + "*" + String(nwpump);
  
   // send packet
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  counter++;
  delay(5000);
}
