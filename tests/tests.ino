#include <EasyNextionLibrary.h>
EasyNex myNex(Serial2); // Create an object of EasyNex class with the name < myNex >

#define motorDirPin 3
#define motorStepPin 4
#define motorEnablePin 5
int btnForward, btnReverse = 0;
// Define the Nextion objects

/*
   Declare a button object [page id:0,component id:1, component name: "b0"].
*/

char buffer[100] = {0};

// Initialize the stepper motor object

// Define motor speed and acceleration
const float maxSpeed = 4000.0; // Adjust this value based on your motor's capabilities
const float acceleration = 3000.0;
/*
   Register a button object to the touch event list.
*/

void setup()
{
    Serial.begin(9600);
    myNex.begin(9600); // Begin the object with a baud rate of 9600
    // Set up the stepper motor properties
    //stepper.setMaxSpeed(maxSpeed);
    //stepper.setAcceleration(acceleration);
    pinMode(motorDirPin, OUTPUT);
    pinMode(motorEnablePin, OUTPUT);
    pinMode(motorStepPin, OUTPUT);
    digitalWrite(motorEnablePin, HIGH);
    // pinMode(5, INPUT_PULLUP);
}

void loop()
{
    btnForward = myNex.readNumber("b0.val");
    // btnForward = digitalRead(4);
    // Serial.println(btnForward);
    btnReverse = myNex.readNumber("b1.val");
    // btnReverse = digitalRead(5);
    // Serial.println(btnReverse);
    if (!btnForward && !btnReverse)
    {
        digitalWrite(motorEnablePin, LOW);
    }
    // Check for button presses
    do
    // ((btnForward))
    {
        if (myNex.readNumber("b0.val"))
        {
            Serial.println("forward button pressed");
            // Move the motor forward
            digitalWrite(motorDirPin, HIGH);
            digitalWrite(motorEnablePin, HIGH);
            // Move in one direction
            digitalWrite(motorStepPin, HIGH);
            delayMicroseconds(1000);
            digitalWrite(motorStepPin, LOW);
            delayMicroseconds(1000);
        }
    } while (myNex.readNumber("b0.val") == 1);

    do
    {
        if (myNex.readNumber("b1.val"))
        {
            Serial.println("reverse button pressed");
            digitalWrite(motorDirPin, LOW);
            digitalWrite(motorEnablePin, HIGH);
            digitalWrite(motorStepPin, HIGH);
            delayMicroseconds(5000);
            digitalWrite(motorStepPin, LOW);
            delayMicroseconds(5000);
        }
    } while (myNex.readNumber("b1.val") == 1);
    delay(1000);
}
