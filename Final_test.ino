//motor
#define enA 3
#define enB 4
#define in1 8
#define in2 9
#define in3 10
#define in4 11


int state;
int flag=0;
int stateStop=0;

//ultrasound
const int trigPin = 12;
const int echoPin = 13;

float duration, distance = 2.80;

//servo
#include <Servo.h>

Servo myservo;
int pos = 0;


void setup() {
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin, OUTPUT);  
	pinMode(echoPin, INPUT);
  Serial.begin(9600);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  pinMode(enA, HIGH);
  pinMode(enB, HIGH);
  myservo.attach(7);
}

void loop() {
  if (Serial.available()>0) {
    state=Serial.read();
    flag=0;
  }

  if (state == 'F'){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    // Delay(1000)
    if(flag==0){
      Serial.println("Go Forward!");
      flag=1;
    }
  }
  else if (state == 'R'){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    if(flag==0){
      Serial.println("Go Right!");
      flag=1;
    }
  }
  else if (state == 'L'){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    if(flag==0){
      Serial.println("Go Left!");
      flag=1;
    }
  }
  else if (state == 'B'){
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    if(flag==0){
      Serial.println("Go Back!");
      flag=1;
    }
  }
  else if (state == 'P'){
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(5000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(2000);
    if(flag==0){
      Serial.println("stop!");
      flag=1;
    }

    //open servo
    for (pos = 90; pos >= 0; pos -= 10) {
      myservo.write(pos);
      delay(100);
    }

    //check distance
    while(distance >= 2.80){
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(2000);
      
      digitalWrite(trigPin, LOW);  
	    delayMicroseconds(2);  
	    digitalWrite(trigPin, HIGH);  
	    delayMicroseconds(10);  
	    digitalWrite(trigPin, LOW);

      duration = pulseIn(echoPin, HIGH); 

      distance = (duration*.0343)/2; 

      Serial.print("Distance: ");  
	    Serial.println(distance);  
	    delay(100);
    }

    //close seervo
    for (pos = 0; pos <= 90; pos += 10) {
      myservo.write(pos);
      delay(100);
    }

    //front-back-front-back
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(3000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(3000);
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(3000);
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(3000);

    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(20000);
  }
}