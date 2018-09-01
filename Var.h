#define LIGHT_COUNT 15
#define SCENE_COUNT 5

// Es werden immer 2 Pins pro Button verwendet
// (1. Pin LED[weisses Kabel], 2. Pin Input Taster[rotes Kabel])
int pin[] = {16,17,18,19,20,21,22,23,24,25,26,27,28,29,10,31,32,33,34,
      35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,A8,A9,A10,A11,A12,A13};

// Liste der Licht-Bezeichnungen aus Loxone, HTML encoded
// %20 -> " "
// %2E -> "."
String lightNames[] = {
    "Cafe%201%2E1",       // "Cafe 1.1"
    "Cafe%201%2E2",       // "Cafe 1.2"
    "Cafe%201%2E3",       // "Cafe 1.3"
    "Cafe%202%2E1",       // "Cafe 2.1"
    "Cafe%202%2E2",       // "Cafe 2.2"
    "Cafe%202%2E3",       // "Cafe 2.3"
    "Cafe%203%2E1",       // "Cafe 3.1"
    "Cafe%203%2E2",       // "Cafe 3.2"
    "Cafe%203%2E3",       // "Cafe 3.3"
    "Cafe%20indirekt",    // "Cafe indirekt"
    "Theke%20ambient",    // "Theke ambient"
    "",                   // ""
    "",                   // ""
    "",                   // ""
    ""                    // ""
};

// Szenen können hier konfiguriert werden
// Eine Szene entspricht eine Liste der Indizes des Arrays lightNames
// Der erste Index eines Arrays ist 0
int scene0[] = {0,3,6};
int scene1[] = {1,4,7};
int scene2[] = {2,5,8};
int scene3[] = {0,1,2,3,4,5,6,7,8,9};
int scene4[] = {}; // Alles Aus

int scenes[] = {scene0, scene1, scene2, scene3, scene4};

int sceneCount[] = {3,3,3,10,0}; // Anzahl der Lichter in den Szenen 0-4

// Von der Szenensteuerung ausschließen
int excluded[] = {11,12,13,14};
