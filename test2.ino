/*2017/04/12
 * SingYu Lam
 * Test for accelerometer using code from http://www.arduino.cc/en/Tutorial/ADXL3xx
 * With smoothing https://www.arduino.cc/en/tutorial/smoothing
 * Introduced calibration and boolean for level or not level
 * Moved smoothing into their own functions
 * Introduced inital calibration
 * Introduced continuous x calibration to detect motion (and stillness)
 */

const int xPin = A0;                 // x-axis input
const int yPin = A1;                 // y-axis input
const int zPin = A2;                 // z-axis input

const int numReadings = 10;     
int readIndex = 0;                   // the index of the current reading

int xReadings[numReadings];          // array to store the readings from the analog input
int xTotal = 0;                      // the running total
int xAverage = 0;                    // the average
int xLevelReading = 0;               // stores the x input at rest
int xLevelReadingNew = 0;            // stores temporary x input that might be the new level reading
int xDifference = 0;                 // difference between rest value and current value
boolean xLevel = true;               // track if the x axis is level

int yReadings[numReadings];          // array to store the readings from the analog input
int yTotal = 0;                      // the running total
int yAverage = 0;                    // the average
int yLevelReading = 0;               // stores the y input at rest
int yLevelReadingNew = 0;            // stores temporary y input that might be the new level reading
int yDifference = 0;                 // difference between rest value and current value
boolean yLevel = true;               // track if the y axis is level

int zReadings[numReadings];          // array to store the readings from the analog input
int zTotal = 0;                      // the running total
int zAverage = 0;                    // the average
int zLevelReading = 0;               // stores the z input at rest
int zLevelReadingNew = 0;            // stores temporary z input that might be the new level reading
int zDifference = 0;                 // difference between rest value and current value
boolean zLevel = true;               // track if the z axis is level

int currentTime = 0;                 // current time in milliseconds
int lastChangeTime = 0;              // last significant change stored to be compared to current time
boolean initialCalibrate = true;     // boolean for first calibration
boolean xCalibrate = false;          // boolean for x-axis calibration
int thresholdDifference = 100;       // amount the accelerometer needs to be off by to check for a new level reading

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

  //get averages from the three axes
  averageX();
  averageY();
  averageZ();

  // advance index to the next position in the array
  readIndex++;

  // loop read index back to 0
  if (readIndex >= numReadings) {
    readIndex = 0;
  }

  currentTime = millis();

  //this only runs once after the first half second
  if (currentTime > 500 && initialCalibrate) {
    
    //turn boolean off so it only runs once
    initialCalibrate = false;

    //assign level readings to the current average
    xLevelReading = xAverage;
    yLevelReading = yAverage;
    zLevelReading = zAverage;
  }

  //after calibration is over, this code continually checks if the accelerometer is level
  if (!initialCalibrate) {
    checkLevel();

    if (!xLevel && !xCalibrate) {
      xLevelReadingNew = xAverage;
      lastChangeTime = millis();
      xCalibrate = true;
    }
    if (xCalibrate && (currentTime-lastChangeTime>1000) && (xAverage-xLevelReadingNew < 100) ) {
      xLevelReading = xLevelReadingNew;
      xCalibrate = false;
    }
    if (xCalibrate && currentTime-lastChangeTime>1100) {
      xCalibrate = false;
    }
    
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
  Serial.print(xAverage);
  // print a tab between values:   
  Serial.print("\t");
  Serial.print("y: ");
  Serial.print(yAverage);
  //Serial.print(analogRead(yPin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print("z: ");
  Serial.print(analogRead(zAverage));
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

void checkLevel () {
  //get the absolute value of the difference
   xDifference = xLevelReading - xAverage;
   xDifference = abs(xDifference);
   yDifference = yLevelReading - yAverage;
   yDifference = abs(yDifference);
   zDifference = zLevelReading - zAverage;
   zDifference = abs(zDifference);

   //check difference against threshold level difference
   
   if (xDifference > thresholdDifference) {
    xLevel = false; 
   } else {
    xLevel = true; 
   }
   if (yDifference > thresholdDifference) {
    yLevel = false; 
   } else {
    yLevel = true; 
   }
   if (zDifference > thresholdDifference) {
    zLevel = false; 
   } else {
    zLevel = true; 
   }  
}
