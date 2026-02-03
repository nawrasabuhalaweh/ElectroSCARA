// this file contains the basis of the communication between python and the arduino.
// it tells the arduino how to interpret commands from the serial monitor to turn it on and off.

const int relayPin = 7;
const int ledPin = 5;

char receivedChar;
boolean newData = false;

void setup() {
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
  digitalWrite(relayPin, LOW);
  
  Serial.begin(9600);
  Serial.println("Ready for input");
}

void loop() {
  recvOneChar();
  closeSwitch();
}

void recvOneChar() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
  }
}

void closeSwitch() {
  if (receivedChar == 't') {
    digitalWrite(relayPin, HIGH);
    digitalWrite(ledPin, HIGH);
  } else if (receivedChar == 'f') {
    digitalWrite(ledPin, LOW);
    digitalWrite(relayPin, LOW);
  }

}
