// Klasse Scene
// Abstraktes Modell eines Szene-Buttons
// Eigenschaften:
// ledPin         =>  digitaler Input zum Schalten der LED
// buttonPin      =>  digitaler Input zur Abfrage des Tasters
// on             =>  gibt an, ob das Licht an (true) oder aus (false)
class Scene {
  int scene;
  int ledPin;
  int buttonPin;
  bool on;

  // wird beim Erstellen eines Objekts aufgerufen, setzt unter anderem den pinMode
public:
  void setup(int sceneArray[], int pin1, int pin2) {
    for (int j = 0; j < 2; j++) {
        Serial.print("Scene: ");
        Serial.println(sceneArray[j]);
    }
    //Serial.println(pin1);
    //Serial.println(pin2);
    scene = sceneArray;
    ledPin = pin1;
    buttonPin = pin2;
    on = false;
    Serial.print(" led: ");
    Serial.print(ledPin);
    Serial.print(" button: ");
    Serial.println(buttonPin);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    pinMode(buttonPin, INPUT_PULLUP);
  }

  // gibt den Wert von buttonPin zurück
public:
  int getButtonPin() {
    return buttonPin;
  }

public:
  int* get() {
    return scene;
  }

public:
  bool isOn() {
    return on;
  }

public:
  void turnLedOff() {
    digitalWrite(ledPin, LOW);  
    on = false;
  }

public:
  void turnLedOn() {
    digitalWrite(ledPin, HIGH);
    on = true;
  }
};
