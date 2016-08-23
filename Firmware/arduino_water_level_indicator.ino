//Coded by MATHEW VARGHESE
//Note that the numbering of arduino pins are different from microcontroller pinout

int pin[11], i;
int d = 18;   // Replace '18' with the depth of the tank o be measured in centimeters
int trig = 2, echo = 3; //Attach Trig of ultrasonic sensor to pin 2 and Echo to pin 3


void setup()
{
 Serial.begin(9600); // Serial output is enabled at 9600 baud
  pin[1] = 13;
  pin[2] = 12;
  pin[3] = 11;
  pin[4] = 10;
  pin[5] =  9;
  pin[6] =  8;
  pin[7] =  7;
  pin[8] =  6;
  pin[9] =  5;
  pin[10] = 4;


  for (i = 1; i <= 10; i++)
    pinMode(pin[i], OUTPUT);
  
}

void loop()
{

   // Establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, in, cm;
  
   
   for (i = 1; i <= 10; i++) //Resetting the LEDs to off state
    digitalWrite(pin[i], LOW);
 
 
  // The PING is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(trig, OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(5);
  digitalWrite(trig, LOW);


  // The echo pin is used to read the signal from the PING: a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);
  in = microsecondsToInches(duration);// Convert the time into distance
  
  
  Serial.println(in);// To print the measured depth through the serial monitor
  
  
  for (i = 1; i <= 10; i++) //Loop is used to light up the LEDs to represent the measured level
    if (in < (i+1) * (d / 11.0))
      digitalWrite(pin[i], HIGH);

}
long microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second). This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PI...
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
