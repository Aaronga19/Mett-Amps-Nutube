

const int CS = 2;
const int INC = 10;
const int UD = 1;

void setup() {
  pinMode(CS, OUTPUT);
  pinMode(INC, OUTPUT);
  pinMode(UD, OUTPUT);
  digitalWrite(CS, HIGH);  
  digitalWrite(INC, HIGH); 
  digitalWrite(UD, HIGH); 
}

void loop() {
   for (int i=0; i<=100; i+=10) {
    setResistance(i);
    delay(100);
  }
}

void setResistance(int percent) { 
  digitalWrite(UD, LOW); 
  digitalWrite(CS, LOW); 
  for (int i=0; i<100; i++) { 
    digitalWrite(INC, LOW);
    delayMicroseconds(1);
    digitalWrite(INC, HIGH);
    delayMicroseconds(1);
  }

  digitalWrite(UD, HIGH);
  for (int i=0; i<percent; i++) {
    digitalWrite(INC, LOW);
    delayMicroseconds(1);
    digitalWrite(INC, HIGH);
    delayMicroseconds(1);
  }

  digitalWrite(CS, HIGH);
}
