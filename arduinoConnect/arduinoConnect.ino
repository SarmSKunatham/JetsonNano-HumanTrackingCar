// Connect to JetsonNano

#include <Servo.h>
#include "configuration.h"
#include <ArduinoJson.h>

StaticJsonDocument<200> doc;

void setup()
{
    // Initialize serial port
    Serial.begin(115200); 
    while (!Serial) continue;
    // Motor driver3
    pinMode(INA3, OUTPUT);
    pinMode(INB3, OUTPUT);
    pinMode(PWM3, OUTPUT);
    // Motor driver4
    pinMode(INA4, OUTPUT);
    pinMode(INB4, OUTPUT);
    pinMode(PWM4, OUTPUT);
    // Set pinmode to write command signal to LED.
    pinMode(ledPin1, OUTPUT);
    pinMode(ledPin2, OUTPUT);
    pinMode(ledPin3, OUTPUT);
    pinMode(ledPin4, OUTPUT);

    // Motor driver3
    digitalWrite(INA3, LOW);
    digitalWrite(INB3, LOW);
    analogWrite(PWM3, 0);

    // Motor driver4
    digitalWrite(INA4, LOW);
    digitalWrite(INB4, LOW);
    analogWrite(PWM4, 0);

    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
}

void loop()
{
    // Check if there is data in serial buffer
    if (Serial.available())
    {
        // Deserialize the JSON document
        DeserializationError error = deserializeJson(doc, Serial);
        

        // Action if parsing succeeds.
        if (!error)
        {
            int cmd = doc["command"];

            // If person is in center range
            if (cmd == 0){
                digitalWrite(ledPin1, HIGH);
                analogWrite(PWM3, 100);
                analogWrite(PWM4, 100);
                digitalWrite(INA3, HIGH);
                digitalWrite(INB3, LOW);
                digitalWrite(INA4, LOW);
                digitalWrite(INB4, HIGH);


            }
            // If person is at the right
            else if (cmd == 1){
                digitalWrite(ledPin2, HIGH);
                digitalWrite(ledPin2, LOW);
                digitalWrite(ledPin3, LOW);
                analogWrite(PWM3, 100);
                analogWrite(PWM4, 100);
                digitalWrite(INA3, HIGH);
                digitalWrite(INB3, LOW);
                digitalWrite(INB4, LOW);
                digitalWrite(INA4, HIGH);

            }
            // If person is at the left
            else if(cmd == 2){
                digitalWrite(ledPin3, HIGH);
                digitalWrite(ledPin1, LOW);
                digitalWrite(ledPin2, LOW);
                analogWrite(PWM3, 100);
                analogWrite(PWM4, 100);
                digitalWrite(INB4, HIGH);
                digitalWrite(INA4, LOW);
                digitalWrite(INA3, LOW);
                digitalWrite(INB3, HIGH);

            }
            else if(cmd == 3) {
                digitalWrite(ledPin1, LOW);
                digitalWrite(ledPin2, LOW);
                digitalWrite(ledPin3, LOW);
                digitalWrite(INA3, HIGH);
                digitalWrite(INB3, HIGH);
                digitalWrite(INA4, HIGH);
                digitalWrite(INB4, HIGH);
            }

        }
        
    }
    else{
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        digitalWrite(INA3, HIGH);
        digitalWrite(INB3, HIGH);
        digitalWrite(INA4, HIGH);
        digitalWrite(INB4, HIGH);
    }
       
}
