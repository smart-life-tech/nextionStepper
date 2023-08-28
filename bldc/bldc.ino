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

    myNex.begin(9600); // Begin the object with a baud rate of 9600
}

void loop()
{
    int btnForward = myNex.readNumber("b0.val");
    int btnReverse = myNex.readNumber("b1.val");
    pwmValue = 255; // myNex.readNumber("pwmSlider.val");

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

    // Update motor speed
    analogWrite(pwmPin, pwmValue);

    // Handle braking
    if (moveForward || moveReverse)
    {
        digitalWrite(brakePin, LOW); // Release brake
    }
    else
    {
        digitalWrite(brakePin, HIGH); // Apply brake
    }
}
