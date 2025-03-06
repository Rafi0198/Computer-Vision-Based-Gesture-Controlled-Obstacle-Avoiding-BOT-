#include <NewPing.h>
#include <WiFi.h>
#include <WebServer.h>
#include <WebSocketsServer.h>

const char* ssid = "Rafi";
const char* password = "qnh1013hg";

WebSocketsServer webSocket = WebSocketsServer(81);

//our L298N control pins
byte LeftMotorForward = 12;
byte LeftMotorBackward = 14;
byte RightMotorForward = 27;
byte RightMotorBackward = 26;
byte LeftMotorSpeed = 13 ; byte RightMotorSpeed = 25;
int SpeedLeft; int SpeedRight;

byte trigPin = 33; byte echoPin =32;
byte forwardLed = 35; byte backwardLed=34;
byte maxDistance = 250;
int distance;
String cmd; 
bool count = true; 

NewPing sonar(trigPin, echoPin, maxDistance);


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  if(type == WStype_TEXT) {

   
     cmd = String((char*)payload);
      //cmd = data.charAt(0);
      Serial.print("Received data: ");
      Serial.println(cmd[0]);
  }

}

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  pinMode(RightMotorForward, OUTPUT);
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);
  pinMode(RightMotorSpeed, OUTPUT);
  pinMode(LeftMotorSpeed, OUTPUT);
//  pinMode(forwardLed, OUTPUT); 
//  pinMode(backwardLed, OUTPUT); 
  


  //delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);

  //  SpeedLeft = 150;
  //  SpeedRight = 150;
  //
  //  analogWrite(LeftMotorSpeed, SpeedLeft);
  //  analogWrite(RightMotorSpeed, SpeedRight);

  WiFi.begin(ssid, password);

  Serial.print("Connecting to ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);

}

void loop() {
  // put your main code here, to run repeatedly:

 
 webSocket.loop();

 distance = readPing(); //Serial.println(distance);
 //distance = 30;
 if (distance > 35) {

    switch(cmd[0]) {  // cmd[0] to check the first character of the string
      
        case 'F':
            moveForward();
            break;
        
        case 'B':
            moveBackward();
            break;

        case 'L':
            turnLeft();
            break;

        case 'R':
            turnRight();
            break;

        case 'S':
            moveStop();
            break;

//        default:
//            moveStop();
//            break;
    }
    count = true;
}


else {
          analogWrite(LeftMotorSpeed, 160);
          if (count) { 
            moveStop();
            count = false; 
           } 
          
          if (cmd[0] == 'B') {
            moveBackward();
           
           }
     
          if (cmd[0] == 'S') {
            moveStop();
             
           }
 
      }

}



int readPing() {
  //delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0) {
    cm = 250;
  }
  return cm;
}

void moveForward() {

  Serial.println("==Forward==");
  //Speed(150,150);

  analogWrite(LeftMotorSpeed, 150);
  analogWrite(RightMotorSpeed, 150);

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);
//  digitalWrite(forwardLed, HIGH);
  
}

void moveBackward() {

  Serial.println("==Backward==");
  //Speed(150,150);

  analogWrite(LeftMotorSpeed, 160);
  analogWrite(RightMotorSpeed, 160);

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
//  digitalWrite(backwardLed, HIGH);

}

void ForwardRight() {
  Serial.println("==ForwardRight==");
  //Speed(150,120);

  analogWrite(LeftMotorSpeed, 160);
  analogWrite(RightMotorSpeed, 130);

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);

}

void ForwardLeft() {
  Serial.println("==ForwardLeftt==");
  //Speed(120,150);

  analogWrite(LeftMotorSpeed, 130);
  analogWrite(RightMotorSpeed, 160);

  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);

}

void BackwardRight() {

  Serial.println("==BackwardRight==");
  //Speed(150,120);

  analogWrite(LeftMotorSpeed, 160);
  analogWrite(RightMotorSpeed, 130);

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);

}

void BackwardLeft() {

  Serial.println("==BackwardLeft==");
  // Speed(120,150);

  analogWrite(LeftMotorSpeed, 130);
  analogWrite(RightMotorSpeed, 160);


  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);

}



void turnRight() {

  Serial.println("==turnRight==");
  //Speed(100,100);

  analogWrite(LeftMotorSpeed, 100);
  analogWrite(RightMotorSpeed, 100);
  
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(RightMotorBackward, HIGH);

  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);

}

void turnLeft() {

  Serial.println("==turnLeft==");
  
  analogWrite(LeftMotorSpeed, 100);
  analogWrite(RightMotorSpeed, 100);

  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);

}

void moveStop() {

  Serial.println("==moveStop==");
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
//  digitalWrite(forwardLed, LOW);
//  digitalWrite(backwardLed, LOW);

  analogWrite(LeftMotorSpeed, 0);
  analogWrite(RightMotorSpeed, 0);
}



void Speed (int SpeedLeft, int SpeedRight) {

  analogWrite(LeftMotorSpeed, SpeedLeft);
  analogWrite(RightMotorSpeed, SpeedRight);

}
