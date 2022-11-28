//Information in the code, and reference material can be found here:
//https://create.arduino.cc/projecthub/robocircuits/line-follower-robot-arduino-299bae author is RoboCircuits
  
  
  int distance; //declaring variable for distance
  double duration; //declating variable for duratrion the signal is out
  int maxspeed = 140; //max speed the robot goes
  int turn_speed = 242; //turning speed
  int tdelay = 8; //delay between actions
  
//H-Bridge Connections 
  int in1 = 6; //Motor One A
  int in2 = 7; //Motor One B
  int in3 = 8; //Motor Two A
  int in4 = 9; //Motor Two B
  int enA = 10; //PWM Control
  int enB = 11; //PWM Control

//Ultrasonic Sensor Connections
  int trigPin = 2; //establishing the trig pin of ultrasonic sensor
  int echoPin = 3; //establishing the echo pin of ultrasonic sensor
  
//Led Connections
  int redLight = 4; //establishing the red led
  int blueLight = 5; //establishing the blue led

//IR Sensor Connection and States
  int irSensor_left = A0;
  int irSensor_right = A1;
  int irLeft_state;
  int irRight_state;

void setup() {
  //Defining what the variables do
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin, INPUT);
  pinMode(echoPin, OUTPUT);
  pinMode(redLight, OUTPUT);
  pinMode(blueLight, OUTPUT);

  digitalWrite(blueLight, HIGH);
  digitalWrite(redLight, HIGH);
  delay(4000); //Start-up delay
}

void loop() {
  irLeft_state = analogRead(irSensor_left); //Reading left IR sensor
  irRight_state = analogRead(irSensor_right); //Reading right IR sensor
  
  if (irRight_state > 500 && irLeft_state < 500){ //Turn right
    digitalWrite (in1,HIGH);
    digitalWrite(in2,LOW);                       
    digitalWrite (in3,HIGH);
    digitalWrite(in4,LOW);
    analogWrite (enA, maxspeed);
    analogWrite (enB, turn_speed);
    
    } if (irRight_state < 500 && irLeft_state > 500){ //Turn left
      digitalWrite(in1,LOW);
      digitalWrite(in2,HIGH);                       
      digitalWrite(in3,LOW);
      digitalWrite(in4,HIGH);
      analogWrite(enA, turn_speed);
      analogWrite(enB, maxspeed);
    
      delay(tdelay);
    
    } if (irRight_state < 500 && irLeft_state < 500){ //Go forward
      digitalWrite(in2,LOW);
      digitalWrite(in1,HIGH);                       
      digitalWrite(in4,HIGH);
      digitalWrite(in3,LOW);
      analogWrite(enA, maxspeed);
      analogWrite(enB, maxspeed);
    
      delay(tdelay);
      
    } if (irRight_state > 500 && irLeft_state > 500){ //Turn robot off
      analogWrite(enA, 0);
      analogWrite(enB, 0);
    }
}

//Uncomment if you wish to see object distance (code expansion pack)
//void lightsReady() {
//  if (distance <= 30 && distance > 0) {
//    digitalWrite(redLight, HIGH); //red led light flashes on
//    delay(400); //wait a small time before changing color
//    digitalWrite(redLight, LOW); //red led turns off
//    digitalWrite(blueLight, HIGH); //blue led light flashes on
//    delay(400); //wait a small time before changing color
//    digitalWrite(blueLight, LOW); //blue led turns off
//      }
//}
//  digitalWrite(trigPin, LOW);
//  delayMicroseconds(2);
//  digitalWrite(trigPin, HIGH);
//  delayMicroseconds(10);
//  digitalWrite(trigPin, LOW);
//  duration = pulseIn(echoPin, HIGH);
//  distance = duration * 0.034 / 2;
