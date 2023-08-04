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

void loop()
{
    btnForward = myNex.readNumber("b0.val");
    btnReverse = myNex.readNumber("b1.val");
    if (btnForward)
    {
        right = true;
        digitalWrite(motorDirPin, HIGH);
    }
    else
    {
        right = false;
    }
    if (btnReverse)
    {
        left = true;
        digitalWrite(motorDirPin, LOW);
    }
    else
    {
        left = false;
    }
    if (right)
    {
        while (1)
        {
            unsigned long currentMillis = millis();
            // Check the digital pin every 1 second
            if (currentMillis - previousMillis >= interval)
            {
                previousMillis = currentMillis;

                // Check the state of the digital pin
                right = myNex.readNumber("b0.val");
                if (!right)
                {
                    Serial.println("Forward button not pressed");
                    right = false;
                    break;
                }
            }
            Serial.println("forward button pressed");
            unsigned long currentMillis = millis();
            // Check the digital pin every 1 second
            if (currentMillis - previousMillis >= interval)
            {
                previousMillis = currentMillis;

                // Check the state of the digital pin
                right = myNex.readNumber("b1.val");
                if (!left)
                {
                    Serial.println("reverse button not pressed");
                    left = false;
                    break;
                }
            }
            digitalWrite(motorStepPin, HIGH);
            delayMicroseconds(500);
            digitalWrite(motorStepPin, LOW);
            delayMicroseconds(500);
        }
    }
    if (left)
    {
        while (1)
        {
            Serial.println("forward button pressed");
            digitalWrite(motorStepPin, HIGH);
            delayMicroseconds(500);
            digitalWrite(motorStepPin, LOW);
            delayMicroseconds(500);
        }
        Serial.println("waiting for  button press");
    }
}
