#include <EasyNextionLibrary.h>
EasyNex myNex(Serial2); // Create an object of EasyNex class with the name < myNex >

#define motorDirPin 3
#define motorStepPin 4
#define motorEnablePin 5
int btnForward, btnReverse = 0;
// Define the Nextion objects
bool right, left = false;
// Define motor speed and acceleration
const float maxSpeed = 4000.0; // Adjust this value based on your motor's capabilities
const float acceleration = 3000.0;
unsigned long previousMillis = 0;
const unsigned long interval = 1000; // 1 second interval
unsigned long counts=0;
int moveForward = false;
int moveReverse = false;
void setup()
{
    Serial.begin(9600);
    myNex.begin(9600); // Begin the object with a baud rate of 9600
    pinMode(motorDirPin, OUTPUT);
    pinMode(motorStepPin, OUTPUT);
}



void loop()
{
    btnForward = myNex.readNumber("b0.val");
    btnReverse = myNex.readNumber("b1.val");
    Serial.println(String(btnForward) + String(btnReverse));
    if (btnForward)
    {
        moveForward = true;
        moveReverse = false;
        digitalWrite(motorDirPin, HIGH);
    }
    else
        moveForward == false;
    if (btnReverse)
    {
        moveReverse = true;
        moveForward = false;
        digitalWrite(motorDirPin, LOW);
    }
    else
        moveReverse == false;

    while (moveForward)
    {
        counts++;
        digitalWrite(motorStepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(motorStepPin, LOW);
        delayMicroseconds(500);
        if(counts>1000)break;
    }

    while (moveReverse)
    {counts++;
        // Code to move the motor in reverse
        digitalWrite(motorStepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(motorStepPin, LOW);
        delayMicroseconds(500);
         if(counts>1000)break;
    }
}
