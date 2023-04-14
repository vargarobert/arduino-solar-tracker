#define WIND_INTENSITY 11
#define RELAY_1 10
#define RELAY_2 9
#define RELAY_3 8
#define RELAY_4 7
#define WIND_ALARM 6

// set up loop
void setup()
{  
  pinMode(WIND_INTENSITY, OUTPUT);
  pinMode(WIND_ALARM, OUTPUT);
  pinMode(RELAY_1, OUTPUT);
  pinMode(RELAY_2, OUTPUT);
  pinMode(RELAY_3, OUTPUT);
  pinMode(RELAY_4, OUTPUT);
}

// main loop
void loop()
{
  windControl();
  sensorOrientationControl();

  delay(2000);
}

void windControl()
{
    int windSpeed = analogRead(A4);
    analogWrite(WIND_INTENSITY, windSpeed / 4);
    int windSpeedNormalised = (windSpeed * (5.0 / 1023.0)) * 10;
    if(windSpeedNormalised >= 25) {
      digitalWrite(WIND_ALARM, HIGH);
    } else {
      digitalWrite(WIND_ALARM, LOW);
    }
}

void sensorOrientationControl()
{
  int toleranceNormalised = 0; // set Tolerance to 0

  int sensorTop = analogRead(A0);    // set the top LDR input to analog pin 0
  int sensorBottom = analogRead(A1); // set the bottom LDR input to analog pin 1
  int sensorLeft = analogRead(A2);   // set the left LDR input to analog pin 2
  int sensorRight = analogRead(A3);  // set the right LDR input to analog pin 3

  int sensorTopDelta = sensorTop - sensorBottom;    // Compares the difference in top and bottom
  int sensorBottomDelta = sensorBottom - sensorTop; // Compares the difference in top and bottom
  int sensorLeftDelta = sensorLeft - sensorRight;   // Compares the difference in left and right
  int sensorRightDelta = sensorRight - sensorLeft;  // Compares the difference in left and right

  int tolerance = analogRead(A5); // Reads the variable resistor value to get Tolerance
  toleranceNormalised = (tolerance * (5.0 / 1023.0)) * 20; // sets Tolerance value and changes value between 1 and 100, making use of the analog voltage https://www.deviceplus.com/arduino/the-basics-of-arduino-reading-voltage

  if ((sensorTopDelta > 0) && (sensorTopDelta >= toleranceNormalised)) // checks to see if sensor test 1 is greater then or equal to the tolerance and that sensor test 1 is a positive number
  {
    digitalWrite(RELAY_1, HIGH);
    digitalWrite(RELAY_2, LOW);
  } else if ((sensorBottomDelta > 0) && (sensorBottomDelta >= toleranceNormalised)) // checks to see if sensor test 2 is greater then or equal to the tolerance and that sensor test 2 is a positive number
  {
    digitalWrite(RELAY_1, LOW);
    digitalWrite(RELAY_2, HIGH);
  } else {
    digitalWrite(RELAY_1, LOW);
    digitalWrite(RELAY_2, LOW); 
  }

  if ((sensorLeftDelta > 0) && (sensorLeftDelta >= toleranceNormalised)) // checks to see if sensor test 3 is greater then or equal to the tolerance and that sensor test 3 is a positive number
  {
    digitalWrite(RELAY_3, HIGH);
    digitalWrite(RELAY_4, LOW);
  } else if ((sensorRightDelta > 0) && (sensorRightDelta >= toleranceNormalised)) // checks to see if sensor test 4 is greater then or equal to the tolerance and that sensor test 4 is a positive number
  {
    digitalWrite(RELAY_3, LOW);
    digitalWrite(RELAY_4, HIGH);
  } else {
    digitalWrite(RELAY_3, LOW);
    digitalWrite(RELAY_4, LOW);
  }
}
