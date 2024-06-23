// Define pins for PIR sensors
const int pirPin1 = 2;
const int pirPin2 = 3;
const int pirPin3 = 4;

// Define pins for LEDs
const int ledPin1 = 8;
const int ledPin2 = 9;

// Define variables to store the PIR sensor states
int pirState1 = LOW;
int pirState2 = LOW;
int pirState3 = LOW;

// Define timing variables
unsigned long previousMillis1 = 0;
unsigned long previousMillis2 = 0;
unsigned long previousMillis3 = 0;
unsigned long previousMillis4 = 0;
const long interval = 15000; // 15 seconds

void setup() {
  // Initialize PIR sensor pins as input
  pinMode(pirPin1, INPUT);
  pinMode(pirPin2, INPUT);
  pinMode(pirPin3, INPUT);
  
  //Initialize Camera pin as output
  pinMode(7,OUTPUT);

  // Initialize LED pins as output
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);

  // Initialize LEDs to be off
  digitalWrite(ledPin1, LOW);
  digitalWrite(ledPin2, LOW);
  digitalWrite(7,LOW);
  Serial.begin(9600); // Initialize serial communication for debugging
}

void loop() {
  //Check for Camera Activation
  if(digitalRead(2) == HIGH)
 {
   previousMillis4 = millis(); // Update last motion detection time
   digitalWrite(7, HIGH);
 }
  if (millis() - previousMillis4 >= interval) 
      digitalWrite(7, LOW);  

  
  // Check the PIR sensor states
  pirState1 = digitalRead(pirPin1);
  pirState2 = digitalRead(pirPin2);
  pirState3 = digitalRead(pirPin3);

  unsigned long currentMillis = millis();

  // If PIR sensor 1 is triggered
  if (pirState1 == HIGH) {
    digitalWrite(ledPin1, HIGH);
    previousMillis1 = currentMillis;
  }

  // If PIR sensor 2 is triggered
  if (pirState2 == HIGH) {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, HIGH);
    previousMillis2 = currentMillis;
  }

  // If PIR sensor 3 is triggered
  if (pirState3 == HIGH) {
    digitalWrite(ledPin2, HIGH);
    previousMillis3 = currentMillis;
  }

  // Turn off LED 1 after 20 seconds if it was triggered by PIR sensor 1 or 2
  if ((digitalRead(ledPin1) == HIGH) && (currentMillis - previousMillis1 >= interval) && (pirState2 == LOW) && (currentMillis - previousMillis2 >= interval)&&(pirState1 == LOW)) {
    digitalWrite(ledPin1, LOW);
  }

  // Turn off LED 2 after 20 seconds if it was triggered by PIR sensor 2 or 3
  if ((digitalRead(ledPin2) == HIGH) && (currentMillis - previousMillis2 >= interval) && (pirState3 == LOW)&& (pirState2 == LOW) && (currentMillis - previousMillis3 >= interval)&&(pirState3 == LOW)) {
    digitalWrite(ledPin2, LOW);
  }

  Serial.print("PIR1: ");
  Serial.print(pirState1);
  Serial.print(" PIR2: ");
  Serial.print(pirState2);
  Serial.print(" PIR3: ");
  Serial.print(pirState3);
  Serial.print(" LED1: ");
  Serial.print(digitalRead(ledPin1));
  Serial.print(" LED2: ");
  Serial.print(digitalRead(ledPin2));
  Serial.print(" Camera: ");
  Serial.println(digitalRead(7));
  delay(10); // Short delay to stabilize sensor readings
}
