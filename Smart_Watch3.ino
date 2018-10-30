/*

Ricardo Mena C
ricardo@crcibernetica.com
http://crcibernetica.com

  This example code is in public domain

*/
#include<math.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <Nextion.h>
#include <MicroGear.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
boolean button1State;
boolean button2State;
//Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps

extern "C" {
#include "user_interface.h"
}
ESP8266WebServer server(80);

#include <EEPROM.h>
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
SoftwareSerial nextion(4, 5);// Nextion TX to pin D1 and RX to pin D2 of Arduino
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>.
  // Time code 
unsigned long timeNow = 0;

unsigned long timeLast = 0;

//Time start Settings:

int startingHour = 12;

// set your starting hour here, not below at int hour. This ensures accurate daily correction of time

int seconds = 0;

int minutes = 33;

int hours = startingHour;

int days = 0;

//Accuracy settings

int dailyErrorFast = 0; // set the average number of milliseconds your microcontroller's time is fast on a daily basis

int dailyErrorBehind = 0; // set the average number of milliseconds your microcontroller's time is behind on a daily basis

int correctedToday = 1; // do not change this variable, one means that the time has already been corrected today for the error in your boards crystal. This is true for the first day because you just set the time when you uploaded the sketch.
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
Nextion myNextion(nextion, 9600); //create a Nextion object named myNextion using the nextion serial port @ 9600bps
int i; 
boolean screenOff = true;
//boolean button1State;
const char* ssid1     = "true_home2G_XWX";// User 
const char* password1 = "Ag9y2876";  // The passwaord converter 
const char* ssid = "AndroidAP";
const char* password = "uknu0822";
#define APPID   "Kornbot"
#define KEY     "wBHqON1EtNqlTzu"
#define SECRET  "nt0utSlDrPEOiYOFFfHYJDbEw"

#define ALIAS   "NodeMCU1"
#define TagetWeb "VisualStudio"
WiFiClient client;
MicroGear microgear(client);

void onMsghandler(char *topic, uint8_t* msg, unsigned int msglen) 
{
  Serial.print("Incoming message --> ");
  Serial.print(topic);
  Serial.print(" : ");
  char strState[msglen];
  for (int i = 0; i < msglen; i++) 
  {
    strState[i] = (char)msg[i];
    Serial.print((char)msg[i]);
  }
 
  String stateStr = String(strState).substring(0, msglen);
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>...
  //LED testing recieve the command function d
    myNextion.setComponentText("g0",stateStr);
      
  if(stateStr == "LivingON") 
  {
   // digitalWrite(MotorL1, OFF);
    String message = myNextion.listen(); //check for message
    message = "68";
   myNextion.sendCommand("screenOff=0"); 
   int bright = map(700, 0, 1024, 0, 100);
  String dim = "dim=" + String(bright);
  myNextion.sendCommand(dim.c_str());
    microgear.chat(TagetWeb, "Living room light on ");
    myNextion.setComponentText("t8", "Living Room");
 delay(500); 
  myNextion.setComponentText("t8", "Light Off");
delay(500); 
 myNextion.setComponentText("t8", " sir");
  } 
  else if (stateStr == "LivingOFF") 
  {
//   digitalWrite(MotorL1, ON);
  // digitalWrite(MotorL1, OFF);
    String message = myNextion.listen(); //check for message
    message = "68"; 
myNextion.sendCommand("screenOff=1"); 
  int bright = map(700, 0, 1024, 0, 100);
  String dim = "dim=" + String(bright);
  myNextion.sendCommand(dim.c_str());
microgear.chat(TagetWeb, "Living rooom light off");
 myNextion.setComponentText("t8", "Living Room");
 delay(500); 
  myNextion.setComponentText("t8", "Light ON");
delay(500); 
 myNextion.setComponentText("t8", " sir");
 delay(500); 
  myNextion.setComponentText("t8", "News");
delay(500); 
   
  }
   if(stateStr == "Remote") 
  {
    // digitalWrite(MotorL1, OFF);
   int bright = map(700, 0, 1024, 0, 100);
  String dim = "dim=" + String(bright);
  myNextion.sendCommand(dim.c_str());
    microgear.chat(TagetWeb, "Remote Swarmbot ");
    myNextion.setComponentText("t8", "Swamr intelligence");
 delay(500); 
  myNextion.setComponentText("t8", "Online");
delay(500); 
 myNextion.setComponentText("t8", " sir");
  }
  else if (stateStr == "FailCon") 
  {
    // digitalWrite(MotorL1, OFF);
   int bright = map(700, 0, 1024, 0, 100);
  String dim = "dim=" + String(bright);
  myNextion.sendCommand(dim.c_str());
    microgear.chat(TagetWeb, "Fail connection swarm ");
    myNextion.setComponentText("t8", "I'm  trying to reconnect swarmbot function");
 delay(500); 
  myNextion.setComponentText("t8", "Swarm offline");
delay(500); 
 myNextion.setComponentText("t8", " sir");
    
  }
 if(stateStr == "Midnight")
 {
    int bright = map(700, 0, 1024, 0, 100);
  String dim = "dim=" + String(bright);
  myNextion.sendCommand(dim.c_str());
    microgear.chat(TagetWeb, "Midnight");
    myNextion.setComponentText("t8", "Midnight Now");
 delay(500); 
  myNextion.setComponentText("t8", "Relax");
delay(500); 
 myNextion.setComponentText("t8", " sir");
 }
 if(stateStr == "Goodmorning")
 {
   int bright = map(700, 0, 1024, 0, 100);
  String dim = "dim=" + String(bright);
  myNextion.sendCommand(dim.c_str());
    microgear.chat(TagetWeb, "Good morning sir ");
    myNextion.setComponentText("t8", stateStr);
  
 delay(500); 
  myNextion.setComponentText("t8", "Having breakfast");
delay(500); 
 myNextion.setComponentText("t8", " sir");
 }
 if(stateStr == "Goodnoon")
 {
   int bright = map(700, 0, 1024, 0, 100);
  String dim = "dim=" + String(bright);
  myNextion.sendCommand(dim.c_str());
    microgear.chat(TagetWeb, "Goodnoon sir");
    myNextion.setComponentText("t8", "Good noon");
 delay(500); 
  myNextion.setComponentText("t8", "Having lunch");
delay(500); 
 myNextion.setComponentText("t8", " sir");
 }
 if(stateStr == "Goodnight") 
 {
   int bright = map(700, 0, 1024, 0, 100);
  String dim = "dim=" + String(bright);
  myNextion.sendCommand(dim.c_str());
    microgear.chat(TagetWeb, "Good night ");
    myNextion.setComponentText("t8", "Are you ");
 delay(500); 
  myNextion.setComponentText("t8", "Going to");
delay(500); 
 myNextion.setComponentText("t8", " Sleep");
 delay(500); 
 myNextion.setComponentText("t8","yet ?");
 }
 if(stateStr == "Goodevning") 
 {
   myNextion.sendCommand("screenOff=0"); 
   int bright = map(700, 0, 1024, 0, 100);
  String dim = "dim=" + String(bright);
  myNextion.sendCommand(dim.c_str());
    microgear.chat(TagetWeb, "Goodevening sir ");
    myNextion.setComponentText("t8", "Good evening ");
 delay(500); 
  myNextion.setComponentText("t8", "sir");
delay(500); 
 myNextion.setComponentText("t8", " News");
 
 }
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
 
}

void onConnected(char *attribute, uint8_t* msg, unsigned int msglen) 
{
  Serial.println("Connected to NETPIE...");
  microgear.setAlias(ALIAS);
}

void onFoundgear(char *attribute, uint8_t* msg, unsigned int msglen) 
{
    Serial.print("Found new member --> ");
    for (int i=0; i<msglen; i++)
    {
        Serial.print((char)msg[i]);
    }
    Serial.println();  
}

void onLostgear(char *attribute, uint8_t* msg, unsigned int msglen) 
{
    Serial.print("Lost member --> ");
    for (int i=0; i<msglen; i++)
    {
      Serial.print((char)msg[i]);
    }
    Serial.println();
}

void setup() {
  Serial.begin(9600);
   WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  Serial.println("Setup done");
   myNextion.setComponentText("g0","Setup Data");
  myNextion.init(); // send the initialization commands for Page 0
  /* Event listener */
    microgear.on(MESSAGE,onMsghandler);
    microgear.on(PRESENT,onFoundgear);
    microgear.on(ABSENT,onLostgear);
    microgear.on(CONNECTED,onConnected);
 

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
       delay(250);
       Serial.print(".");
    }

    Serial.println("WiFi connected");  
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
   
    //uncomment the line below if you want to reset token -->
    microgear.init(KEY,SECRET,ALIAS);
    microgear.connect(APPID);
}

void loop() {
   
  if(screenOff){
    screenOff = false;
    myNextion.sendCommand("sleep=1");
    delay(1500);
  int bright = map(700, 0, 1024, 0, 100);
  String dim = "dim=" + String(bright);
  myNextion.sendCommand(dim.c_str());
      WiBBconnect();
    
  }
  
  String message = myNextion.listen(); //check for message
  if(message.startsWith("68")){
    myNextion.sendCommand("sleep=0");
   while (screenOff = true) 
   {
     WiBBconnect();
   
   for( i = 700 ; i <=1024;i+=1) {
     myNextion.setComponentText("t0",String(i));
      if (message == "65 0 2 0 ffff ffff ffff") {
    myNextion.buttonToggle(button1State, "t1", 0, 2);
    myNextion.setComponentText("g0","Button hit");
  }
  if(screenOff = true)
  {
  WiBBconnect();
 
  }
  if(i == 700) 
  {
  Displayword();
 // String message = myNextion.listen(); //check for message
 
  }
  if(i == 740) 
  {
 
  int bright = map(200, 0, 740, 0, 100);
  String dim = "dim=" + String(bright);
  myNextion.sendCommand(dim.c_str());  
  }
   }  
  }
 }
}
void TimeDis() 
{
  timeNow = millis()/1000; // the number of milliseconds that have passed since boot

seconds = timeNow - timeLast;

//the number of seconds that have passed since the last time 60 seconds was reached.

if (seconds == 60) {

timeLast = timeNow;

minutes = minutes + 1; }

//if one minute has passed, start counting milliseconds from zero again and add one minute to the clock.

if (minutes == 60){

minutes = 0;

hours = hours + 1; }



// if one hour has passed, start counting minutes from zero and add one hour to the clock



if (hours == 24){

hours = 0;

days = days + 1;

}

//if 24 hours have passed, add one day

if (hours ==(24 - startingHour) && correctedToday == 0){

delay(dailyErrorFast*1000);

seconds = seconds + dailyErrorBehind;

correctedToday = 1; }

//every time 24 hours have passed since the initial starting time and it has not been reset this day before, add milliseconds or delay the program with some milliseconds.

//Change these varialbes according to the error of your board.

// The only way to find out how far off your boards internal clock is, is by uploading this sketch at exactly the same time as the real time, letting it run for a few days

// and then determining how many seconds slow/fast your boards internal clock is on a daily average. (24 hours).

if (hours == 24 - startingHour + 2) {

correctedToday = 0; }

//let the sketch know that a new day has started for what concerns correction, if this line was not here the arduiono // would continue to correct for an entire hour that is 24 - startingHour.

Serial.print("The time is: ");

Serial.print(days);

Serial.print(":");

Serial.print(hours);

Serial.print(":");

Serial.print(minutes);

Serial.print(":");

Serial.println(seconds);
//String Time = String(days) +String(:)+String(hours)+String(:)+String(minutes)+String(:)+String(seconds);
myNextion.setComponentText("t5",String(hours));

myNextion.setComponentText("t6",String(minutes));

myNextion.setComponentText("t7",String(seconds));
}
void WiBBconnect() 
{
  if(microgear.connected()) 
  {
   
    microgear.loop();
    Serial.println("Sentient Robotics netwok");
    Serial.println("connected...");
    microgear.chat(TagetWeb,"Smart watch online");
    myNextion.setComponentText("t8","Connected");
    delay(500); 
    myNextion.setComponentText("t8","WiFi");
    
    int Analog = analogRead(A0); 
    microgear.chat(TagetWeb,Analog); 
  }
  else 
  {
    Serial.println("connection lost, reconnect...");
    microgear.connect(APPID);
    myNextion.setComponentText("t8","Fail conn");
   // scann();
  }
  delay(250);
}
void Displayword() 
{
    myNextion.setComponentText("t8", "Hello sir");
     delay(500); 
  
     TimeDis();
     myNextion.setComponentText("t1", "Health care");
     delay(500); 
     myNextion.setComponentText("t1", "you can check your healthy here");
     delay(500); 
     myNextion.setComponentText("t1", "Health care");
     delay(500); 
    myNextion.setComponentText("t3", "Control your Vihicles");
     delay(500); 
    myNextion.setComponentText("t3", "Automobil");
     delay(500); 
    myNextion.setComponentText("t4", "Control swarm robots");
     delay(500); 
     myNextion.setComponentText("t4", "example");
     delay(500); 
     myNextion.setComponentText("t4", "Drone, Smartbot");
     delay(500); 
     myNextion.setComponentText("t4", "Swarm Intelligence");
     delay(500); 
     myNextion.setComponentText("t2", "Control your home");
     delay(500); 
     myNextion.setComponentText("t2", "example");
     delay(500); 
     myNextion.setComponentText("t2", "lightbulp and electrical devices");
     delay(500); 
     myNextion.setComponentText("t2", "Home Automation");
     delay(500);     
     myNextion.setComponentText("t8", "If there is a news");
     delay(500); 
     myNextion.setComponentText("t8", "You need to know ");
     delay(500); 
     myNextion.setComponentText("t8", "I will");
     delay(500); 
     myNextion.setComponentText("t8","tell you");
     delay(500);     
    myNextion.setComponentText("t8", "Friday A.I.");
     delay(500);      
     myNextion.setComponentText("t8", "Your Smart");
     delay(500); 
     myNextion.setComponentText("t8", "Watch");
     delay(500); 
      myNextion.setComponentText("t8", "News");
     delay(500);
      scann();
     
}
void scann()
{
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0)
    Serial.println("no networks found");
  else
  {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i)
    {
      // Print SSID and RSSI for each network found
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
    myNextion.setComponentText("g0",String(WiFi.SSID(i))+String(WiFi.RSSI(i)));
  
   
     delay(300);
      Serial.print(" (");
      Serial.print(WiFi.RSSI(i));
      if(WiFi.RSSI(i) <-60) 
      {
         myNextion.setComponentText("g0","Far signal"+String(WiFi.RSSI(i))+String(WiFi.SSID(i))); 
         delay(10); 
        myNextion.setComponentText("g0",String(DistanceHomeCalt(WiFi.RSSI(i)))+String("meter")+String(WiFi.SSID(i))); // Distance calculation function
        microgear.chat(TagetWeb,String(DistanceHomeCalt(WiFi.RSSI(i)))+String("meter")+String(WiFi.SSID(i))); // Sending the message to the Friday A.I. for measure and calculate everything 
      }
 //   myNextion.setComponentText("g0",String(WiFi.RSSI(i))); 
    // delay(500);
      Serial.print(")");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*");
    //myNextion.setComponentText("g0",String((WiFi.encryptionType(i) == ENC_TYPE_NONE)?" ":"*")); 

    //  delay(5000);
    }
  }
  Serial.println("");
}
float DistanceHomeCalt(float RSSIT)  // the function of the Distance calcultion function  
{
  float  d ; // The outout distance calculation 
  float n = 2.0; // The signal exponent in the freespace = 2 
  float Do = 1;  // The reference distance is 1 meter  
  //float Px = ((RSSIT/20)- log(32*3.14)); //The function of the px of 
  d =  10*pow(10,abs(RSSIT/20) -log(100.48)); // The distance calculation of the function on the wifi signal 
  return(d);// return the float value back into the function of the distance display 
}

