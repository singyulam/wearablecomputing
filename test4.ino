/*2017/03/22
 * SingYu Lam
 * Test for accelerometer using code from http://www.arduino.cc/en/Tutorial/ADXL3xx
 * With smoothing https://www.arduino.cc/en/tutorial/smoothing
 */

const int xPin = A0;             // x-axis input
const int yPin = A1;             // y-axis input
const int zPin = A2;             // z-axis input

const int numReadings = 40;     
int readIndex = 0;               // the index of the current reading

int xReadings[numReadings];      // the readings from the analog input
int xTotal = 0;                  // the running total
int xAverage = 0;                // the average

int yReadings[numReadings];      // the readings from the analog input
int yTotal = 0;                  // the running total
int yAverage = 0;                // the average

int zReadings[numReadings];      // the readings from the analog input
int zTotal = 0;                  // the running total
int zAverage = 0;                // the average

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
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  
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
  Serial.print(zAverage);
  Serial.println();
  // delay before next reading:
  delay(100);
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
