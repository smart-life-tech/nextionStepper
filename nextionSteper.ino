#include <AccelStepper.h>
//#include <EasyNextionLibrary.h>
#include "Nextion.h"
// Define the motor control pins (you might need to adjust these)
#define motorStepPin 2
#define motorDirPin 3

// Define the Nextion objects
NexButton btnForward = NexButton(0, 1, "btnForward");
NexButton btnReverse = NexButton(0, 2, "btnReverse");

// Initialize the stepper motor object
AccelStepper stepper(AccelStepper::FULL4WIRE, motorStepPin, motorDirPin);

// Define motor speed and acceleration
const float maxSpeed = 1000.0; // Adjust this value based on your motor's capabilities
const float acceleration = 500.0;

void setup() {
  // Nextion setup
  nexInit();

  // Set up the stepper motor properties
  stepper.setMaxSpeed(maxSpeed);
  stepper.setAcceleration(acceleration);
}

void loop() {
  // Update the Nextion touch events
  nexLoop(nex_listen_list);

  // Check for button presses
  if (nexButtonPressed(btnForward)) {
    // Move the motor forward
    stepper.setSpeed(maxSpeed);
    stepper.runSpeed();
  }

  if (nexButtonPressed(btnReverse)) {
    // Move the motor in reverse
    stepper.setSpeed(-maxSpeed);
    stepper.runSpeed();
  }
}
