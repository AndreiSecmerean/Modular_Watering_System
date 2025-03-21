#include <LiquidCrystal.h>

//default values
#define maxLevel 10 //highest alower value for water in reservoir
#define minLevel 50 //lowest alowed value for water in reservoir
#define defaultSoilHumidity 50 //value of humidity at start up (optional at this time)
#define soilValueCompare 40

//Pin-out for ultrasoni distance sensor
const int trigPin = 4;
const int echoPin = 5;

//Pin-out for soil sensor
#define soilSensor A0
const int enableSoilSensor = 12;

//Pin-out for LCD
const int rs = 6, en = 7, d4 = 8, d5 = 9, d6 = 10, d7 = 11;

//Pin-out for Relays
const int pumpRelay = 2;
const int valve1 = 3;

//Flags
bool isWater = true;
bool needWatering = false;
  
//Initianting the LCD 
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(enableSoilSensor, OUTPUT);
  pinMode(pumpRelay, OUTPUT);
  pinMode(valve1, OUTPUT);
}

void loop()
{
    int waterLevel  = Distance();
    int soilLevel = ReadSoil();
    //int soilPercentage = (soilLevel / defaultSoilHumidity)*100;
    int soilPercentage = map(soilLevel, 0, 100, 0, 100);
    Serial.print(soilPercentage);

  DisplaySoilValue();
  DisplayWaterLevel();

  checkFlags(waterLevel, soilPercentage);
  Serial.print("isWater: ");
  Serial.print(isWater);
  Serial.print("\n");
  Serial.print("needWatering: ");
  Serial.print(needWatering);
  Serial.print("\n");

  if(isWater){
      if(needWatering){
          digitalWrite(pumpRelay, HIGH);
          digitalWrite(valve1, HIGH);
          Serial.print("Pump and valve open, Watering!\n");
      }else{
        digitalWrite(pumpRelay, LOW);
        digitalWrite(valve1, LOW);
        Serial.print("Pump and valve closed! Soil moisture is suficient.");
      }
      
  }else{
    digitalWrite(pumpRelay, LOW);
    digitalWrite(valve1, LOW);
    Serial.print("Pump and valve closed! Water Low!");
  }
  

  delay(3000);
  PurgeLCD();
}

int Distance(){  
  unsigned int distance;
  int duration;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration*0.0343)/2;
   
    return  distance; //raw data
}

int ReadSoil(){
      int sensorValue = 0;
      digitalWrite(enableSoilSensor, LOW);
      delayMicroseconds(50);

      digitalWrite(enableSoilSensor, HIGH);
      delay(50);
      sensorValue = analogRead(soilSensor);
      digitalWrite(enableSoilSensor, LOW);
      int outputValue = map(sensorValue, 0, 1023, 255, 0);

      //return sensorValue; //raw sensor value
      return outputValue;  //maped sensor value
}

void checkFlags(int waterLevel, int soilLevel){
  //checking water level in water tank
    if(waterLevel >= minLevel){
      isWater = false;
    } else{
      isWater = true;
    }

  //checking water content in soil
    if(soilLevel < soilValueCompare - 0.01*soilValueCompare){
      needWatering = true;
    } else{
      needWatering = false;
    }


  
}

void DisplaySoilValue(){
    int soilValue = ReadSoil();
  lcd.setCursor(0,1);
  lcd.print("Soil: ");
  //int percentage = (soilValue / defaultSoilHumidity)*100;
  int percentage = map(soilValue, 0, 100, 0, 100);
  lcd.print(percentage);

  Serial.print("Soil Humidity: ");
  Serial.print(soilValue);
  Serial.print("\n");
}

void DisplayWaterLevel(){
  int distance = Distance();
  lcd.setCursor(0, 0);
  lcd.print("WaterLevel: ");
  lcd.setCursor(11, 0);
  lcd.print(distance);
  lcd.print("%");

  Serial.print("Water Level: ");
  Serial.print(distance);
  Serial.print("%\n");
}

void PurgeLCD(){
  lcd.setCursor(11, 0);
  lcd.print("     ");
  lcd.setCursor(6, 1);
  lcd.print("            ");
}