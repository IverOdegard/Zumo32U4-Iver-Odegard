#include <Wire.h>
#include <Zumo32U4.h>

const uint16_t maxspeed =200;

Zumo32U4Buzzer buzzer;
Zumo32U4LineSensors lineSensors;
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;

Zumo32U4OLED display;

#define NUM_SENSORS 5
unsigned int lineSensorValues[NUM_SENSORS];

void calibrateSensors()
{
  display.clear();
  display.print(F("Press A"));
  display.gotoXY(0, 1);
  display.print(F("to calib"));
  buttonA.waitForButton();
  for (uint16_t i = 0; i < 300; i++)
  {
    motors.setSpeeds(-150,150);
    lineSensors.calibrate();
  } 
  motors.setSpeeds(0, 0);
}

void startDrive()
{
  display.clear();
  display.print(F("Press A"));
  display.gotoXY(0, 1);
  display.print(F("to drive"));
  buttonA.waitForButton();
}


void drive()
{
   int16_t position = lineSensors.readLine(lineSensorValues);
   int16_t error = position - 2000;

   if (error < 0)
   motors.setSpeeds(200+(error/10), 200);

   else
   motors.setSpeeds(200, 200-(error/10));
  
}

void setup() {
  // put your setup code here, to run once:
lineSensors.initFiveSensors();
calibrateSensors();
startDrive();
}

void loop() {
  // put your main code here, to run repeatedly:
drive();
  

}