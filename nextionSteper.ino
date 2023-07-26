#include <AccelStepper.h>
// #include <EasyNextionLibrary.h>
#include "Nextion.h" //https://github.com/itead/ITEADLIB_Arduino_Nextion.git
// Define the motor control pins (you might need to adjust these)
#define motorStepPin 2
#define motorDirPin 3
bool btnForward, btnReverse = false;
// Define the Nextion objects
NexButton b0 = NexButton(0, 1, "btnForward");
NexButton b1 = NexButton(0, 2, "btnReverse");

/*
 * Declare a button object [page id:0,component id:1, component name: "b0"].
 */

char buffer[100] = {0};

void b0PopCallback(void *ptr)
{
    uint16_t len;
    uint16_t number;
    NexButton *btn = (NexButton *)ptr;
    dbSerialPrintln("b0PopCallback");
    dbSerialPrint("ptr=");
    dbSerialPrintln((uint32_t)ptr);
    memset(buffer, 0, sizeof(buffer));

    /* Get the text value of button component [the value is string type]. */
    btn->getText(buffer, sizeof(buffer));
    number = atoi(buffer);
    btnForward = number;
    //   number += 1;

    // memset(buffer, 0, sizeof(buffer));
    // itoa(number, buffer, 10);

    /* Set the text value of button component [the value is string type]. */
    //  btn->setText(buffer);
}

void b1PopCallback(void *ptr)
{
    uint16_t len;
    uint16_t number;
    NexButton *btn = (NexButton *)ptr;
    dbSerialPrintln("b0PopCallback");
    dbSerialPrint("ptr=");
    dbSerialPrintln((uint32_t)ptr);
    memset(buffer, 0, sizeof(buffer));

    /* Get the text value of button component [the value is string type]. */
    btn->getText(buffer, sizeof(buffer));
    number = atoi(buffer);
    btnReverse = number;
}

// Initialize the stepper motor object
AccelStepper stepper(AccelStepper::FULL4WIRE, motorStepPin, motorDirPin);

// Define motor speed and acceleration
const float maxSpeed = 1000.0; // Adjust this value based on your motor's capabilities
const float acceleration = 500.0;
/*
 * Register a button object to the touch event list.
 */
NexTouch *nex_listen_list[] =
    {
        &b0,
        &b1,
        NULL};
void setup()
{
    // Nextion setup
    nexInit();

    // Set up the stepper motor properties
    stepper.setMaxSpeed(maxSpeed);
    stepper.setAcceleration(acceleration);
}

void loop()
{
    // Update the Nextion touch events
    nexLoop(nex_listen_list);

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
