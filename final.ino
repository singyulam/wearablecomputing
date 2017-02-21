/*2017/02/15
SingYu Lam
GDES 3015 - Wearable Computing
---------------------------------------------
10 LEDs
---------------------------------------------
https://www.arduino.cc/en/Tutorial/Ping
I put all the ultrasonic distance code into a single function called ultrasoundPing so I can call it more easily in my main for loop
By calling ultrasoundPing at the beginning of every loop I no longer need to wait for an entire LED sequence to fire before the delay
changes. Instead, it is more responsive now and the delay can change within a sequence.
*/

//define constant variables
#define ledPin1 11
#define ledPin2 10
#define ledPin3 9
#define ledPin4 6
#define ledPin5 A0
#define ledPin6 A1
#define ledPin7 A2
#define ledPin8 A3
#define ledPin9 A4
#define ledPin10 A5

#define trigPin 12
#define echoPin 13

//ledDelay controls both the time the LED is on for as well as the time it is off
int ledDelay;

//array to store all led pins
int ledPins[] = {ledPin1, ledPin2, ledPin3, ledPin4, ledPin5, ledPin6, ledPin7, ledPin8, ledPin9, ledPin10};

boolean tooclose = false;

void setup() {
  Serial.begin (9600);
  
  //ultrasonic sensor pin mode
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //set pin modes for leds
  for (int i = 0; i < sizeof(ledPins); i++) {
    pinMode(ledPins[i], OUTPUT); 
  }
}

void loop() {
  //cycle through 0 to 9 to match with corresponding case statements
  for (int i = 0; i < 10; i++) {
    //gets ultrasound distance and maps it to ledDelay
    ultrasoundPing();
    delay(50);

    //debug check for which for loop
    Serial.print("i ");
    Serial.println(i);

    //if proximity is not less than tooclose, go through switch statements
    if (!tooclose) {
      switch (i) {
        case 0:
          //turn on and off again an LED based on ledDelay
          analogWrite(ledPin10,255);
          delay(ledDelay);
          analogWrite(ledPin10,0);
          delay(ledDelay);
          Serial.println("ledPin10");
          break;
        case 1:
          //turn on and off again an LED based on ledDelay
          analogWrite(ledPin9,255);
          delay(ledDelay);
          analogWrite(ledPin9,0);
          delay(ledDelay);
          Serial.println("ledPin9");
          break;
        case 2:
          //turn on and off again an LED based on ledDelay
          analogWrite(ledPin8,255);
          delay(ledDelay);
          analogWrite(ledPin8,0);
          delay(ledDelay);
          Serial.println("ledPin8");
          break;
        case 3:
          //turn on and off again an LED based on ledDelay
          analogWrite(ledPin7,255);
          delay(ledDelay);
          analogWrite(ledPin7,0);
          delay(ledDelay);
          Serial.println("ledPin7");
          break;
        case 4:
          //turn on and off again an LED based on ledDelay
          analogWrite(ledPin6,255);
          delay(ledDelay);
          analogWrite(ledPin6,0);
          delay(ledDelay);
          Serial.println("ledPin6");
          break;
        case 5:
          //turn on and off again an LED based on ledDelay
          analogWrite(ledPin5,255);
          delay(ledDelay);
          analogWrite(ledPin5,0);
          delay(ledDelay);
          Serial.println("ledPin5");
          break;
        case 6:
          //turn on and off again an LED based on ledDelay
          digitalWrite(ledPin4,HIGH);
          delay(ledDelay);
          digitalWrite(ledPin4,LOW);
          delay(ledDelay);
          Serial.println("ledPin4");
          break;
        case 7:
          //turn on and off again an LED based on ledDelay
          digitalWrite(ledPin3,HIGH);
          delay(ledDelay);
          digitalWrite(ledPin3,LOW);
          delay(ledDelay);
          Serial.println("ledPin3");
          break;
        case 8:
          //turn on and off again an LED based on ledDelay
          digitalWrite(ledPin2,HIGH);
          delay(ledDelay);
          digitalWrite(ledPin2,LOW);
          delay(ledDelay);
          Serial.println("ledPin2");
          break;
        case 9:
          //turn on and off again an LED based on ledDelay
          digitalWrite(ledPin1,HIGH);
          delay(ledDelay);
          digitalWrite(ledPin1,LOW);
          delay(ledDelay);
          Serial.println("ledPin1");
          break;
      }
    } else {
      //turn all LEDs on and off when tooclose is true
      digitalWrite(ledPin1,HIGH);
      digitalWrite(ledPin2,HIGH);
      digitalWrite(ledPin3,HIGH);
      digitalWrite(ledPin4,HIGH);
      analogWrite(ledPin5,255);
      analogWrite(ledPin6,255);
      analogWrite(ledPin7,255);
      analogWrite(ledPin8,255);
      analogWrite(ledPin9,255);
      analogWrite(ledPin10,255);
      delay(100);
      digitalWrite(ledPin1,LOW);
      digitalWrite(ledPin2,LOW);
      digitalWrite(ledPin3,LOW);
      digitalWrite(ledPin4,LOW);
      analogWrite(ledPin5,0);
      analogWrite(ledPin6,0);
      analogWrite(ledPin7,0);
      analogWrite(ledPin8,0);
      analogWrite(ledPin9,0);
      analogWrite(ledPin10,0);
      delay(100);
    }
    
  }

}

long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}

void ultrasoundPing() {
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(echoPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);

  //debug check to monitor distance
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  //reset tooclose to false
  tooclose=false;
  
  //exceptions outside of intended range are caught and accounted for with an if statement
  if (cm < 45) {
    cm = 45;
    tooclose=true;
  } else if (cm > 300) {
    cm = 300;
  } else {
    //map cm values from 45 to 300 cm into a millisecond range from 5 to 300 millesconds
    ledDelay = map(cm, 45, 200, 5, 300);  
  }
  
  //debug check to see current LED delay
  Serial.print(ledDelay);
  Serial.print(" ms");
  Serial.println();

}
