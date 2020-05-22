/*
  Pins for Mega
  J1 2 PULL, 3 DIR
  J2 4 PULL, 5 DIR
  J3 6 PULL, 7 DIR
  J4 8 PULL, 9 DIR
  J5 10 PULL, 11 DIR
  J6 12 PULL, 13 DIR
  J7 20 PULL, 21 DIR
*/

// Using 8,9 for uno to test with
int stepPin = 8;  //PUL-
int directionPin = 9;  // DIR-

int loops = 0;
int pulseWidthMicros = 0;
int millisbetweenSteps = 5; // milliseconds - or try 1000 for slower steps

int maxStepsForward = 1000;
int maxStepsBackward = 1000;
int reset = maxStepsForward * 2;

void setup() {
  Serial.println("init");
  Serial.begin(9600);

  pinMode(directionPin, OUTPUT);
  pinMode(stepPin, OUTPUT);

  digitalWrite(directionPin, HIGH);

  delay(2000);
}

void forward() {
  // Serial.println("forward");
  digitalWrite(directionPin, HIGH);
  digitalWrite(stepPin, HIGH);
  delay(pulseWidthMicros);
  digitalWrite(stepPin, LOW);
  delay(millisbetweenSteps);
}

void backward() {
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
      forward();
      loops++;
    } else if (loops >= maxStepsForward && loops <= reset){
      backward();
      loops++;
    } else if (loops > reset) {
      loops = 0;
    }
}