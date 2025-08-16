//Aurdino Based code


#include <Servo.h>   

Servo servo;     
int trigPin = 5;    
int echoPin = 6;   
int servoPin = 7;
int irSensor = 9;
int led = 10;
long duration, dist, average;   
long aver[3];   

void setup() {       
    Serial.begin(9600);
    servo.attach(servoPin);  
    pinMode(trigPin, OUTPUT);  
    pinMode(echoPin, INPUT);  
    pinMode(irSensor, INPUT_PULLUP);  // Fix: Enable pull-up to prevent floating values
    pinMode(led, OUTPUT); 
    servo.write(150);  // Start in closed position
    delay(100);
} 

void measure() {  
    digitalWrite(led, HIGH);
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(15);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    dist = (duration / 2) / 29.1;    

    if (dist < 5 || dist > 1000) {  
        dist = 1000;  
    }
}

void loop() { 
    for (int i = 0; i < 3; i++) {  
        measure();               
        aver[i] = dist;            
        delay(10);              
    }
    dist = (aver[0] + aver[1] + aver[2]) / 3;    

    int irState = digitalRead(irSensor); 

    if ((dist > 5 && dist < 50) || irState == LOW) {  
        servo.write(0);  
        delay(3000);       
        servo.write(150);    
        delay(1000);
    }
    
    Serial.print("Distance: ");
    Serial.print(dist);
    Serial.print(" cm, IR Sensor: ");
    Serial.println(irState == LOW ? "Detected" : "No Object");
}
