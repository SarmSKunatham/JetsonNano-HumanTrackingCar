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


    // Initialize motor driver
    // Motor driver3
    digitalWrite(INA3, LOW);
    digitalWrite(INB3, LOW);
    analogWrite(PWM3, 0);

    // Motor driver4
    digitalWrite(INA4, LOW);
    digitalWrite(INB4, LOW);
    analogWrite(PWM4, 0);

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
                // set PWM for the speed of rotation of motor
                analogWrite(PWM3, 60);
                analogWrite(PWM4, 60);
                // Motor 3 clockwise direction
                digitalWrite(INA3, HIGH);
                digitalWrite(INB3, LOW);
                // Motor 4 Counterclockwise direction
                digitalWrite(INA4, LOW);
                digitalWrite(INB4, HIGH);


            }
            // If person is at the right
            else if (cmd == 1){
                // set PWM for the speed of rotation of motor
                analogWrite(PWM3, 60);
                analogWrite(PWM4, 60);
                // Motor 3&4 clockwise direction, so it'll move to the right
                digitalWrite(INA3, HIGH);
                digitalWrite(INB3, LOW);
                digitalWrite(INB4, LOW);
                digitalWrite(INA4, HIGH);

            }
            // If person is at the left
            else if(cmd == 2){
                // set PWM for the speed of rotation of motor
                analogWrite(PWM3, 60);
                analogWrite(PWM4, 60);
                // Motor 3&4 Counterclockwise direction, so it'll move to the left
                digitalWrite(INA4, LOW);
                digitalWrite(INB4, HIGH);
                digitalWrite(INA3, LOW);
                digitalWrite(INB3, HIGH);
            }
            
            else if(cmd == 3){
              // Brake
              digitalWrite(INA3, HIGH);
              digitalWrite(INB3, HIGH);
              digitalWrite(INA4, HIGH);
              digitalWrite(INB4, HIGH);
            }
            else if (cmd == 4){
              // Move backward
              // set PWM for the speed of rotation of motor
              analogWrite(PWM3, 40);
              analogWrite(PWM4, 40);
              // Motor 3 Counterclockwise direction
              digitalWrite(INA3, LOW);
              digitalWrite(INB3, HIGH);
              // Motor 4 clockwise direction
              digitalWrite(INA4, HIGH);
              digitalWrite(INB4, LOW);
            }
            else{
              digitalWrite(INA3, HIGH);
              digitalWrite(INB3, HIGH);
              digitalWrite(INA4, HIGH);
              digitalWrite(INB4, HIGH);
            }

        }
        
    }
    // If there is no serial sending to arduino
    else{

        digitalWrite(INA3, HIGH);
        digitalWrite(INB3, HIGH);
        digitalWrite(INA4, HIGH);
        digitalWrite(INB4, HIGH);
    }
  delay(100);
}
