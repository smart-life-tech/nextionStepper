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
    if (btnForward)
    {
        right = true;
        digitalWrite(motorDirPin, HIGH);
    }else{
        right=false;
    }
    if (btnReverse)
    {
        left = true;
        digitalWrite(motorDirPin, LOW);
    }else{
left=false;
    }
    if (right)
    {
        Serial.println("forward button pressed");
        digitalWrite(motorStepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(motorStepPin, LOW);
        delayMicroseconds(500);
    }
    if (left)
    {
        Serial.println("forward button pressed");
        digitalWrite(motorStepPin, HIGH);
        delayMicroseconds(500);
        digitalWrite(motorStepPin, LOW);
        delayMicroseconds(500);
    }
    Serial.println("waiting for  button press");
}
