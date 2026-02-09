#include <LiquidCrystal.h>

const int relayPin = 7;
const int upPin = 8;
const int downPin = 9;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char receivedChar = 0;
int feed = 2000;
int count = 0;

void setup() {

  Serial.begin(9600);

  pinMode(upPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);
  pinMode(relayPin, OUTPUT);

  digitalWrite(relayPin, LOW);

  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setting up...");
  
}

void loop() {
  if (Serial.available() > 0) {
    receivedChar = Serial.read();
    closeSwitch();          // act immediately on new char
  }

  updateFeed();

  lcd.setCursor(0, 0);
  lcd.print("Feed Rate: ");
  lcd.print(feed);
  lcd.print("   ");         // clears leftover digits

  count++;
  if (count % 200 == 0) {
    Serial.println(feed);
  }
}

void closeSwitch() {
  if (receivedChar == 't') {
    digitalWrite(relayPin, HIGH);
    lcd.setCursor(0, 1);
    lcd.print("EMagnet:ON ");
    receivedChar = 0;       // consume
  } 
  else if (receivedChar == 'f') {
    digitalWrite(relayPin, LOW);
    lcd.setCursor(0, 1);
    lcd.print("EMagnet:OFF");
    receivedChar = 0;       // consume
  }
  count++;
  if (count % 60 == 0) {
    Serial.print(feed);
  }
}

void updateFeed() {
  if (digitalRead(upPin) == LOW) {
    feed += 5;
  }
  if (digitalRead(downPin) == LOW) {
    feed -= 5;
  }
}
