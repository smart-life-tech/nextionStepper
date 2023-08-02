// Pin numbers
const int directionPin = 3;
const int stepPin = 2;
const int reversePin = 4;
const int forwardPin = 5;

// Variables to track button states and movement
bool forwardButtonPressed = false;
bool reverseButtonPressed = false;
bool forwardMovementDone = true;
bool reverseMovementDone = true;

// Other constants
const int NumSteps = 400; // Number of steps to move the motor
const int Speed = 1000;   // Speed at which the motor will "step" (shouldn't be less than 200)

void setup()
{
    Serial.begin(9600);
    pinMode(forwardPin, INPUT_PULLUP);
    pinMode(reversePin, INPUT_PULLUP);
    pinMode(directionPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    digitalWrite(directionPin, LOW);
    digitalWrite(stepPin, LOW);
}

void loop()
{
    digitalWrite(directionPin, HIGH);
    // Move in one direction
    for (int distance = 0; distance < NumSteps; distance++)
    {
        digitalWrite(stepPin, HIGH);
        delayMicroseconds(Speed);
        digitalWrite(stepPin, LOW);
        delayMicroseconds(Speed);
    }

    // Add a small delay to avoid excessive loop iterations
    delay(500);
}
