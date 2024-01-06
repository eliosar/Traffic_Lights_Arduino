#include "Constants.h"
#include "Variables.h"

void setup() {
  Serial.begin(9600);

  pinMode(lightCar13Green, OUTPUT);
  pinMode(lightCar13Yellow, OUTPUT);
  pinMode(lightCar13Red, OUTPUT);

  pinMode(lightPedestrian13Green, OUTPUT);
  pinMode(lightPedestrian13Red, OUTPUT);

  pinMode(lightCar24Green, OUTPUT);
  pinMode(lightCar24Yellow, OUTPUT);
  pinMode(lightCar24Red, OUTPUT);

  pinMode(lightPedestrian24Green, OUTPUT);
  pinMode(lightPedestrian24Red, OUTPUT);

  pinMode(potentiometer, INPUT);

  digitalWrite(lightCar13Green, high);
  digitalWrite(lightPedestrian24Green, high);
  digitalWrite(lightCar24Red, high);
  digitalWrite(lightPedestrian13Red, high);
  potentiometerWork();
}

void loop() {
  wait(waitForSecEachRound);
  Serial.println("finish round13");
  Serial.println("start round24 setup");
  changeTo24();
  Serial.println("finish round24 setup");
  Serial.println("start round24");
  wait(waitForSecEachRound);
  Serial.println("finish round24");
  changeTo13();
  Serial.println("--------------------");
}

void changeTo24(){
  // Pedestrians24 RED
  analogWrite(lightPedestrian24Green, LOW);
  analogWrite(lightPedestrian24Red, high);
  // Car13 YELLOW
  analogWrite(lightCar13Green, LOW);
  analogWrite(lightCar13Yellow, high);
  // Car24 RED YELLOW
  analogWrite(lightCar24Yellow, high);
  // wait
  wait(waitForSecInChange);
  // Car24 GREEN
  analogWrite(lightCar24Yellow, LOW);
  analogWrite(lightCar24Red, LOW);
  analogWrite(lightCar24Green, high);
  // Car13 RED
  analogWrite(lightCar13Yellow, LOW);
  analogWrite(lightCar13Red, high);
  // Pedestrian13 GREEN
  analogWrite(lightPedestrian13Red, LOW);
  analogWrite(lightPedestrian13Green, high);
}

void changeTo13(){
  // Pedestrians13 RED
  analogWrite(lightPedestrian13Green, LOW);
  analogWrite(lightPedestrian13Red, high);
  // Car24 YELLOW
  analogWrite(lightCar24Green, LOW);
  analogWrite(lightCar24Yellow, high);
  // Car13 RED YELLOW
  analogWrite(lightCar13Yellow, high);
  // wait
  wait(waitForSecInChange);
  // Car13 GREEN
  analogWrite(lightCar13Yellow, LOW);
  analogWrite(lightCar13Red, LOW);
  analogWrite(lightCar13Green, high);
  // Car24 RED
  analogWrite(lightCar24Yellow, LOW);
  analogWrite(lightCar24Red, high);
  // Pedestrian24 GREEN
  analogWrite(lightPedestrian24Red, LOW);
  analogWrite(lightPedestrian24Green, high);
}

// still have to callibrate it
void wait(int sec){
  unsigned long millisTmp = millis();
  unsigned long wantedMillis = millisTmp + ((sec * 1000) / currentSpeed);

  while(millis() <= wantedMillis){
    wantedMillis = millisTmp + ((sec * 1000) / currentSpeed);
    do{
    potentiometerWork();
    }while(currentSpeed == 0);
  }
  Serial.println(currentSpeed);

  /*unsigned long restMillis = wantedMillis - millis();
  //notice about millis()!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  while(restMillis > 0){
    //potentiometerWork();
    restMillis = wantedMillis - millis();
    restMillis = restMillis / currentSpeed;
  }*/

  /*for(int i = 0; i < sec; i++){
    for(int x = 0; x < 20; x++){ // divides each second in 50ms
      delay(50 * currentSpeed);
      //potentiometerWork();
    }
  }*/
}

void buttonWork(){
  if(digitalRead(button)){
    currentSpeed++;
    if(currentSpeed == 2) currentSpeed = 1;
  }
}