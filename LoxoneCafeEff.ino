// Entwickler:  Willi Dueck
// Email:       willi_dueck@gmx.de
//
// Programm zur Schaltung von Licht mithilfe eines Arduino MEGA2560
// und einem Ethernet Shield

// Bibliotheken laden
#include <SPI.h>
#include <Ethernet.h>
#include <ArduinoHttpClient.h>

#include "Config.h"
#include "Var.h"
#include "Light.h"
#include "Scene.h"

// Konfiguration in "Config.h" hinterlegen
// Lichtkreise und Szenen in "Var.h" hinterlegen


// globale Variablen

// zaehlt die Anzahl der Input Scans
int scanCount = 0;

// Array zum Speichern der Objekte
Light light[LIGHT_COUNT];
Scene scene[SCENE_COUNT];
  
// Setup Connection
char url[] = LOXONE_URL;
byte mac[] = MAC_ADDRESS;
IPAddress ip(FALLBACK_IP);
EthernetClient client;
HttpClient http = HttpClient(client, url, LOXONE_PORT);

// Start des Programms

void setup()
{
  Serial.begin(9600);
  Serial.println("setup...");
  Serial.println(ip);
  //if (Ethernet.begin(mac) == 0) {
    //Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  //}

  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());
  Serial.println("Connected!");
  Serial.println("setup lights...");
  int cPin = 0;
  
  Serial.println("Lights:");
  for (int i = 0; i < LIGHT_COUNT; i++) {
    int led = pin[cPin++];
    int button = pin[cPin++];
    light[i].setup(lightNames[i], led, button);
  }

  Serial.println("Scenes:");
  for (int i = 0; i < SCENE_COUNT; i++) {
    int led = pin[cPin++];
    int button = pin[cPin++];
    scene[i].setup(scenes[i], led, button);
  }
}

void loop()
{
  //Serial.println("");
  //Serial.print("scanButtons");
  scanButtons();

  // nach 10000 button scans update led status
  scanCount++;
  if (scanCount >= 100000) {
    Serial.println("updateLeds...");
    updateLeds(http);
    scanCount = 0;
  }
}

// globale Methoden

// Methode zum Updaten der LEDs per Webrequest
void updateLeds(HttpClient http) {
  for (int i = 0; i < LIGHT_COUNT; i++) {
    light[i].updateLed(http);
    scanButtons();
  }
  scanCount = 0;
}

// Methode zum Scan der Input-Buttons
void scanButtons() {
  for (int i = 0; i < LIGHT_COUNT; i++) {
    //Serial.print(".");
    if (!digitalRead(light[i].getButtonPin())) {
      Serial.print("Light Button pin: ");
      Serial.println(light[i].getButtonPin());

      
      
      if (light[i].isOn())
      {
        light[i].turnOff(http);
      }
      else
      {
        light[i].turnOn(http);
      }
      //light[i].updateLed(http);
    }
  }

  for (int i = 0; i < SCENE_COUNT; i++) {
    //Serial.print(".");
    if (!digitalRead(scene[i].getButtonPin())) {
      Serial.print("Scene Button pin: ");
      Serial.println(scene[i].getButtonPin());
      int* sc = scene[i].get();
      szeneLedsOff();
      if (sceneCount[i] == 0) {
        scene[i].turnLedOn();
        allOff(false);
        scene[i].turnLedOff();
      } else {
        scene[i].turnLedOn();
        allOff(true);  
      }
      
      for (int j = 0; j < sceneCount[i]; j++) {
        light[sc[j]].turnOn(http);
      }
    }
  }
}

void allOff(bool exclude) {
  Serial.println("AllOff");
  for (int i = 0; i < LIGHT_COUNT; i++) {
    if (exclude) {
      for (int j = 0; j < (sizeof(excluded)/sizeof(int)); j++) {
        if (i == excluded[j]) {
          return;
        }
      }
    }
    light[i].turnOff(http);
  }
}

void szeneLedsOff() {
  for (int i = 0; i < SCENE_COUNT; i++) {
    scene[i].turnLedOff();
  }
}
