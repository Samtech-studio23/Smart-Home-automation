/*************************************************************
  Blynk is a platform with iOS and Android apps to control
  ESP32, Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build mobile and web interfaces for any
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: https://www.blynk.io
    Sketch generator:           https://examples.blynk.cc
    Blynk community:            https://community.blynk.cc
    Follow us:                  https://www.fb.com/blynkapp
                                https://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP32 chip.

  NOTE: This requires ESP32 support package:
    https://github.com/espressif/arduino-esp32

  Please be sure to select the right ESP32 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6tN5YvUPf"
#define BLYNK_TEMPLATE_NAME "SMART home"
#define BLYNK_AUTH_TOKEN "fcU4nezxeWJvhV46FEoQfxJ3tm_YF4iN"

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Your WiFi credentials.
char ssid[] = "B&S Fashion Store";
char pass[] = "weldingtig200";

// Relay pins
const int relayPin1 = 2;   // GPIO 2 for relay 1
const int relayPin2 = 4;   // GPIO 4 for relay 2
const int relayPin3 = 5;   // GPIO 5 for relay 3

// Switch pins (for manual control)
const int switchPin1 = 22; // GPIO 22 for manual switch 1
const int switchPin2 = 23; // GPIO 23 for manual switch 2
const int switchPin3 = 21; // GPIO 21 for manual switch 3

// Variables to track relay states
bool relayState1 = false;
bool relayState2 = false;
bool relayState3 = false;

void setup() {
  Serial.begin(9600);
  
  pinMode(relayPin1, OUTPUT);
  pinMode(relayPin2, OUTPUT);
  pinMode(relayPin3, OUTPUT);
  
  pinMode(switchPin1, INPUT_PULLUP); // Use internal pull-up resistor for switch 1
  pinMode(switchPin2, INPUT_PULLUP); // Use internal pull-up resistor for switch 2
  pinMode(switchPin3, INPUT_PULLUP); // Use internal pull-up resistor for switch 3

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
  
  // Read manual switches and control relays
  if (digitalRead(switchPin1) == LOW) { // Switch 1 pressed
    relayState1 = !relayState1; // Toggle relay 1
    digitalWrite(relayPin1, relayState1 ? HIGH : LOW); // Control relay 1
    Blynk.virtualWrite(V0, relayState1); // Update Blynk UI for relay 1
    delay(500); // Debounce delay
  }

  if (digitalRead(switchPin2) == LOW) { // Switch 2 pressed
    relayState2 = !relayState2; // Toggle relay 2
    digitalWrite(relayPin2, relayState2 ? HIGH : LOW); // Control relay 2
    Blynk.virtualWrite(V1, relayState2); // Update Blynk UI for relay 2
    delay(500); // Debounce delay
  }

  if (digitalRead(switchPin3) == LOW) { // Switch 3 pressed
    relayState3 = !relayState3; // Toggle relay 3
    digitalWrite(relayPin3, relayState3 ? HIGH : LOW); // Control relay 3
    Blynk.virtualWrite(V2, relayState3); // Update Blynk UI for relay 3
    delay(500); // Debounce delay
  }

  // Control relays via Blynk Virtual Pins
  Blynk.virtualWrite(V0, relayState1);
  Blynk.virtualWrite(V1, relayState2);
  Blynk.virtualWrite(V2, relayState3);
}

BLYNK_WRITE(V0) {
  relayState1 = param.asInt(); // Set relay 1 state via Blynk
  digitalWrite(relayPin1, relayState1 ? HIGH : LOW); // Control relay 1
}

BLYNK_WRITE(V1) {
  relayState2 = param.asInt(); // Set relay 2 state via Blynk
  digitalWrite(relayPin2, relayState2 ? HIGH : LOW); // Control relay 2
}

BLYNK_WRITE(V2) {
  relayState3 = param.asInt(); // Set relay 3 state via Blynk
  digitalWrite(relayPin3, relayState3 ? HIGH : LOW); // Control relay 3
}
