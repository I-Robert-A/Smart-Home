
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
#define DHTPIN D3// Connect Data pin of DHT to D2
int led = D4;     // Connect LED to D5
int x;
//int buzzer=D5;
//int sens;
//int yx;
//int xx;
//int kk;
//int ll;
//int Senz=D6;
int m1=D7;
int m2=D8;
//int i,k=0,r=0,p=1,k1=0,d,r1,r2,r3,r4;
int l=0;
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
FirebaseData poartaData;
//FirebaseData usaData;
FirebaseJson json;
float temperature;
//OneWire oneWire(ONE_WIRE_BUS);
//DallasTemperature sensors(&oneWire);

void sensorUpdate(){
float h = dht.readHumidity();
 
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("C  ,"));
  Serial.print(f);
  Serial.println(F("F  "));
if (Firebase.setFloat(firebaseData, "/FirebaseIOT/temperature", t))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }

  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/humidity", h))
  {
    Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.println("------------------------------------");
    Serial.println();
  }
  else
  {
    Serial.println("FAILED");
    Serial.println("REASON: " + firebaseData.errorReason());
    Serial.println("------------------------------------");
    Serial.println();
  }
}
void setup()
{
  analogWrite(D1,1023);
  //!!!!!!!!!!!Posibila problema
  //asta e pus nou !!!!!  sensors.begin();
  //
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  //dht2.begin();
    dht.begin();
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
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
  Firebase.reconnectWiFi(true);
}

  // Wait for a bit before checking the temperature again
  //delay(1000);
 void loop(){
   sensorUpdate();
   float t = dht.readTemperature();
   Serial.println(t);
   if(Firebase.getString(firebaseData, "/FirebaseIOT/temp")){
    if(strchr("0123456789",firebaseData.stringData()[3])==0){
      x=int(firebaseData.stringData()[2])-48;
    }
    else{
     x=int(firebaseData.stringData()[2])-48;
     x=x*10;
     x=x+int(firebaseData.stringData()[3])-48;
   }}
   Serial.println(x);
   if(x<t){
    digitalWrite(led,HIGH);
   }
   else{digitalWrite(led,LOW);
 //realizarea comunicarii dintre Firebase si motorul servo si motorul DC
  if (Firebase.getString(poartaData, "/FirebaseIOT/poarta")){
    Serial.println(poartaData.stringData());
    
    if (poartaData.stringData() == "1" && l==0) {
    Deschis();
    Serial.println("Poarta on");
    delay(3000);
    Stop();
    }
  else if (poartaData.stringData() == "0" && l==1){
    Inchis();
    Serial.println("Poarta off");
    delay(3000);
    Stop();
    }
  }}}
  
 void Deschis(){
    digitalWrite(m1,HIGH);
    digitalWrite(m2,LOW);
    l=1;
    }
    void Inchis(){
      digitalWrite(m1,LOW);
      digitalWrite(m2,HIGH);
      l=0;
    }
    void Stop(){
      digitalWrite(m1,LOW);
      digitalWrite(m2,LOW);    
    }
