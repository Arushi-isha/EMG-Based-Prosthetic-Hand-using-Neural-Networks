#define EMG_THUMB  A0
#define EMG_INDEX  A1
#define EMG_MIDDLE A2
#define EMG_RING   A3
#define EMG_LITTLE A6

int readEMG(int pin) {
  int sum = 0;
  for(int i = 0; i < 10; i++) {
    sum += analogRead(pin);
  }
  return sum / 10;
}

void setup() {
  Serial.begin(115200);
}

void loop() {
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

  delay(5);
}