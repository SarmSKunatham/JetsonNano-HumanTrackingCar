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
    // Setup PIN MODE
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

    // Initialize motor driver
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
                // led1 light
                digitalWrite(ledPin1, HIGH);
                digitalWrite(ledPin2, LOW);
                digitalWrite(ledPin3, LOW);
                // set PWM for the speed of rotation of motor
                analogWrite(PWM3, 100);
                analogWrite(PWM4, 100);
                // Motor 3 clockwise direction
                digitalWrite(INA3, HIGH);
                digitalWrite(INB3, LOW);
                // Motor 4 Counterclockwise direction
                digitalWrite(INA4, LOW);
                digitalWrite(INB4, HIGH);


            }
            // If person is at the right
            else if (cmd == 1){
                // led 2 light
                digitalWrite(ledPin2, HIGH);
                digitalWrite(ledPin2, LOW);
                digitalWrite(ledPin3, LOW);
                // set PWM for the speed of rotation of motor
                analogWrite(PWM3, 100);
                analogWrite(PWM4, 100);
                // Motor 3&4 clockwise direction, so it'll move to the right
                digitalWrite(INA3, HIGH);
                digitalWrite(INB3, LOW);
                digitalWrite(INB4, LOW);
                digitalWrite(INA4, HIGH);

            }
            // If person is at the left
            else if(cmd == 2){
                // led 3 light
                digitalWrite(ledPin3, HIGH);
                digitalWrite(ledPin1, LOW);
                digitalWrite(ledPin2, LOW);
                // set PWM for the speed of rotation of motor
                analogWrite(PWM3, 100);
                analogWrite(PWM4, 100);
                // Motor 3&4 Counterclockwise direction, so it'll move to the left
                digitalWrite(INA4, LOW);
                digitalWrite(INB4, HIGH);
                digitalWrite(INA3, LOW);
                digitalWrite(INB3, HIGH);

            }
        }
        
    }
    // If there is no serial sending to arduino
    else{
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, LOW);
        digitalWrite(INA3, HIGH);
        digitalWrite(INB3, HIGH);
        digitalWrite(INA4, HIGH);
        digitalWrite(INB4, HIGH);
    }
  delay(300);
}
