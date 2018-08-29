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

// Konfiguration in "Variables.h" hinterlegen


// globale Variablen

// zaehlt die Anzahl der Input Scans
int scanCount = 0;

// Array zum Speichern der Objekte
Light light[LIGHT_COUNT];
  
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
  Serial.print(LOXONE_PASSWORD);
  //if (Ethernet.begin(mac) == 0) {
    //Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  //}

  // print your WiFi shield's IP address:
  IPAddress ip = Ethernet.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
  Serial.println("Connected!");
  Serial.println("setup lights...");
  int pin = START_PIN;
  for (int i = 0; i < LIGHT_COUNT; i++)
  {
    int led = pin++;
    int button = pin++;
    light[i].setup(lightNames[i], led, button);
  }
}

void loop()
{
  //Serial.println("");
  //Serial.print("scanButtons");
  scanButtons();

  // nach 10000 button scans update led status
  scanCount++;
  if (scanCount >= 100000)
  {
    Serial.println("updateLeds...");
    updateLeds(http);
    scanCount = 0;
  }
}

// globale Methoden

// Methode zum Updaten der LEDs per Webrequest
void updateLeds(HttpClient http)
{
  for (int i = 0; i < LIGHT_COUNT; i++)
  {
    light[i].updateLed(http);
    scanButtons();
  }
  scanCount = 0;
}

// Methode zum Scan der Input-Buttons
void scanButtons()
{
  for (int i = 0; i < LIGHT_COUNT; i++)
  {
    //Serial.print(".");
    if (!digitalRead(light[i].getButtonPin()))
    {
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
}
