#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2    // Data wire is plugged into port 2 on the Arduino
#define ledPin 7         // ledPin to arduino pin 7

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

float celsius = 0;
const int buzzer = 9;    // Buzzer to arduino pin 9
int state = 0;

void setup(void)
{
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);  
  // Serial.begin(38400); // Default communication rate of the Bluetooth module
  
  sensors.begin();
  
  tone(buzzer, 1000, 500);
  noTone(buzzer);
}

void loop(void)
{ 
  Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  Serial.println("DONE");
  
  celsius = sensors.getTempCByIndex(0);

  if(Serial.available() > 0){    // Checks whether data is comming from the serial port
    state = Serial.read();      // Reads the data from the serial port
    }
  if (state == '0') {
    digitalWrite(ledPin, LOW);     // Turn LED OFF
    Serial.println("LED: OFF");    // Send back, to the phone, the String "LED: ON"
    state = 0;
    }
  else if (state == '1') {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED: ON");
    state = 0;
    } 
  
  // Check if reading was successful
  if(celsius != DEVICE_DISCONNECTED_C) 
  {
    Serial.print("Temperature is: ");
    Serial.print(celsius);  
    Serial.println(" C ");
  } 
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
  
  // Check the right range of temperature
  if (celsius >= 30 && celsius <= 38)
  {
    Serial.println("The milk is ready");
  }
  else if(celsius > 38)
  {
    Serial.println("The milk is too hot, it needs to be cooled");
    tone(buzzer, 1000, 500);
    noTone(buzzer);
    delay(500);
    tone(buzzer, 1000, 500);
    noTone(buzzer);
    delay(500);
  }
   else if(celsius < 30)
  {
    Serial.println("The milk should be heated");
    tone(buzzer, 1000, 1500);
    noTone(buzzer);
    delay(500);
  }
}
