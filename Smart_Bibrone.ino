#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 3    // Data wire is plugged into port 3 on the Arduino

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

const int signal_Led = 12;    // signal_Led to arduino pin 12
const int green_Led = 8;     // green_Led to arduino pin 8
const int blue_Led = 9;     // blue_Led to arduino pin 9
const int red_Led = 10;    // red_Led to arduino pin 10

float celsius = 0;
char degree = 176; //ASCI value of Degree
int state = 0;

void setup(void)
{
  pinMode(signal_Led, OUTPUT);
  pinMode(green_Led, OUTPUT);
  pinMode(blue_Led, OUTPUT);
  pinMode(red_Led, OUTPUT);

  digitalWrite(signal_Led, LOW);
  digitalWrite(green_Led, LOW);
  digitalWrite(blue_Led, LOW);
  digitalWrite(red_Led, LOW);

  Serial.begin(9600);  
  sensors.begin();
}

void loop(void)
{
  if(Serial.available() > 0){    // Checks whether data is comming from the serial port
    state = Serial.read();      // Reads the data from the serial port
    }
    
  if (state == '0') {
    // Turn LEDs OFF
    digitalWrite(signal_Led, LOW);     
    digitalWrite(green_Led, LOW);
    digitalWrite(blue_Led, LOW);
    digitalWrite(red_Led, LOW);
    Serial.println("Smart bibron is OFF");
    state = 0;
    }
    
  else if (state == '1') {
    digitalWrite(signal_Led, HIGH);

    sensors.requestTemperatures(); // Send the command to get temperatures
    celsius = sensors.getTempCByIndex(0);
    
    Serial.print("Temperature is: ");
    Serial.print(celsius);
    Serial.print(degree);
    Serial.println(" C ");
    delay(1000);

    // Check the right range of temperature
    if (celsius >= 30 && celsius <= 38)
    {
      Serial.println("The milk is ready");
      digitalWrite(green_Led, HIGH);
      delay(1000);
    }
    else if(celsius > 38)
    {
      Serial.println("The milk is too hot, you should cool it");
      digitalWrite(red_Led, HIGH);
      delay(1000);
    }
     else if(celsius < 30)
    {
      Serial.println("The milk is too cold, you should heat it");
      digitalWrite(blue_Led, HIGH);
      delay(1000);
    }
  
    state = 0;
    } 

}