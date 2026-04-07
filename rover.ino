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

#define LSW PA14 
#define RSW PA13
#define TRIG_PIN PC14
#define ECHO_PIN PC15
#define M1 PA0
#define M2 PA1
#define M3 PB8
#define M4 PB9

int textSize = 1;
long duration;
float distance;

bool lastStateLSW = 0;
bool lastStateRSW = 0;
bool inverted = false;
bool systemReady = false;

Servo s1;

Adafruit_SH1106 display(-1);

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
  // put your main code here, to run repeatedly:

}
