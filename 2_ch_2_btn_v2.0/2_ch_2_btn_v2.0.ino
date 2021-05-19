/* This is physical switch v2.1 
 *  last update on 19 May 2021
 *  Tested & working fine   lasted on 19 May 2021 9:00 pm
 *  2 channel relay & 2 Button
 *  last upload on box switch
 */


#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
char auth[] = "unique Code here";

char ssid[] = "ssid";           // WiFi SSID.
char pass[] = "password";         //  Wifi password

// Set your LED and physical button pins here
const int relayPin2 = 12;
const int relayPin1 = 13;
//============================//
const int btnPin1 = 5;
const int btnPin2 = 4;

//===========================//

BlynkTimer timer;
void checkPhysicalButton();

int relay1State = LOW;
int btn1State = HIGH;

int relay2State = LOW;
int btn2State = HIGH;

// Every time we connect to the cloud...
BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(V12);
  Blynk.syncVirtual(V13);
  Blynk.syncVirtual(V14);
  Blynk.syncVirtual(V15);  
}

// When App button is pushed - switch the state
BLYNK_WRITE(V12) {
  relay1State = param.asInt();
  digitalWrite(relayPin1, relay1State);
}
  
 BLYNK_WRITE(V13) {
  relay2State = param.asInt();
  digitalWrite(relayPin2, relay2State);
 }

void checkPhysicalButton()
{
  if (digitalRead(btnPin1) == LOW) {
    // btn1State is used to avoid sequential toggles
    if (btn1State != LOW) {

      // Toggle LED state
      relay1State = !relay1State;
      digitalWrite(relayPin1, relay1State);

      // Update Button Widget
      Blynk.virtualWrite(V12, relay1State);
    }
    btn1State = LOW;
  } else {
    btn1State = HIGH;
  }

  if (digitalRead(btnPin2) == LOW) {
    // btnState is used to avoid sequential toggles
    if (btn2State != LOW) {

      // Toggle LED state
      relay2State = !relay2State;
      digitalWrite(relayPin2, relay2State);

      // Update Button Widget
      Blynk.virtualWrite(V13, relay2State);
    }
    btn2State = LOW;
  } else {
    btn2State = HIGH;
  }
}


void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 8442);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8442);

  pinMode(relayPin1, OUTPUT);
  pinMode(btnPin1, INPUT_PULLUP);
  digitalWrite(relayPin1, relay1State);
  

  pinMode(relayPin2, OUTPUT);
  pinMode(btnPin2, INPUT_PULLUP);
  digitalWrite(relayPin2, relay2State);
  // Setup a function to be callled every 100 ms
  timer.setInterval(500L, checkPhysicalButton);

}

void loop()
{
  Blynk.run();
  timer.run();
}
