#include <LiquidCrystal.h>

LiquidCrystal lcd_1(12, 11, 7, 6, 5, 4);

#define POLL_BUTTON_PIN 8
#define INT_BUTTON_PIN  3
#define LED_PIN         13

volatile bool interruptFlag = false;
unsigned long lastPollTime = 0;
unsigned long lastInterruptTime = 0;
const unsigned long DEBOUNCE_DELAY = 50;

// Timing variables to measure response time
unsigned long pollStartTime = 0;
unsigned long pollEndTime = 0;

unsigned long interruptStartTime = 0;
unsigned long interruptEndTime = 0;

void handleInterrupt() {
  if (digitalRead(INT_BUTTON_PIN) == LOW) {
    unsigned long now = millis();
    if (now - lastInterruptTime > DEBOUNCE_DELAY) {
      // Record interrupt start time
      interruptStartTime = millis();
      interruptFlag = true;
      lastInterruptTime = now;
    }
  }
}

void setup() {
  Serial.begin(9600);
  lcd_1.begin(16, 2);
  lcd_1.clear();
  lcd_1.print("System Ready");

  pinMode(POLL_BUTTON_PIN, INPUT_PULLUP);
  pinMode(INT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  attachInterrupt(digitalPinToInterrupt(INT_BUTTON_PIN), handleInterrupt, FALLING);

  Serial.println("Ready - Polling vs Interrupt with Timer");
}

void loop() {
  // Polling button
  if (digitalRead(POLL_BUTTON_PIN) == LOW) {
    if (millis() - lastPollTime > DEBOUNCE_DELAY) {
      Serial.println("Polling Button Pressed!");

      // Record start time
      pollStartTime = millis();

      // Turn ON LED
      digitalWrite(LED_PIN, HIGH);
      updateLCD("Polling", true);

      // Keep LED ON for 500 ms
      delay(500);

      // Simulate long task (busy loop)
      Serial.println("Doing long task...");
      lcd_1.setCursor(0, 1);
      lcd_1.print("Busy counting...  ");
      for (volatile unsigned long i = 0; i < 500000; i++) {
        // Simulate CPU work
        if (interruptFlag) break; // allow interrupt to break loop
      }

      // Record end time for polling
      pollEndTime = millis();

      // Turn OFF LED
      digitalWrite(LED_PIN, LOW);
      updateLCD("Polling", false);

      // Print response time
      Serial.print("Polling Response Time: ");
      Serial.print(pollEndTime - pollStartTime);
      Serial.println(" ms");

      lastPollTime = millis();

      // Wait for button release
      while (digitalRead(POLL_BUTTON_PIN) == LOW);
    }
  }

  // Interrupt button
  if (interruptFlag) {
    interruptFlag = false;

    // Record end time
    interruptEndTime = millis();

    Serial.println("Interrupt Triggered!");

    updateLCD("Interrupt", true);
    blinkLED(3, 100);
    updateLCD("Interrupt", false);

    // Calculate and show interrupt response time
    unsigned long responseTime = interruptEndTime - interruptStartTime;

    Serial.print("Interrupt Response Time: ");
    Serial.print(responseTime);
    Serial.println(" ms");

    // Also show both times on LCD
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
    lcd_1.print("Poll: ");
    lcd_1.print(pollEndTime - pollStartTime);
    lcd_1.print("ms");

    lcd_1.setCursor(0, 1);
    lcd_1.print("Int:  ");
    lcd_1.print(responseTime);
    lcd_1.print("ms");

    delay(2000); // Wait to read times
  }
}

void blinkLED(int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    digitalWrite(LED_PIN, HIGH);
    delay(delayTime);
    digitalWrite(LED_PIN, LOW);
    delay(delayTime);
  }
}

void updateLCD(const char* method, bool state) {
  lcd_1.clear();
  lcd_1.setCursor(0, 0);
  lcd_1.print(method);
  lcd_1.setCursor(0, 1);
  lcd_1.print("LED: ");
  lcd_1.print(state ? "ON " : "OFF");
}
