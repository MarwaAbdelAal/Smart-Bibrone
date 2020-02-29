#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2    // Data wire is plugged into port 2 on the Arduino
#define ledPin 7         // ledPin to arduino pin 7

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

const int buzzer = 9;    // Buzzer to arduino pin 9
float celsius = 0;
char degree = 176; //ASCI value of Degree

int state = 0;

void setup(void)
{
  pinMode(buzzer, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  Serial.begin(9600);  
  
  sensors.begin();

  digitalWrite(buzzer, HIGH);
  delay(500);
  digitalWrite(buzzer, LOW);
  delay(500);
}

void loop(void)
{
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
    
    sensors.requestTemperatures(); // Send the command to get temperatures
    celsius = sensors.getTempCByIndex(0);
    
    Serial.print("Temperature is: ");
    Serial.print(celsius);
    Serial.print(degree);
    Serial.println(" C ");
    // Check the right range of temperature
    if (celsius >= 30 && celsius <= 38)
    {
      Serial.println("The milk is ready");
      delay(1000);
    }
    else if(celsius > 38)
    {
      Serial.println("The milk is too hot, you should let it cool");
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      delay(500);
      digitalWrite(buzzer, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      delay(500);
    }
     else if(celsius < 30)
    {
      Serial.println("The milk is too cold, you should heat it");
      digitalWrite(buzzer, HIGH);
      delay(1500);
      digitalWrite(buzzer, LOW);
      delay(500);
    }
  
    state = 0;
    } 

}