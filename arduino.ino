#include <Servo.h>

// =========================
// EMG PINS
// =========================
#define EMG_THUMB  A0
#define EMG_INDEX  A1
#define EMG_MIDDLE A2
#define EMG_RING   A3
#define EMG_LITTLE A4

// =========================
// SERVO OBJECTS
// =========================
Servo thumb, indexF, middle, ring, little;

int posOpen = 20;
int posClose = 100;

// =========================
// READ EMG (AVERAGE FILTER)
// =========================
int readEMG(int pin) {
  int sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(pin);
  }
  return sum / 10;
}

// =========================
// SETUP
// =========================
void setup() {
  Serial.begin(115200);

  thumb.attach(3);
  indexF.attach(5);
  middle.attach(6);
  ring.attach(9);
  little.attach(10);

  openHand();
}

// =========================
// LOOP
// =========================
void loop() {

  // -------- SEND EMG DATA --------
  int t = readEMG(EMG_THUMB);
  int i = readEMG(EMG_INDEX);
  int m = readEMG(EMG_MIDDLE);
  int r = readEMG(EMG_RING);
  int l = readEMG(EMG_LITTLE);

  Serial.print(t); Serial.print(",");
  Serial.print(i); Serial.print(",");
  Serial.print(m); Serial.print(",");
  Serial.print(r); Serial.print(",");
  Serial.println(l);

  // -------- RECEIVE ML OUTPUT --------
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    int gesture = cmd.toInt();
    executeGesture(gesture);
  }

  delay(10);  // stable sampling (~100 Hz)
}

// =========================
// GESTURE CONTROLLER
// =========================
void executeGesture(int gesture) {
  switch (gesture) {
    case 0: openHand(); break;
    case 1: thumbOnly(); break;
    case 2: indexOnly(); break;
    case 3: middleOnly(); break;
    case 4: ringOnly(); break;
    case 5: littleOnly(); break;
    case 6: closeHand(); break;
    case 7: victory(); break;
    case 8: thumbsup(); break;
  }
}

// =========================
// HAND FUNCTIONS
// =========================
void openHand() {
  thumb.write(posOpen);
  indexF.write(posOpen);
  middle.write(posOpen);
  ring.write(posOpen);
  little.write(posOpen);
}

void closeHand() {
  thumb.write(posClose);
  indexF.write(posClose);
  middle.write(posClose);
  ring.write(posClose);
  little.write(posClose);
}

void thumbOnly() {
  openHand();
  thumb.write(posClose);
}

void indexOnly() {
  openHand();
  indexF.write(posClose);
}

void middleOnly() {
  openHand();
  middle.write(posClose);
}

void ringOnly() {
  openHand();
  ring.write(posClose);
}

void littleOnly() {
  openHand();
  little.write(posClose);
}

void victory() {
  openHand();
  thumb.write(posClose);
  ring.write(posClose);
  little.write(posClose);
}

void thumbsup() {
  openHand();
  indexF.write(posClose);
  middle.write(posClose);
  ring.write(posClose);
  little.write(posClose);
}