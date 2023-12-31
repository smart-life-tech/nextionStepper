#include <Arduino.h>
#include <EasyNextionLibrary.h>

EasyNex myNex(Serial2); // Use the correct Serial port and baud rate

// Define motor control pins
const int brakePin = 5;
const int dir = 2;
const int pwmPin = 4;
const int fgPin = 3; // Feedback signal pin

bool moveForward = false;
bool moveReverse = false;
int pwmValue = 0;

void setup()
{
    pinMode(brakePin, OUTPUT);
    pinMode(dir, OUTPUT);
    pinMode(pwmPin, OUTPUT);
    pinMode(fgPin, INPUT);
    analogWrite(pwmPin, 0);
    myNex.begin(9600); // Begin the object with a baud rate of 9600
    Serial.begin(9600);
}

void loop()
{
    delay(600);
    int btnForward = myNex.readNumber("b0.val");
    int btnReverse = myNex.readNumber("b1.val");
    Serial.println(String(btnForward) + String(btnReverse));
    pwmValue = 255; // myNex.readNumber("pwmSlider.val");
    int feedback = digitalRead(fgPin);
    updateStatus(feedback);
    if (btnForward)
    {
        moveForward = true;
        moveReverse = false;
        digitalWrite(dir, LOW);
    }
    else
    {
        moveForward = false;
    }

    if (btnReverse)
    {
        moveReverse = true;
        moveForward = false;

        digitalWrite(dir, HIGH);
    }
    else
    {
        moveReverse = false;
    }

    // Handle braking
    if (moveForward || moveReverse)
    {
        digitalWrite(brakePin, HIGH); // Release brake
        // Update motor speed
        analogWrite(pwmPin, pwmValue);
    }
    else
    {
        digitalWrite(brakePin, LOW); // Apply brake
        // Update motor speed
        analogWrite(pwmPin, 0);
        digitalWrite(pwmPin,LOW);
    }
}
void updateStatus(int feedback)
{
    char statusMsg[50];
    snprintf(statusMsg, sizeof(statusMsg), "Feedback: %s", feedback ? "Active" : "Inactive");
    Serial.println(statusMsg);
}