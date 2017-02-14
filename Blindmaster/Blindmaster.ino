/*

*/

#include <Wire.h>
#include <Adafruit_MotorShield.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <DNSServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <String.h>

#include "utility/Adafruit_MS_PWMServoDriver.h"

ESP8266WebServer server(80);

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
//Motor connected to M1 (M1 = 1, M2 = 2 etc)
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

uint8_t lastCommand;
String webString;

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome to ESP8266 Blind Master");

  // If device does not have valid AP login, starts as AP with WiFi config @ http://192.168.4.1
  WiFiManager wifiManager;
  wifiManager.autoConnect("BlindMaster", "password"); //call without parameter for unique name (i.e. "ESP" + ID)

  // Motor shield config
  AFMS.begin();
  runMotor(FORWARD, 0);

  // Web server configuration
  lastCommand = BRAKE;

  server.on("/", []() {
    webString = buildHtml(lastCommand);
    server.send(200, "text/html", webString);
  });

  //FORWARD = 1, BACKWARD = 2, BRAKE = 3, RELEASE = 4
  server.on("/up", []() {
    runMotor(FORWARD);
    webString = buildHtml(FORWARD);
    server.send(200, "text/html", webString);
  });

  server.on("/down", []() {
    runMotor(BACKWARD);
    webString = buildHtml(BACKWARD);
    server.send(200, "text/html", webString);
  });

  server.on("/stop", []() {
    stopMotor();
    webString = buildHtml(BRAKE);
    server.send(200, "text/html", webString);
  });

  server.begin();
  Serial.print("Connected to AP, started web server.");
}

void loop() {
  server.handleClient();
}

// Functions for running/stopping the motor. Uses M1 port.

void runMotor(uint8_t dir) {
  myMotor->setSpeed(255);
  myMotor->run(dir);
  lastCommand = dir;
}

void stopMotor() {
  myMotor->run(RELEASE);
  lastCommand = BRAKE;
}

void runMotor(uint8_t dir, uint8_t seconds) {
  runMotor(dir);
  delay(seconds * 1000);
  stopMotor();
}

// Build webpage, static part first

String buildHtml(uint8_t dir) {
  String baseString = "";     // C is apparently broken...
  baseString = baseString + "<html><head>"+
"<title>M.nu rullgardinsmästare</title>"+
"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">"+
"<style>"+
"h2 {"+
"  font-family: Open Sans;"+
"}"+
"body {"+
"  text-align: center;"+
"}"+
".buttons {"+
"    display: flex;"+
"    justify-content: stretch;"+
"}"+
".btn {"+
"    line-height: 2em;"+
"    background: #D60412;"+
"    color: white;"+
"    text-align: center;"+
"    text-decoration: none;"+
"    font-size: 28px;"+
"    flex-grow: 1;"+
"}"+
".btn:hover {"+
"  background: #9E050F;"+
"}"+
".btn-disabled {"+
"  background: #7A4C4F;"+
"  pointer-events: none;"+
"}"+
"</style></head>"+
"<body>"+
"  <h2>Blind master</h2>"+
"  <div class=\"buttons\">";

// Disable button depending on fetched URL. Uses inline ifs
// Syntax (condition) ? true-case : false-case

baseString = baseString +
"    <a class=\"btn" + ((dir == FORWARD) ? " btn-disabled" : "") +"\" href=\"/up\">&#9650;</a>" +
"    <a class=\"btn" + ((dir == BRAKE) ? " btn-disabled" : "") +"\" href=\"/stop\">&#11035;</a>" +
"    <a class=\"btn" + ((dir == BACKWARD) ? " btn-disabled" : "") +"\" href=\"/down\">&#9660;</a></div>";

  return baseString + "</body></html>";
}
