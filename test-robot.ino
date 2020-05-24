/*
  Pins for Mega
  J1 2 PULL, 3 DIR - Rotate base
  J2 4 PULL, 5 DIR - Arm up and down
  J3 6 PULL, 7 DIR - Elbow up and down
  J4 8 PULL, 9 DIR - Rotate Elbow
  J5 10 PULL, 11 DIR - Rotate Wrist // DANGER THIS HAS LIMITED RANGE (install limit switches before using)
  J6 12 PULL, 13 DIR - Spin Hand
  J7 20 PULL, 21 DIR - Slide on rail, (not installed yet)
*/

boolean enableMovement = false;

boolean J1_enabled = false;
boolean J2_enabled = false;
boolean J3_enabled = false;
boolean J4_enabled = false;
boolean J5_enabled = false;
boolean J6_enabled = false;
boolean J7_enabled = false;

// Rotate base
const int J1_STEP = 2;
const int J1_DIR = 3;

// Move Arm up and down
const int J2_STEP = 4;
const int J2_DIR = 5;

// Move elbow up and down
const int J3_STEP = 6;
const int J3_DIR = 7;

// Rotate elbow elbow
const int J4_STEP = 8;
const int J4_DIR = 9;

// DANGER  Rotate wrist
const int J5_STEP = 10;
const int J5_DIR = 11;

// Spin hand
const int J6_STEP = 12;
const int J6_DIR = 13;

int steps = 0;
int pulseWidthMicros = 1;
int millisbetweenSteps = 0; // milliseconds - or try 1000 for slower steps

int maxStepsForward = 1000;
int reset = maxStepsForward * 2;

void setup() {
  Serial.println("init");
  Serial.begin(9600);

 // Setup output / movement pins
  Serial.println("setup pin modes");
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
    if (i % 2 == 0) {
      Serial.println("");
    } else {
      digitalWrite(i, HIGH);
    }
  }

  // Setup input relays
  Serial.println("setup relay pin modes");
  for (int i = 14; i <= 19; i++) {
    pinMode(i, INPUT);
  }

  Serial.println("Power up drivers... movement starting program in 5 seconds");
  delay(1000);
  Serial.println("4");
  delay(1000);
  Serial.println("3");
  delay(1000);
  Serial.println("2");
  delay(1000);
  Serial.println("1");
  delay(1000);

/* Test J5 movement
  enableMovement = true;
  J1_enabled = false;
  J2_enabled = false;
  J3_enabled = false;
  J4_enabled = false;
  J5_enabled = true; // DANGER
  J6_enabled = false;
*/

  enableMovement = true;
  J1_enabled = true;
  J2_enabled = true;
  J3_enabled = true;
  J4_enabled = true;
  J5_enabled = false; // DANGER
  J6_enabled = true;

  Serial.println("Moving...");
}

void forward(int stepPin, int directionPin) {
  digitalWrite(directionPin, HIGH);
  digitalWrite(stepPin, HIGH);
  delay(pulseWidthMicros);
  digitalWrite(stepPin, LOW);
  delay(millisbetweenSteps);
}

void backward(int stepPin, int directionPin) {
  digitalWrite(directionPin, LOW); 
  digitalWrite(stepPin, HIGH);
  delay(pulseWidthMicros);
  digitalWrite(stepPin, LOW);
  delay(millisbetweenSteps);
}

void readRelayState() {
  for (int i = 14; i <= 19; i++) {
    int readValue = digitalRead(i);
    if (i == 14 && readValue == 1) {
      J1_enabled = false;
      J5_enabled = false;
    } else if (i == 15 && readValue == 1) {
      J2_enabled = false;
    } else if (i == 16 && readValue == 1) {
      J3_enabled = false;
    } else if (i == 17 && readValue == 1) {
      J4_enabled = false;
    } else if (i == 18 && readValue == 1) {
      J5_enabled = false;
    } else if (i == 19 && readValue == 1) {
      J6_enabled = false;
    }
  }
}

void loop() {

    if (steps % 2000 == 0) {
      Serial.println(steps);
    }

    readRelayState();

    if (steps <= maxStepsForward) {

      if (enableMovement) {
        if (J1_enabled) forward(J1_STEP, J1_DIR);
        if (J2_enabled) forward(J2_STEP, J2_DIR);
        if (J3_enabled) backward(J3_STEP, J3_DIR);
        if (J6_enabled) backward(J6_STEP, J6_DIR);
        if (J4_enabled) forward(J4_STEP, J4_DIR); // twist axis

        // if (J5_enabled) backward(J5_STEP, J5_DIR); // DANGER Enable with Caution
      }

      steps++;
    } else if (steps >= maxStepsForward && steps <= reset) {

      if (enableMovement) {
        if (J1_enabled) backward(J1_STEP, J1_DIR);
        if (J2_enabled) backward(J2_STEP, J2_DIR);
        if (J3_enabled) forward(J3_STEP, J3_DIR);
        if (J6_enabled) forward(J6_STEP, J6_DIR);
        if (J4_enabled) backward(J4_STEP, J4_DIR); // twist axis

        // if (J5_enabled) forward(J5_STEP, J5_DIR); // DANGER Enable with Caution
      }

      steps++;
    } else if (steps > reset) {
      steps = 0;
    }

}