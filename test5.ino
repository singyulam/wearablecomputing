/*2017/03/22
 * SingYu Lam
 * Test for accelerometer using code from http://www.arduino.cc/en/Tutorial/ADXL3xx
 * With smoothing https://www.arduino.cc/en/tutorial/smoothing
 * Introduced calibration and boolean for level or not level
 */

const int xPin = A0;             // x-axis input
const int yPin = A1;             // y-axis input
const int zPin = A2;             // z-axis input

const int numReadings = 40;     
int readIndex = 0;               // the index of the current reading

int xReadings[numReadings];      // the readings from the analog input
int xTotal = 0;                  // the running total
int xAverage = 0;                // the average
int xLevelReading = 0;           // stores the x input at rest
int xDifference = 0;             // difference between rest value and current value
boolean xLevel = true;           // track if the x axis is level

int yReadings[numReadings];      // the readings from the analog input
int yTotal = 0;                  // the running total
int yAverage = 0;                // the average
int yLevelReading = 0;           // stores the y input at rest
int yDifference = 0;             // difference between rest value and current value
boolean yLevel = true;           // track if the y axis is level

int zReadings[numReadings];      // the readings from the analog input
int zTotal = 0;                  // the running total
int zAverage = 0;                // the average
int zLevelReading = 0;             // stores the z input at rest
int zDifference = 0;           // difference between rest value and current value
boolean zLevel = true;           // track if the z axis is level

int currentTime = 0;             // current time in milliseconds
boolean calibrate = true;        // boolean for calibration period

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
  
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    xReadings[thisReading] = 0;
    yReadings[thisReading] = 0;
    zReadings[thisReading] = 0;
  }
}

void loop() {
  averageX();
  averageY();
  averageZ();

  // advance to the next position in the array:
  readIndex++;

  // loop read index back to 0
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  currentTime = millis();

  if (currentTime > 500 && calibrate) {
    calibrate = false;
    xLevelReading = xAverage;
    yLevelReading = yAverage;
    zLevelReading = zAverage;
  } 
  
   xDifference = xLevelReading - xAverage;
   xDifference = abs(xDifference);
   yDifference = yLevelReading - yAverage;
   yDifference = abs(yDifference);
   zDifference = zLevelReading - zAverage;
   zDifference = abs(zDifference);

   if (xDifference > 200) {
    xLevel = false; 
   } else {
    xLevel = true; 
   }
   if (yDifference > 200) {
    yLevel = false; 
   } else {
    yLevel = true; 
   }
   if (zDifference > 200) {
    zLevel = false; 
   } else {
    zLevel = true; 
   }

  Serial.print (xLevel);
  Serial.print("\t");
  Serial.print (yLevel);
  Serial.print("\t");
  Serial.print (zLevel);
  Serial.println();

  /*
  // print the sensor values:
  Serial.print("x: ");
  Serial.print(analogRead(xPin));
  // print a tab between values:   
  Serial.print("\t");
  Serial.print("y: ");
  Serial.print(yAverage);
  //Serial.print(analogRead(yPin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print("z: ");
  Serial.print(analogRead(zPin));
  Serial.println();
  */
  // delay before next reading:
  delay(10);
}


void averageX () {
  // read from the sensor:
  xReadings[readIndex] = analogRead(xPin);

  xTotal = 0;

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    xTotal += xReadings[thisReading];
  }

  // calculate the average:
  xAverage = xTotal/numReadings;
}

void averageY () {
    // read from the sensor:
  yReadings[readIndex] = analogRead(yPin);

  yTotal = 0;

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    yTotal += yReadings[thisReading];
  }

  
  // calculate the average:
  yAverage = yTotal/numReadings;
}


void averageZ () {
  // read from the sensor:
  zReadings[readIndex] = analogRead(zPin);

  zTotal = 0;

  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    zTotal += zReadings[thisReading];
  }

  // calculate the average:
  zAverage = zTotal/numReadings;
}
