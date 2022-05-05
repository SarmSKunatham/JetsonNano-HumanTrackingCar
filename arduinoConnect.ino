// Connect to JetsonNano

#include <Servo.h>
#include "configuration.h"
#include <ArduinoJson.h>

StaticJsonDocument<200> doc;

void setup()
{
    // Initialize serial port
    Serial.begin(115200) while (!Serial) continue;
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
            int area = doc["area"];
            int angle_x = doc["angle_x"];
            int angle_y = doc["angle_y"];

            Serial.println("Area: ", area);
            Serial.println("Angle_x: ", angle_x);
            Serial.println("Angle_y: ", angle_y);
        }
    }
}
