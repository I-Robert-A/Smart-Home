

//Initializarea librariilor folosite pentru comunicarea cu diferite componente hardware
#include "FirebaseESP8266.h"  // Instaleaza libraria Firebase pentru ESP8266
#include <DHT.h>    // Instaleaza libraria DHT11 si libraria de senzor Adafruit Unified
#include <Servo.h>  //Instaleaza libraria folosita pentru motorul servo
#include <OneWire.h>
#include <Arduino.h>
#if defined(ESP32) || defined(ARDUINO_RASPBERRY_PI_PICO_W)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#else

// Other Client defined here
// To use custom Client, define ENABLE_CUSTOM_CLIENT in src/ESP_Mail_FS.h.
// See the example Custom_Client.ino for how to use.

#endif

#include <ESP_Mail_Client.h>
//realizarea conexiunii cu Firebase
#define FIREBASE_HOST "fir-iot-27cf7-default-rtdb.firebaseio.com" //Without http:// or https:// schemes
#define FIREBASE_AUTH "nOkf5M1wQJElXDAUoOzR4YWeq1S5K90vzZhntZKV"
#define WIFI_SSID "DIGI-01024552"
#define WIFI_PASSWORD "YEhi8I3I"
#define ONE_WIRE_BUS D2 
#define DHT2PIN 0//declararea senzorului DHT
#define SMTP_HOST "smtp.gmail.com"
#define SMTP_PORT esp_mail_smtp_port_587 // port 465 is not available for Outlook.com
#define AUTHOR_EMAIL "tesstr14@gmail.com"
#define AUTHOR_PASSWORD "tfbsmfbwzdtjejny"
SMTPSession smtp;

//declararea variabilelor
int buzzer=D5;
int sens;
int yx;
int xx;
int kk;
int ll;
int Senz=D6;
int m1=D7;
int m2=D8;
int i,k=0,r=0,p=1,k1=0,d,r1,r2,r3,r4;
int l=0;
//declararea motoarelor servo
Servo myservo;
Servo garaj;
#define DHTTYPE    DHT11
//DHT dht(DHTPIN, DHTTYPE);
DHT dht2(DHT2PIN, DHTTYPE);
int fanPin = D4;
FirebaseData firebaseData;
FirebaseData usaData;
FirebaseJson json;
float temperature;
OneWire oneWire(ONE_WIRE_BUS);
#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif


void setup()
{kk=0;
ll=0;
  analogWrite(D1,1023);
  //declararea tipurilor de date ale variabilelor, OUTPUT sau INPUT
  pinMode(Senz, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(fanPin, OUTPUT);
  digitalWrite(fanPin, LOW);
  Serial.begin(9600);
  dht2.begin();//pornirea senzorului DHT
  pinMode(m1,OUTPUT);
  pinMode(m2,OUTPUT);
  //atasarea motoarelor la pini
  myservo.attach(D0);
  garaj.attach(D1,900,2500);
  //conectarea la WIFI
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

void sensorUpdate(){
   
  float h2=dht2.readHumidity();
  //citeste umiditatea de la senzorul DHT
  
  float t2=dht2.readTemperature();
  //citeste temperatura de la senzorul DHT in grade Celsius

  float f2=dht2.readTemperature(true);
  //citeste temperatura de la senzorul DHT in grade Fahrenheit
  
 // verifica daca vreo citire a esuat si se opreste mai devreme
  if(isnan(h2) || isnan(t2) || isnan(f2)){
    Serial.println(F("Failed to read from exterior DHT sensor!"));
    return;
  }
//afisarea datelor de la senzor in Serial Monitor
 Serial.print(F("Humidity: "));
  Serial.print(h2);
  Serial.print(F("%  Temperature: "));
  Serial.print(t2);
  Serial.print(F("C  ,"));
  Serial.print(f2);
  Serial.println(F("F  "));
  //realizarea comunicarii dintre senzorul DHT11 si Firebase
   if (Firebase.setFloat(firebaseData, "/FirebaseIOT/temp", temperature))
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
  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/temperatureE", t2))
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

  if (Firebase.setFloat(firebaseData, "/FirebaseIOT/humidityE", h2))
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
void loop() {
   Sonerie();
  sensorUpdate();
  Sonerie();
 //realizarea comunicarii dintre Firebase si motorul servo al usii garajului, iar in cazul in care aceeasi comanda nu este introdusa de doua ori la rand va executa actiunea corespunzatoare
  Sonerie();
   if (Firebase.getString(usaData, "/FirebaseIOT/usa")){
    Serial.println(usaData.stringData());
    if(usaData.stringData() == "0" && k==1){
        garaj.writeMicroseconds(900);
      k=0;
      k1=0;
      Serial.println("garajOFF");
   }
    else if (usaData.stringData() == "1"  && k==0) {
    garaj.writeMicroseconds(2500);
    k++;
    Serial.println("garajON");
    }}
    Sonerie();
    //programul pentru deschiderea usii prin intermediul unui cod ce este furnizat de catre aplicatia MIT App Inventor prin intermediul Firebase
    if (Firebase.getString(usaData, "/FirebaseIOT/cod"))
    { d=0;
                  if(usaData.stringData() == "1")
                  {Serial.println("cod");
                  r1=0;
                  r2=0;
                  r3=0;
                  r4=0;
  Sonerie();    
  while(d<100){
  if (Firebase.getString(usaData, "/FirebaseIOT/unu"))
  {
    Serial.println(usaData.stringData());
    if (usaData.stringData() == "1") 
    {
      r1=1;
      Serial.println("unu");
    }
  }
  else{r1=0;}
    Sonerie();
  if (Firebase.getString(usaData, "/FirebaseIOT/doi"))
  {Serial.println(usaData.stringData());
    if(usaData.stringData() == "1"){
      r2=1;
            Serial.println("doi");}
       }else{r2=0;}
             if (Firebase.getString(usaData, "/FirebaseIOT/trei")){
              Serial.println(usaData.stringData());
              if(usaData.stringData() =="1"){
                r3=1;
                Serial.println("trei");}
             }else{r3=0;}
                if (Firebase.getString(usaData, "/FirebaseIOT/patru")){
                  Serial.println(usaData.stringData());
                    if(usaData.stringData() =="1"){
                      r4=1;
                      Serial.println("patru");}
                }else{r4=0;}
                         if (Firebase.getString(usaData, "/FirebaseIOT/enter")){
                          Serial.println(usaData.stringData());
                          Serial.println("r");
                                  Serial.println(r);
                             if(usaData.stringData() =="1"){
                              d=100;
                             if(r1==1 && r2==1 && r3==1 && r4==1){//in momentul introducerii codului corect usa se deschide
                               for(i=0;i<=180;i++){
                               r4=0;
                                  myservo.write(i);}
                                  Serial.println("usaON");
                               delay(5000);
                               for(i=180;i>=0;i--){
                              myservo.write(i);}
                              k1++;
                              p=0;}}}
  
  delay(100);
  d++;
  Serial.println("uuuu");
  Serial.println(d);
    }}
}Sonerie();}
void smtpCallback(SMTP_Status status)
{
  /* Print the current status */
  Serial.println(status.info());

  /* Print the sending result */
  if (status.success())
  {
    // ESP_MAIL_PRINTF used in the examples is for format printing via debug Serial port
    // that works for all supported Arduino platform SDKs e.g. AVR, SAMD, ESP32 and ESP8266.
    // In ESP8266 and ESP32, you can use Serial.printf directly.

    Serial.println("----------------");
    ESP_MAIL_PRINTF("Message sent success: %d\n", status.completedCount());
    ESP_MAIL_PRINTF("Message sent failed: %d\n", status.failedCount());
    Serial.println("----------------\n");

    for (size_t i = 0; i < smtp.sendingResult.size(); i++)
    {
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);

      // In case, ESP32, ESP8266 and SAMD device, the timestamp get from result.timestamp should be valid if
      // your device time was synched with NTP server.
      // Other devices may show invalid timestamp as the device time was not set i.e. it will show Jan 1, 1970.
      // You can call smtp.setSystemTime(xxx) to set device time manually. Where xxx is timestamp (seconds since Jan 1, 1970)
      time_t ts = (time_t)result.timestamp;

      ESP_MAIL_PRINTF("Message No: %d\n", i + 1);
      ESP_MAIL_PRINTF("Status: %s\n", result.completed ? "success" : "failed");
      ESP_MAIL_PRINTF("Date/Time: %s\n", asctime(localtime(&ts)));
      ESP_MAIL_PRINTF("Recipient: %s\n", result.recipients.c_str());
      ESP_MAIL_PRINTF("Subject: %s\n", result.subject.c_str());
    }
    Serial.println("----------------\n");

    // You need to clear sending result as the memory usage will grow up.
    smtp.sendingResult.clear();
  }
}
//Functie pentru alarma in cazul unei intrari prin efractie
void Sonerie(){
   if(sens==LOW){
    Serial.println("vede");
        yx=1;
      }
  xx=1;
  sens=digitalRead(Senz);
     if (Firebase.getString(usaData, "/FirebaseIOT/STOP")){    
                if(usaData.stringData()=="0"){
                xx=0;
                }
                else{xx=1;
                yx=0;}
            }  
            Serial.println("ssdfssfsfdsfs");
            Serial.println(yx);
        if(yx==1){
        if (Firebase.getString(usaData, "/FirebaseIOT/alarma")){ 
          yx=0;       
        if(usaData.stringData()=="1"){ 
          MailClient.networkReconnect(true);
smtp.debug(1);

  /* Set the callback function to get the sending results */
  smtp.callback(smtpCallback);

  /* Declare the Session_Config for user defined session credentials */
  Session_Config config;

  /* Set the session config */
  config.server.host_name = SMTP_HOST;
  config.server.port = SMTP_PORT;
  config.login.email = AUTHOR_EMAIL;
  config.login.password = AUTHOR_PASSWORD;

  /** Assign your host name or you public IPv4 or IPv6 only
   * as this is the part of EHLO/HELO command to identify the client system
   * to prevent connection rejection.
   * If host name or public IP is not available, ignore this or
   * use generic host "mydomain.net".
   *
   * Assign any text to this option may cause the connection rejection.
   */
  config.login.user_domain = F("mydomain.net");

  /* Set the NTP config time */
  config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
  config.time.gmt_offset = 3;
  config.time.day_light_offset = 0;

  /* The full message sending logs can now save to file */
  /* Since v3.0.4, the sent logs stored in smtp.sendingResult will store only the latest message logs */
  // config.sentLogs.filename = "/path/to/log/file";
  // config.sentLogs.storage_type = esp_mail_file_storage_type_flash;

  /** In ESP32, timezone environment will not keep after wake up boot from sleep.
   * The local time will equal to GMT time.
   *
   * To sync or set time with NTP server with the valid local time after wake up boot,
   * set both gmt and day light offsets to 0 and assign the timezone environment string e.g.

     config.time.ntp_server = F("pool.ntp.org,time.nist.gov");
     config.time.gmt_offset = 0;
     config.time.day_light_offset = 0;
     config.time.timezone_env_string = "JST-9"; // for Tokyo

   * The library will get (sync) the time from NTP server without GMT time offset adjustment
   * and set the timezone environment variable later.
   *
   * This timezone environment string will be stored to flash or SD file named "/tze.txt"
   * which set via config.time.timezone_file.
   *
   * See the timezone environment string list from
   * https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
   *
   */

  /* Declare the message class */
  SMTP_Message message;

  /* Set the message headers */
  message.sender.name = "Iohannis"; // This witll be used with 'MAIL FROM' command and 'From' header field.
  message.sender.email = AUTHOR_EMAIL; // This witll be used with 'From' header field.
  message.subject = F("Test sending plain text Email");
  message.addRecipient("tine", "andreea.duca@cncn.ro"); // This will be used with RCPT TO command and 'To' header field.

  String textMsg = "Sunt tu din viitor";
  message.text.content = textMsg;

  /** If the message to send is a large string, to reduce the memory used from internal copying  while sending,
   * you can assign string to message.text.blob by cast your string to uint8_t array like this
   *
   * String myBigString = "..... ......";
   * message.text.blob.data = (uint8_t *)myBigString.c_str();
   * message.text.blob.size = myBigString.length();
   *
   * or assign string to message.text.nonCopyContent, like this
   *
   * message.text.nonCopyContent = myBigString.c_str();
   *
   * Only base64 encoding is supported for content transfer encoding in this case.
   */

  /** The Plain text message character set e.g.
   * us-ascii
   * utf-8
   * utf-7
   * The default value is utf-8
   */
  message.text.charSet = F("us-ascii");

  /** The content transfer encoding e.g.
   * enc_7bit or "7bit" (not encoded)
   * enc_qp or "quoted-printable" (encoded)
   * enc_base64 or "base64" (encoded)
   * enc_binary or "binary" (not encoded)
   * enc_8bit or "8bit" (not encoded)
   * The default value is "7bit"
   */
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  // If this is a reply message
  // message.in_reply_to = "<parent message id>";
  // message.references = "<parent references> <parent message id>";

  /** The message priority
   * esp_mail_smtp_priority_high or 1
   * esp_mail_smtp_priority_normal or 3
   * esp_mail_smtp_priority_low or 5
   * The default value is esp_mail_smtp_priority_low
   */
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_low;

  // message.response.reply_to = "someone@somemail.com";
  // message.response.return_path = "someone@somemail.com";

  /** The Delivery Status Notifications e.g.
   * esp_mail_smtp_notify_never
   * esp_mail_smtp_notify_success
   * esp_mail_smtp_notify_failure
   * esp_mail_smtp_notify_delay
   * The default value is esp_mail_smtp_notify_never
   */
  // message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;

  /* Set the custom message header */
  message.addHeader(F("Message-ID: <abcde.fghij@gmail.com>"));

  // For Root CA certificate verification (ESP8266 and ESP32 only)
  // config.certificate.cert_data = rootCACert;
  // or
  // config.certificate.cert_file = "/path/to/der/file";
  // config.certificate.cert_file_storage_type = esp_mail_file_storage_type_flash; // esp_mail_file_storage_type_sd
  // config.certificate.verify = true;

  // The WiFiNINA firmware the Root CA certification can be added via the option in Firmware update tool in Arduino IDE

  /* Connect to server with the session config */

  // Library will be trying to sync the time with NTP server if time is never sync or set.
  // This is 10 seconds blocking process.
  // If time synching was timed out, the error "NTP server time synching timed out" will show via debug and callback function.
  // You can manually sync time by yourself with NTP library or calling configTime in ESP32 and ESP8266.
  // Time can be set manually with provided timestamp to function smtp.setSystemTime.

  /* Connect to the server */
  if (!smtp.connect(&config))
    return;

  if (smtp.isAuthenticated())
    Serial.println("Successfully logged in.");
  else
    Serial.println("Connected with no Auth.");

  /* Start sending Email and close the session */
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());

  // to clear sending result log
  // smtp.sendingResult.clear();

  ESP_MAIL_PRINTF("Free Heap: %d\n", MailClient.getFreeHeap());
  void smtpCallback(SMTP_Status status);
          yx=0;   
                Serial.println("armat");
                Serial.println(sens);
                   while(xx==0){  
                    yx=0;
                    if (Firebase.getString(usaData, "/FirebaseIOT/STOP")){    
                if(usaData.stringData()=="0"){
                xx=0;
                }
                else{xx=1;
                yx=0;
                Serial.println("ggggggggg");}
            }//while
            yx=0;
                      Serial.println("miscare");
                      Serial.println("asasasasasas");
                         tone(buzzer, 820);
                         delay(100);
                         tone(buzzer, 1000);
                         //noTone(buzzer);
  }
  noTone(buzzer);
  }}}
}
