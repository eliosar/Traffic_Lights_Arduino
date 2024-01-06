#include "Constants.h"
#include "Variables.h"

void setup() {
  Serial.begin(9600);
  while(!Serial);

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

  pinMode(button, INPUT);

  digitalWrite(lightCar13Green, HIGH);
  digitalWrite(lightPedestrian24Green, HIGH);
  digitalWrite(lightCar24Red, HIGH);
  digitalWrite(lightCar24Yellow, LOW); // Yellow somehow just wanted to be also on
  digitalWrite(lightPedestrian13Red, HIGH);
  buttonWork();
  Serial.println("setup");
}

void loop() {
  Serial.println("loop start");
  Serial.println("--------------------");
  wait(waitForSecEachRound);
  Serial.println("finish round13");
  Serial.println("start round24 setup");
  Serial.println("--------------------");
  changeTo24();
  Serial.println("finish round24 setup");
  Serial.println("start round24");
  Serial.println("--------------------");
  wait(waitForSecEachRound);
  Serial.println("finish round24");
  Serial.println("--------------------");
  changeTo13();
}

void changeTo24(){
  // Pedestrians24 RED
  digitalWrite(lightPedestrian24Green, LOW);
  digitalWrite(lightPedestrian24Red, HIGH);
  // Car13 YELLOW
  digitalWrite(lightCar13Green, LOW);
  digitalWrite(lightCar13Yellow, HIGH);
  // Car24 RED YELLOW
  digitalWrite(lightCar24Yellow, HIGH);
  // wait
  wait(waitForSecInChange);
  // Car24 GREEN
  digitalWrite(lightCar24Yellow, LOW);
  digitalWrite(lightCar24Red, LOW);
  digitalWrite(lightCar24Green, HIGH);
  // Car13 RED
  digitalWrite(lightCar13Yellow, LOW);
  digitalWrite(lightCar13Red, HIGH);
  // Pedestrian13 GREEN
  digitalWrite(lightPedestrian13Red, LOW);
  digitalWrite(lightPedestrian13Green, HIGH);
}

void changeTo13(){
  // Pedestrians13 RED
  digitalWrite(lightPedestrian13Green, LOW);
  digitalWrite(lightPedestrian13Red, HIGH);
  // Car24 YELLOW
  digitalWrite(lightCar24Green, LOW);
  digitalWrite(lightCar24Yellow, HIGH);
  // Car13 RED YELLOW
  digitalWrite(lightCar13Yellow, HIGH);
  // wait
  wait(waitForSecInChange);
  // Car13 GREEN
  digitalWrite(lightCar13Yellow, LOW);
  digitalWrite(lightCar13Red, LOW);
  digitalWrite(lightCar13Green, HIGH);
  // Car24 RED
  digitalWrite(lightCar24Yellow, LOW);
  digitalWrite(lightCar24Red, HIGH);
  // Pedestrian24 GREEN
  digitalWrite(lightPedestrian24Red, LOW);
  digitalWrite(lightPedestrian24Green, HIGH);
}

// still have to callibrate it
void wait(int sec){
  unsigned long millisTmp = millis();
  unsigned long wantedMillis = millisTmp + ((sec * 1000) / currentSpeed);

  while(millis() <= wantedMillis){
    wantedMillis = millisTmp + ((sec * 1000) / currentSpeed);
    do{
    buttonWork();
    }while(currentSpeed == 0);
  }
  Serial.print("current speed: ");
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
    if(millis() >= lastPressed + 500){
      lastPressed = millis();
      currentSpeed++;
      if(currentSpeed == 3) {currentSpeed = 0; Serial.println("stop");}
    }
  }
}