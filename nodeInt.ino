#include "FirebaseESP8266.h"  // Instaleaza libraria Firebase pentru ESP8266
#include <ESP8266WiFi.h>
#include <DHT.h>    // Instaleaza libraria DHT11 si libraria de senzor Adafruit Unified
//realizarea conexiunii cu Firebase
#define FIREBASE_HOST "fir-iot-27cf7-default-rtdb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "nOkf5M1wQJElXDAUoOzR4YWeq1S5K90vzZhntZKV"
#define WIFI_SSID "DIGI-01024552"
#define WIFI_PASSWORD "YEhi8I3I"
//#define ONE_WIRE_BUS D2 
//#define DHT2PIN 0
#define DHTPIN 2// Connect Data pin of DHT to D2
int led = D1;     // Connect LED to D5
int radiator = D0;
int parter = D5;
int afara = D7;
int subsol = D6;
int Et1 = D2;
int Et2 = D3;
//int buzzer=D5;
//int sens;
//int yx;
//int xx;
//int kk;
//int ll;
//int Senz=D6;
//int m1=D7;
//int m2=D8;
//int i,k=0,r=0,p=1,k1=0,d,r1,r2,r3,r4;
//int l=0;
//l era bool si k era 0 si l cred ca era 0
//Servo myservo;
//Servo garaj;
#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);
//DHT dht2(DHT2PIN, DHTTYPE);
//int fanPin = D4;
//Define FirebaseESP8266 data object
FirebaseData firebaseData;
//FirebaseData firebaseData2;
FirebaseData ledData;
FirebaseData radiatorData;
//FirebaseData parterData;
FirebaseData afaraData;
//FirebaseData subsolData;
//FirebaseData Et1Data;
//FirebaseData Et2Data;
//FirebaseData poartaData;
//FirebaseData usaData;
FirebaseJson json;
float temperature;
//OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature sensors(&oneWire);


void setup()
{
  analogWrite(D1,1023);
  //!!!!!!!!!!!Posibila problema
  //asta e pus nou !!!!!  sensors.begin();
  //
 // pinMode(led, OUTPUT);
  Serial.begin(9600);
  //dht2.begin();
    //dht.begin();
  pinMode(led,OUTPUT);
  pinMode(radiator,OUTPUT);
  pinMode(parter,OUTPUT);
  pinMode(afara,OUTPUT);
 pinMode(Et1,OUTPUT);
  pinMode(Et2,OUTPUT);
  pinMode(subsol,OUTPUT);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");

    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);}
  void loop(){
  // Wait for a bit before checking the temperature again
  //delay(1000);
  if (Firebase.getString(ledData, "/FirebaseIOT/led")){
    Serial.println(ledData.stringData());
    
    if (ledData.stringData() == "1") {
    digitalWrite(led, HIGH);
    Serial.println("ghgh");
    }
  else if (ledData.stringData() == "0"){
    digitalWrite(led, LOW);
    Serial.println("tyyrtr");
    }
  }if (Firebase.getString(radiatorData, "/FirebaseIOT/radiator")){
    Serial.println(radiatorData.stringData());
    
    if (radiatorData.stringData() == "1") {
    digitalWrite(radiator, HIGH);
    Serial.println("muuuu");
    }
  else if (radiatorData.stringData() == "0"){
    digitalWrite(radiator, LOW);
    Serial.println("arrrrr");
    }}
    if (Firebase.getString(ledData, "/FirebaseIOT/parter")){
    Serial.println(ledData.stringData());
    
    if (ledData.stringData() == "1") {
    digitalWrite(parter, HIGH);
    Serial.println("sssss");
    }
  else if (ledData.stringData() == "0"){
    digitalWrite(parter, LOW);
    Serial.println("ccccccc");
    }}
    if (Firebase.getString(ledData, "/FirebaseIOT/Et1")){
    Serial.println(ledData.stringData());
    
    if (ledData.stringData() == "1") {
    digitalWrite(Et1, HIGH);
    Serial.println("sssss");
    }
  else if (ledData.stringData() == "0"){
    digitalWrite(Et1, LOW);
    Serial.println("ccccccc");
    }}
     if (Firebase.getString(ledData, "/FirebaseIOT/Et2")){
    Serial.println(ledData.stringData());
    
    if (ledData.stringData() == "1") {
    digitalWrite(Et2, HIGH);
    Serial.println("sssss");
    }
  else if (ledData.stringData() == "0"){
    digitalWrite(Et2, LOW);
    Serial.println("ccccccc");
    }}
     if (Firebase.getString(ledData, "/FirebaseIOT/subsol")){
    Serial.println(ledData.stringData());
    
    if (ledData.stringData() == "1") {
    digitalWrite(subsol, HIGH);
    Serial.println("sssss");
    }
  else if (ledData.stringData() == "0"){
    digitalWrite(subsol, LOW);
    Serial.println("ccccccc");
    }}
    
    if (Firebase.getString(afaraData, "/FirebaseIOT/afara")){
    Serial.println(afaraData.stringData());
    
    if (afaraData.stringData() == "1") {
    digitalWrite(afara, HIGH);
    Serial.println("qqqqqq");
    }
  else if (afaraData.stringData() == "0"){
    digitalWrite(afara, LOW);
    Serial.println("pppppp");
    }
  }}
