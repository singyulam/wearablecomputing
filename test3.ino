/*2017/03/22
 * SingYu Lam
 * Test for accelerometer using code from http://www.arduino.cc/en/Tutorial/ADXL3xx
 */

const int xPin = A0;       //x-axis input
const int yPin = A1;       //y-axis input
const int zPin = A2;       //z-axis input

void setup() {
  // initialize the serial communications:
  Serial.begin(9600);
}

void loop() {
  // print the sensor values:
  Serial.print("x: ");
  Serial.print(analogRead(xPin));
  // print a tab between values:   
  Serial.print("\t");
  Serial.print("y: ");
  Serial.print(analogRead(yPin));
  // print a tab between values:
  Serial.print("\t");
  Serial.print("z: ");
  Serial.print(analogRead(zPin));
  Serial.println();
  // delay before next reading:
  delay(100);
}
