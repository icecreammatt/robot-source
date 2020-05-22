/*
  Pins for Mega
  J1 2 PULL, 3 DIR - Rotate base
  J2 4 PULL, 5 DIR - Arm up and down
  J3 6 PULL, 7 DIR - Elbow up and down
  J4 8 PULL, 9 DIR - Rotate Wrist
  J5 10 PULL, 11 DIR - Roll Wrist // DANGER THIS HAS LIMITED RANGE (install limit switches before using)
  J6 12 PULL, 13 DIR - Roll Hand
  J7 20 PULL, 21 DIR - Slide on rail, (not installed yet)
*/
const int J1_STEP = 2;
const int J1_DIR = 3;

const int J2_STEP = 4;
const int J2_DIR = 5;

const int J3_STEP = 6;
const int J3_DIR = 7;

const int J4_STEP = 8;
const int J4_DIR = 9;

// DANGER
// const int J5_STEP = 10;
// const int J5_DIR = 11;

const int J6_STEP = 12;
const int J6_DIR = 13;

// Using 8,9 for uno to test with
int stepPin = 2;  //PUL-
int directionPin = 3;  // DIR-

int loops = 0;
int pulseWidthMicros = 0;
int millisbetweenSteps = 2; // milliseconds - or try 1000 for slower steps

int maxStepsForward = 2000;
int maxStepsBackward = maxStepsForward;
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

  delay(2000);
}

void forward(int stepPin, int directionPin) {
  // Serial.println("forward");
  digitalWrite(directionPin, HIGH);
  digitalWrite(stepPin, HIGH);
  delay(pulseWidthMicros);
  digitalWrite(stepPin, LOW);
  delay(millisbetweenSteps);
}

void backward(int stepPin, int directionPin) {
  // Serial.println("backward");
  digitalWrite(directionPin, LOW); 
  digitalWrite(stepPin, HIGH);
  delay(pulseWidthMicros);
  digitalWrite(stepPin, LOW);
  delay(millisbetweenSteps);
}

void loop() {
    if (loops % 100 == 0) {
      Serial.println(loops);
    }
    if (loops <= maxStepsForward) {
      forward(J1_STEP, J1_DIR);
      forward(J2_STEP, J2_DIR);
      backward(J3_STEP, J3_DIR);
      // forward(J4_STEP, J4_DIR);
      backward(J6_STEP, J6_DIR);
      loops++;
    } else if (loops >= maxStepsForward && loops <= reset){
      backward(J1_STEP, J1_DIR);
      backward(J2_STEP, J2_DIR);
      forward(J3_STEP, J3_DIR);
      // backward(J4_STEP, J4_DIR);
      forward(J6_STEP, J6_DIR);
      loops++;
    } else if (loops > reset) {
      loops = 0;
    }
}