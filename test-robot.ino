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

  Serial.println("setup pin modes");
  for (int i = 2; i <= 13; i++) {
    pinMode(i, OUTPUT);
    if (i % 2 == 0) {
      Serial.println("");
    } else {
      digitalWrite(i, HIGH);
    }
  }

  delay(5000);
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

void loop() {

    if (steps % 100 == 0) {
      Serial.println(steps);
    }

    if (steps <= maxStepsForward) {
      forward(J1_STEP, J1_DIR);
      forward(J2_STEP, J2_DIR);
      backward(J3_STEP, J3_DIR);
      backward(J6_STEP, J6_DIR);
      forward(J4_STEP, J4_DIR); // twist axis

      // backward(J5_STEP, J5_DIR); // DANGER Enable with Caution

      steps++;
    } else if (steps >= maxStepsForward && steps <= reset) {
      backward(J1_STEP, J1_DIR);
      backward(J2_STEP, J2_DIR);
      forward(J3_STEP, J3_DIR);
      forward(J6_STEP, J6_DIR);
      backward(J4_STEP, J4_DIR); // twist axis

      // forward(J5_STEP, J5_DIR); // DANGER Enable with Caution

      steps++;
    } else if (steps > reset) {
      steps = 0;
    }

}