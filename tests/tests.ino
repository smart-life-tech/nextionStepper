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
void setup()
{
    Serial.begin(9600);
    myNex.begin(9600); // Begin the object with a baud rate of 9600
    pinMode(motorDirPin, OUTPUT);
    pinMode(motorStepPin, OUTPUT);
}

bool moveForward = false;
bool moveReverse = false;

void loop()
{
    btnForward = myNex.readNumber("b0.val");
    btnReverse = myNex.readNumber("b1.val");

    if (btnForward)
    {
        moveForward = true;
        moveReverse = false;
        digitalWrite(motorDirPin, HIGH);
    }
    else if (btnReverse)
    {
        moveReverse = true;
        moveForward = false;
        digitalWrite(motorDirPin, LOW);
    }

    if (moveForward || moveReverse)
    {
        if (moveForward)
        {
            digitalWrite(motorStepPin, HIGH);
            delayMicroseconds(500);
            digitalWrite(motorStepPin, LOW);
            delayMicroseconds(500);
        }

        if (moveReverse)
        {
            // Code to move the motor in reverse
            digitalWrite(motorStepPin, HIGH);
            delayMicroseconds(500);
            digitalWrite(motorStepPin, LOW);
            delayMicroseconds(500);
        }
        unsigned long currentMillis = millis();

        if (currentMillis - previousMillis >= interval)
        {
            previousMillis = currentMillis;
            Serial.println("Button pressed");
        }
    }
}
