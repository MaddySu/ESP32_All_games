#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

// Define the pin for the button
#define BUTTON_PIN 4

enum GameState { WAITING, READY, REACT, SHOW_RESULT };
GameState gameState = WAITING;

unsigned long startTime;
unsigned long endTime;
unsigned long reactionTime;

void setup() {
  Serial.begin(115200);

  // Initialize display
  display.begin(0x3c, true); // initialize with the I2C addr 0x3c
  display.display(); // show splashscreen
  delay(1000);
  display.clearDisplay();

  // Initialize button pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 20);
  display.print("Press button to start");
  display.display();
}

void loop() {
  switch (gameState) {
    case WAITING:
      if (digitalRead(BUTTON_PIN) == LOW) {
        gameState = READY;
        display.clearDisplay();
        display.setCursor(10, 20);
        display.print("Get Ready...");
        display.display();
        delay(random(2000, 5000)); // Wait for a random time between 2-5 seconds
        gameState = REACT;
        display.clearDisplay();
        display.setCursor(10, 20);
        display.print("PRESS NOW!");
        display.display();
        startTime = millis();
      }
      break;

    case READY:
      // This state is handled by the delay in the WAITING case
      break;

    case REACT:
      if (digitalRead(BUTTON_PIN) == LOW) {
        endTime = millis();
        reactionTime = endTime - startTime;
        gameState = SHOW_RESULT;
      }
      break;

    case SHOW_RESULT:
      display.clearDisplay();
      display.setCursor(10, 20);
      display.print("Reaction Time:");
      display.setCursor(10, 30);
      display.print(reactionTime);
      display.print(" ms");
      display.setCursor(10, 40);
      display.print("Press to restart");
      display.display();
        delay(1000);
      if (digitalRead(BUTTON_PIN) == LOW) {
        delay(500); // Debounce delay
        gameState = WAITING;
        display.clearDisplay();
        display.setCursor(10, 20);
        display.print("Press button to start");
        display.display();
      }
      break;
  }
}
