

int pulMinus = 9;  //PUL-
int pulPlus = 10;  // PUL+5

int dirMinus = 11;  // DIR-
int dirPlus = 12;   // DIR+5

int loops = 0;

void setup() {
  pinMode(pulMinus, OUTPUT);
  pinMode(pulPlus, OUTPUT);
  
  pinMode(dirMinus, OUTPUT);
  pinMode(dirPlus, OUTPUT);

//  digitalWrite(dirMinus, HIGH); // for reverse 
  digitalWrite(dirMinus, LOW); 
  digitalWrite(dirPlus, LOW);

//  digitalWrite(pulMinus, LOW); // for reverse
  digitalWrite(pulMinus, HIGH);
  digitalWrite(pulPlus, LOW);

  
  Serial.begin(9600);
  Serial.println("init");

  // Forward
  digitalWrite(dirPlus, HIGH);
  delay(100);
  digitalWrite(dirPlus, LOW);

  // Reverse
//  digitalWrite(pulPlus, HIGH);
//  delay(100);
//  digitalWrite(pulPlus, LOW);
  
}

void forward() {
    digitalWrite(pulPlus, HIGH);
    digitalWrite(pulPlus, LOW);
}

void reverse() { 
    digitalWrite(dirPlus, HIGH);
    digitalWrite(dirPlus, LOW);
}


void loop() {

//   if(loops < 100) {
    forward();
    loops++;
//   }

  Serial.println(loops);
  delay(1);
}