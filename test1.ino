/*2017/04/12
 * SingYu Lam
 * Test for accelerometer using code from http://www.arduino.cc/en/Tutorial/ADXL3xx
 */

const int xPin = A0;                 // x-axis input
const int yPin = A1;                 // y-axis input
const int zPin = A2;                 // z-axis input

int xReading = 0;
int yReading = 0;
int zReading = 0;

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
}

void loop() {
  
  xReading = analogRead(xPin);
  yReading = analogRead(yPin);
  zReading = analogRead(xPin);
  
  // print the sensor values:
  Serial.print("x: ");
  Serial.print(xReading);
  // print a tab between values:   
  Serial.print("\t");
  Serial.print("y: ");
  Serial.print(yReading);
  // print a tab between values:
  Serial.print("\t");
  Serial.print("z: ");
  Serial.print(analogRead(zReading));
  Serial.println();
  
  
  // delay before next reading:
  delay(10);
}
