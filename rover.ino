#include <Adafruit_SH1106.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <Servo.h>

String wifiName = "Airtel_avdeep_r";
String wifiP = "Niti1@deep";
String userID = "P44J1";
String page = "terminal";
String datatype = "STRING";
String Path = "";
String request ="";

#define TRIG_PIN PC14
#define ECHO_PIN PC15
#define LEFT_P PA0
#define LEFT_N PA1
#define RIGHT_P PB8
#define RIGHT_N PB9
#define OBSTACLE_DISTANCE 20
#define LEFT_ANGLE 150
#define RIGHT_ANGLE 30
#define CENTER_ANGLE 90

int textSize = 1;
long duration;
float distance;
float prev;

bool lastStateLSW = 0;
bool lastStateRSW = 0;
bool inverted = false;
bool systemReady = false;

Servo s1;

Adafruit_SH1106 display(-1);

float ema(float val);
float getDistance();
void updateDisplay();
void espInit();
void oledDisplay(String msg);
void forward();
void left();
void right();
void stop();
void lookLeft();
void lookRight();
void lookCenter();
void moveSmoothWithScan(int from, int to);
void runObstacleMode();


enum RequestType {
  REQ_SSID,
  REQ_PASS,
  REQ_PATH,
  REQ_TYPE,
  REQ_UNKNOWN
};

RequestType getRequestType(String req) {
  if (req == "REQ:SSID") return REQ_SSID;
  else if (req == "REQ:PASS") return REQ_PASS;
  else if (req == "REQ:PATH") return REQ_PATH;
  else if (req == "REQ:TYPE") return REQ_TYPE;
  else return REQ_UNKNOWN;
}

float ema(float val){
  prev = val;
  float alpha = 0.6;

  float filtered = alpha * prev + (1 - alpha) * val;
  prev = filtered;
  return filtered;
}

float getDistance(){
  digitalWrite(TRIG_PIN,0);
  delayMicroseconds(2);

  digitalWrite(TRIG_PIN,1);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN,0);

  duration = pulseIN(ECHO_PIN,1);
  distance = duration * 0.0343 / 2;

  return ema(distance);
}

void updateDisplay(){
  oledDisplay("Terminal: " + request);
}

void espInit() {

  switch(getRequestType(request)) {

    case REQ_SSID:
      Serial3.println("SSID:" + wifiName);
      Serial.println("Sent SSID");
      oledDisplay("Sent SSID");
      break;

    case REQ_PASS:
      Serial3.println("PASS:" + wifiP);
      Serial.println("Sent PASS");
      oledDisplay("Sent PASS");
      break;

    case REQ_PATH:
      Serial3.println("PATH:" + Path);
      Serial.println("Sent PATH");
      oledDisplay("Sent PATH");
      break;

    case REQ_TYPE:
      Serial3.println("TYPE:" + datatype);
      Serial.println("Sent TYPE");
      oledDisplay("System Ready");
      systemReady = true;
      break;

    default:
      oledDisplay("Waiting for init...");
      Serial.println("Ignored (not ready): " + request);
      break;
  }

  delay(100);
}

void oledDisplay(String msg){
  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(textSize);
  display.setTextColor(WHITE);
  display.println(msg);
  display.display();
}

void forward(){
  digitalWrite(LEFT_P,1);
  digitalWrite(LEFT_N,0);
  digitalWrite(RIGHT_P,1);
  digitalWrite(RIGHT_N,0);
}

void left(){
  digitalWrite(LEFT_P,1);
  digitalWrite(LEFT_N,0);
  digitalWrite(RIGHT_P,0);
  digitalWrite(RIGHT_N,1);
}

void right(){
  digitalWrite(LEFT_P,0);
  digitalWrite(LEFT_N,1);
  digitalWrite(RIGHT_P,1);
  digitalWrite(RIGHT_N,0);
}

void stop(){
  digitalWrite(LEFT_P,0);
  digitalWrite(LEFT_N,0);
  digitalWrite(RIGHT_P,0);
  digitalWrite(RIGHT_N,0);
}

void lookLeft(){
  int current = servo.read();
  moveSmoothWithScan(current, LEFT_ANGLE);
}

void lookRight(){
  int current = servo.read();
  moveSmoothWithScan(current,RIGHT_ANGLE);
}

void lookCenter(){
  int current = servo.read();
  moveSmoothWithScan(current,CENTER_ANGLE);
}

void moveSmoothWithScan(int from, into to){
  if(from < to){
    for (int i = from; i <= to; i++){
      servo.write(i);

      float dist = getDistance();

      if(dist < OBSTACLE_DISTANCE){
        stop();
      }

      delay(10);
    }
  }else{
    for (int i = from; i>=to ; i--){
      servo.write(i);

      float dist = getDistance();

      if(dist < OBSTACLE_DISTANCE){
        stop();
      }

      delay(10);
    }
  }
}

void runObstacleMode(){
  float dist = getDistance();

  if(dist>=OBSTACLE_DISTANCE){
    forward();
    return;
  }

  stop();

  lookLeft();
  delay(200);
  float leftDist = getDistance();

  lookRight()
  delay(200);
  float rightDist = getDistance();

  lookCenter();
  delay(100);

  if(leftDist > rightDist){
    left();
  }else{
    right();
  }

  delay(400);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial3.begin(9600);

  Serial.println("STM32 Booted");

  Path = "commands/" + userID + "/" + page;

  pinMode(LSW, INPUT);
  pinMode(RSW, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(M1,OUTPUT);
  pinMode(M2,OUTPUT);
  pinMode(M3,OUTPUT);
  pinMode(M4,OUTPUT);
  
  s1.attach(PB1);

  display.begin(SH1106_SWITCHCAPVCC, 0x3C);

  display.setTextSize(1);
  display.invertDisplay(1);

  oledDisplay("System Booting...");
}

void loop() {
  // put your main code here, to run repeatedly