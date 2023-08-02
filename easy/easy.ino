#include <AccelStepper.h>
#include <EasyNextionLibrary.h>
EasyNex myNex(Serial2);  // Create an object of EasyNex class with the name < myNex >

#define motorStepPin 2
#define motorDirPin 3
int btnForward, btnReverse = 0;
// Define the Nextion objects

/*
 * Declare a button object [page id:0,component id:1, component name: "b0"].
 */

char buffer[100] = { 0 };

// Initialize the stepper motor object
AccelStepper stepper(AccelStepper::FULL4WIRE, motorStepPin, motorDirPin);

// Define motor speed and acceleration
const float maxSpeed = 1000.0;  // Adjust this value based on your motor's capabilities
const float acceleration = 500.0;
/*
 * Register a button object to the touch event list.
 */

void setup() {
  Serial.begin(9600);
  myNex.begin(9600);  // Begin the object with a baud rate of 9600
  // Set up the stepper motor properties
  stepper.setMaxSpeed(maxSpeed);
  stepper.setAcceleration(acceleration);
}

void loop() {
   btnForward = myNex.readNumber("b0.val");
  Serial.println(btnForward);
  btnReverse = myNex.readNumber("b1.val");
  Serial.println(btnReverse);
  // Check for button presses
  if ((btnForward)) {
    Serial.println("forward button pressed");
    // Move the motor forward
    stepper.setSpeed(maxSpeed);
    stepper.runSpeed();
  }

  if ((btnReverse)) {
    Serial.println("reverse button pressed");
    // Move the motor in reverse
    stepper.setSpeed(-maxSpeed);
    stepper.runSpeed();
  }
  delay(1000);
}
