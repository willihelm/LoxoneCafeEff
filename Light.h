// Klasse Light
// Abstraktes Modell eines Buttons
// Eigenschaften:
// lightName      =>  Lichtbezeichnung innerhalb von Loxone
// ledPin         =>  digitaler Input zum Schalten der LED
// buttonPin      =>  digitaler Input zur Abfrage des Tasters
// on             =>  gibt an, ob das Licht an (true) oder aus (false)
class Light
{
  String lightName;
  int ledPin;
  int buttonPin;
  bool on;

  // wird beim Erstellen eines Objekts aufgerufen, setzt unter anderem den pinMode
public:
  void setup(String name, int pin1, int pin2)
  {
    lightName = name;
    ledPin = pin1;
    buttonPin = pin2;
    on = false;
    Serial.print(name);
    Serial.print(" led: ");
    Serial.print(ledPin);
    Serial.print(" button: ");
    Serial.println(buttonPin);
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    pinMode(buttonPin, INPUT_PULLUP);
  }

  // gibt den Status des Lichts zurück
public:
  bool isOn()
  {
    return on;
  }

  // gibt den Wert von buttonPin zurück
public:
  int getButtonPin()
  {
    return buttonPin;
  }

  // Aktualisiert die Anzeige und den Status des Lichts, Webrequest an Loxone
public:
  void updateLed(HttpClient http)
  {
    // Webrequest to update led
    http.beginRequest();
    http.get("/dev/sps/io/LK%20" + lightName + "/state");
    http.sendBasicAuth(LOXONE_USER, LOXONE_PASSWORD);
    http.endRequest();
    
    unsigned long start = millis();
    
    //int statusCode = http.responseStatusCode();
    String response = http.responseBody();

    unsigned long end = millis();
    Serial.println(end - start);
    
    //Serial.print("code: ");
    //Serial.println(statusCode);
    //Serial.print("response: ");
    //Serial.println(response);

    //int responseChar[] = response.toCharArray(buf, len) // Das geht noch nicht
    //Serial.print(responseChar);
    int from = 73 + lightName.length();
    String value = response.substring(from, from + 1);
    //Serial.println("value: " + value);

    if (value == "1")
    {
      Serial.print(lightName);
      Serial.println(" is on");
      digitalWrite(ledPin, HIGH);
      on = true;
    }
    else
    {
      Serial.print(lightName);
      Serial.println(" is off");
      digitalWrite(ledPin, LOW);
      on = false;
    };
  }

// schaltet das Licht an, Webrequest an Loxone
public:
  void turnOn(HttpClient http)
  {
    Serial.println("An");
    
    // Webrequest to turn on this light
    http.beginRequest();
    http.get("/dev/sps/io/" + lightName + "/Ein");
    http.sendBasicAuth(LOXONE_USER, LOXONE_PASSWORD);
    http.endRequest();
    
    Serial.print(lightName);
    Serial.println(" is on");
    digitalWrite(ledPin, HIGH);
    on = true;

    while(!digitalRead(buttonPin)) {
      // warte bis losgelassen
    }
  }

// schaltet das Licht aus, Webrequest an Loxone
public:
  void turnOff(HttpClient http)
  {
    Serial.println("Aus");

    // Webrequest to turn off this light
    http.beginRequest();
    http.get("/dev/sps/io/" + lightName + "/Aus");
    http.sendBasicAuth(LOXONE_USER, LOXONE_PASSWORD);
    http.endRequest();

    Serial.print(lightName);
    Serial.println(" is off");
    digitalWrite(ledPin, LOW);
    on = false;
    
    while(!digitalRead(buttonPin)) {
      // warte bis losgelassen
    }
  }
};
