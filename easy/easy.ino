#include <AccelStepper.h>
#include <EasyNextionLibrary.h>
EasyNex myNex(Serial1); // Create an object of EasyNex class with the name < myNex >
       
#define motorStepPin 2
#define motorDirPin 3
bool btnForward, btnReverse = false;
// Define the Nextion objects

/*
 * Declare a button object [page id:0,component id:1, component name: "b0"].
 */

char buffer[100] = {0};


// Initialize the stepper motor object
AccelStepper stepper(AccelStepper::FULL4WIRE, motorStepPin, motorDirPin);

// Define motor speed and acceleration
const float maxSpeed = 1000.0; // Adjust this value based on your motor's capabilities
const float acceleration = 500.0;
/*
 * Register a button object to the touch event list.
 */

void setup()
{
     myNex.begin(9600); // Begin the object with a baud rate of 9600
    // Set up the stepper motor properties
    stepper.setMaxSpeed(maxSpeed);
    stepper.setAcceleration(acceleration);
}

void loop()
{

    // Check for button presses
    if ((btnForward))
    {
        // Move the motor forward
        stepper.setSpeed(maxSpeed);
        stepper.runSpeed();
    }

    if ((btnReverse))
    {
        // Move the motor in reverse
        stepper.setSpeed(-maxSpeed);
        stepper.runSpeed();
    }
}
