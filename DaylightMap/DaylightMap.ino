#include <WiFi.h>
#include "time.h"
#include <NewPing.h>
#define ledPin1 22
#define ledPin2 15
#define ledPin3 13
#define ledPin4 21
#define ledPin5 27
#define echoPin 33
#define trigPin 32
#define maxDist 100
#define buttonPin 2

NewPing sonar(trigPin, echoPin, maxDist);

const char* ssid     = "Columbia University";
const char* password = "";

const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -32400;
const int   daylightOffset_sec = 3600;
int akst;
int pst;
int mst;
int cst;
int est;
int mode;
long dur;
long dist;
int lastButtonState = HIGH;
int buttonState = HIGH; 
unsigned long lastDebounceTime = 0; 
unsigned long debounceDelay = 50;  
bool buttonPressed = false;


void setup(){
  Serial.begin(9600);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  
  // Init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  getLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);

  mode = 1; // CHANGE
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(ledPin5, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(buttonPin), pressButton, FALLING);
}

void loop(){
  delay(50);
  akst = getLocalTime();
  timezone();

  // BUTTON CHANGING MODE

  if (buttonPressed){
    Serial.println("pressed");
    mode = switchMode();
    buttonPressed = false;
  }

  // MODE FUNCTIONS 
  if (mode == 0){
    display(6);
  }
  else if (mode == 1){
    display(1);
    display(2);
    display(3);
    display(4);
    display(5);
  }
  else if (mode == 2){
    activeSense();
    if (0 <= dist && dist <= 6){
      display(1);
    }
    if (6 < dist && dist <= 9){
      display(2);
    }
    if (9 < dist && dist <= 12){
      display(3);
    }
    if (12 < dist && dist <= 15){
      display(4);
    }
    if (15 < dist && dist <= 18){
      display(5);
    }
    if (19 < dist){
      display(6);
    }
  }

  // TEST TIMEZONES AND LIGHT LEVELS
  Serial.print("Alaska time:");
  Serial.println(akst);
  Serial.print("Pacific time:");
  Serial.println(pst);
  Serial.print("Mountain time:");
  Serial.println(mst);
  Serial.print("Central time:");
  Serial.println(cst);
  Serial.print("Eastern time:");
  Serial.println(est);
}

int switchMode(){
  if (mode == 1){
    return 2;
  }
    else if (mode == 2){
      return 1;
    }
      else{
        return 9999;
      }
}

void pressButton(){
  buttonPressed = true;
}

int getLocalTime(){
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return 999;
  }
  char timeHour[3];
  strftime(timeHour,3, "%H", &timeinfo);
  return atoi(timeHour);
}


void timezone(){
  if (akst == 20){
    pst = 21;
    mst = 22;
    cst = 23;
    est = 0;
  }
  else if (akst == 21){
    pst = 22;
    mst = 23;
    cst = 0;
    est = 1;
  }
  else if (akst == 22){
    pst = 23;
    mst = 0;
    cst = 1;
    est = 2;
  }
  else if (akst == 23){
    pst = 0;
    mst = 1;
    cst = 2;
    est = 3;
  }
  else{
    pst = akst + 1;
    mst = akst + 2;
    cst = akst + 3;
    est = akst + 4;
  }
}


int lightLevel(int x){
  int level;
  if ((0 <= x && x < 7) || (18 < x && x <= 23)){
    level = 0;
  }
  if ((6 < x && x <= 8) || x == 18){
    level = 5;
  }
  if ((8 < x && x <= 10) || x == 17){
    level = 127;
  }
  if ((10 < x && x <= 12) || (14 < x && x <= 16)){
    level = 191;
  }
   if (12 < x && x <= 14){
    level = 255;
  }
  return level;
}

long activeSense(){
  dist = sonar.ping_cm();
  return dist;
}


void display(int x){
  if (x == 1){
    analogWrite(ledPin1, lightLevel(akst));
  }
  else if (mode == 2){
    analogWrite(ledPin1, 0);
  }
  if (x == 2){
    analogWrite(ledPin2, lightLevel(pst)); 
  }
  else if (mode == 2){
    analogWrite(ledPin2, 0);
  }
  if (x == 3){
    analogWrite(ledPin3, lightLevel(mst)); 
  }
  else if (mode == 2){
    analogWrite(ledPin3, 0);
  }
  if (x == 4){
    analogWrite(ledPin4, lightLevel(cst)); 
  }
  else if (mode == 2){
    analogWrite(ledPin4, 0);
  }
  if (x == 5){
    analogWrite(ledPin5, lightLevel(est));
  }
  else if (mode == 2){
    analogWrite(ledPin5, 0);
  }
  if (x==6){
    analogWrite(ledPin1, 0);
  }
}
