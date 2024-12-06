#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

/*
* -Title:
* -- Engr 111 Team 7
*
* - Description
* --Team project for the mobility of a designed robot
*
*/

//functions prototypes 

//right Wheel
void rFoward();
void rBack();

//left Wheel
void lFoward();
void lBack();

//Vehicle movement
void moveF();        
void moveB();
void rStop();
void lStop();
void stop();
void r360();
void l360();

//ultrasonic
float checkDisk();




// Pins and varible description
//wheel movement
const int rwheel= 4;
const int rWhCurrent = 6;
const int lwheel= 2;
const int lwhCurrent = 5;
const int defaultSpeed = 55;//sixty five

//Object detection
const int objleftSensor = A1;
const int objrightSensor = A2;

//Ligth Sensor
const int lprmSensor = 7;
const int rprmSensor = 9;

//ultra sonic
const int trigpin = 12;
const int echoPin = 13;
float d;

void setup() {
  //wheel movement
  pinMode(lwheel, OUTPUT);
  pinMode(rwheel, OUTPUT);
  pinMode(lwhCurrent, OUTPUT);
  pinMode(rWhCurrent, OUTPUT);

  //object detection
  pinMode(objleftSensor, INPUT);
  pinMode(objrightSensor, INPUT);

  //light sensor
  pinMode(lprmSensor,INPUT);
  pinMode(rprmSensor,INPUT);

  // Ultrasonic sensor 
  Serial.begin(9600);
  pinMode(trigpin, OUTPUT);
  pinMode(echoPin, INPUT);

  //lcd
  lcd.init();
  lcd.backlight();
}

void loop() {
  //obstacle avoidance 
  int rObj = digitalRead(objrightSensor);
  int lObj = digitalRead(objleftSensor);
  //lightSensor
  int rColor = digitalRead(rprmSensor);
  int lColor = digitalRead(lprmSensor);

  //ultrasonic
  d =checkDisk();
  Serial.println(d);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Obstacle Distance");// line 1 
  //lcd.setCursor(0,1); lcd.print(d);
  //delay(200);
if(rColor == 0 && lColor == 0 ) //ligth sensor mobility
    {
      moveF();
    }
    else if (rColor == 1 && lColor == 1) //both black line
    {
      stop();
    }

    //Turn Right 
    else if (rColor == 1 && lColor == 0 )
    {
      lFoward();
      rBack();
    }

    //Turn Left
    else if (lColor == 1 && rColor == 0 )
    {
      rFoward();
      lBack();
    }
}

  

// Function Definition

// Ultrasonic Sensor Distance Calcualtion
float checkDisk()
{
  // Clears the trigpin condition 
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);

  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigpin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin, LOW);

  // Read te echoPin, returns the sound wave travel time in microseconds
  long duration = pulseIn (echoPin, HIGH);

  // calculatinf the distance 
  float d = duration * 0.034 /2; // speed of sound wave divide by 2 (go and back)

  // return the diatance 
  return d;
}

//right wheel Foward
void rFoward()
{
  digitalWrite(rwheel, LOW);
  analogWrite(rWhCurrent, defaultSpeed);
}
void rBack()
{
  digitalWrite(rwheel, HIGH); //right back
  analogWrite(rWhCurrent, defaultSpeed);
}
 

//left wheel movements 
void lFoward()
{
  digitalWrite(lwheel, HIGH);
  analogWrite(lwhCurrent, defaultSpeed);
}
void lBack()
{
  digitalWrite(lwheel, LOW);
  analogWrite(lwhCurrent, defaultSpeed);
}

//MOvements 
void moveF() //foward
{
  rFoward();
  lFoward();
}
void moveB() //back
{
  lBack();
  rBack();
}

//Stop moving
void rStop()
{
  digitalWrite(rwheel, LOW);
  analogWrite(rWhCurrent, 0);
}
void lStop()
{
  digitalWrite(lwheel, HIGH);
  analogWrite(lwhCurrent, 0);
}
void stop()
{
  lStop();
  rStop();
}

//for funcies
void r360()
{
  rFoward();
  lBack();
}
void l360()
{
  rBack();
  lFoward();
}
