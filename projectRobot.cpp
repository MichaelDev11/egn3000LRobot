int distance; //declaring variable for distance
double duration; //declating variable for duratrion the signal is out

int trigPin = 2; //establishing the trig pin of ultrasonic sensor
int echoPin = 3; //establishing the echo pin of ultrasonic sensor
int redLight = 4; //establishing the red led
int blueLight = 5; //establishing the blue led

int irSensor = 12; //establishing the ultrasonic sensor on the left of the robot
int irSensor_2 = 13; //establishing the ultrasonic sensor on the right of the robot

int in1 = 6; //right motor fwd
int in2 = 7; //right motor bwd
int in3 = 8; //left motor fwd
int in4 = 9; //left motor bwd
int enA = 10; //pwm
int enB = 11; //pwm

int speedcap = 180; //this is the max speed signal we want to be sent to the L298N
int speedfactor = 0.66; //this is the multiplier when we want the robot to drive a little slower

void setup() {
  pinMode(trigPin, OUTPUT); //establish trig pin as output, it emits sound
  pinMode(echoPin, INPUT); //establish echo pin as input, receives the reflected sound waves
  pinMode(irSensor, INPUT); //establish the left side IR sensor as input
  pinMode(irSensor_2, INPUT); //establish the right side IR sensor as input
  pinMode(redLight, OUTPUT); //establish red led as an output, emits red light
  pinMode(blueLight, OUTPUT); //establish blue led as an output, emits light
  pinMode(in1, OUTPUT); //establishing motor to L298N communication
  pinMode(in2, OUTPUT); //establishing motor to L298N communication
  pinMode(in3, OUTPUT); //establishing motor to L298N communication
  pinMode(in4, OUTPUT); //establishing motor to L298N communication
  pinMode(enA, OUTPUT); //establishing the PWM connection between arduino and the L298N
  pinMode(enB, OUTPUT); //establishing the PWM connection between arduino and the L298N

  Serial.begin(9600); //establish to begin serial communication
}

void loop() {
  //References for usage of ultrasonic sensor were 
  //found here: https://create.arduino.cc/projecthub/abdularbi17/ultrasonic-sensor-hc-sr04-with-arduino-tutorial-327ff6 by Arbi Abdul Jabbaar
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  
  //Section of code regarding line following and motor movements
  //Reference regarding IR sensor use was found here: shorturl.at/ovQSU by Debashis Das
  if (digitalRead(irSensor) == HIGH && digitalRead(irSensor_2) == HIGH) {   //evaluating the state of each IR sensor
    Serial.print("Motors should stop spinning here"); //print statement to state the robots action

    digitalWrite(in1, LOW); //motor 1 off
    digitalWrite(in2, LOW); //motor 1 off
    digitalWrite(in3, LOW); //motor 2 off
    digitalWrite(in4, LOW); //motor 2 off
    digitalWrite(enA, 0); //no PWM signal
    digitalWrite(enB, 0); //no PWM signal
    
    lightsReady(); //checks and runs a function if the lights are coming on or not

  } if (digitalRead(irSensor) == LOW && digitalRead(irSensor_2) == LOW) {   //evaluating the state of each IR sensor
    Serial.print("No line found, actuate motors to move to the line"); //print statement to state the robots action

    digitalWrite(in1, HIGH); //motor 1 on forward direction
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH); //motor 2 on forward direction
    digitalWrite(in4, LOW);
    digitalWrite(enA, speedcap); //send pwm for speed
    digitalWrite(enB, speedcap); //send pwm for speed
    
    lightsReady(); //checks and runs a function if the lights are coming on or not
  } if (digitalRead(irSensor) == HIGH && digitalRead(irSensor_2) == LOW) {   //evaluating the state of each IR sensor
    Serial.print("Line found on left side of the robot, so turn the robot, and navigate to the black line"); //print statement to state the robots action

    digitalWrite(in1, HIGH); //motor 1 on forward direction (right motor)
    digitalWrite(in2, LOW); 
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH); //motor 2 on reverse direction (left motor)
    digitalWrite(enA, speedcap); //send pwm for speed
    digitalWrite(enB, speedcap * speedfactor); //send pwm for speed
    
    lightsReady(); //checks and runs a function if the lights are coming on or not

  } if (digitalRead(irSensor) == LOW && digitalRead(irSensor_2) == LOW) {   //evaluating the state of each IR sensor
    Serial.print("Line found on the right side of the robot, turn right and navigate to the line"); //print statement to state the robots action

    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH); //motor 1 on reverse direction (right motor)
    digitalWrite(in3, HIGH); //motor 2 on forward direction (left motor)
    digitalWrite(in4, LOW); 
    digitalWrite(enA, speedcap * speedfactor); //send pwm for speed
    digitalWrite(enB, speedcap); //send pwm for speed
    
    lightsReady(); //checks and runs a function if the lights are coming on or not

  } else {   //else statement to helpo if none of the conditions above are met
    Serial.print("Odd case, stop the robot completely"); //print statement to state the robots action

    //everything off
    digitalWrite(in1, LOW); 
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW); 
    digitalWrite(enA, 0);
    digitalWrite(enB, 0);
   
    lightsReady(); //checks and runs a function if the lights are coming on or not
  }

}

//Section of the code regarding flashing led's and ultrasonic sensor
void lightsReady() {
    while (distance <= 25) {
    digitalWrite(redLight, HIGH); //red led light flashes on
    delay(400); //wait a small time before changing color
    digitalWrite(redLight, LOW); //red led turns off
    digitalWrite(blueLight, HIGH); //blue led light flashes on
    delay(400); //wait a small time before changing color
    digitalWrite(blueLight, LOW); //blue led turns off
    }
  }
