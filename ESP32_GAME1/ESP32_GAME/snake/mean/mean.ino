#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// OLED display
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

// Define pin numbers for buttons
#define UP_BUTTON_PIN 12
#define DOWN_BUTTON_PIN 14
#define LEFT_BUTTON_PIN 27
#define RIGHT_BUTTON_PIN 26

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Game variables
bool gameRunning = false;
bool gameStarted = false;
int selectedGame = 0; // 0: Menu, 1: Pong, 2: Snake

void setup() {
  Serial.begin(115200);

  // Initialize display
  display.begin(0x3c, true); // initialize with the I2C addr 0x3c
  display.display(); // show splashscreen
  delay(1000);
  display.clearDisplay();

  // Initialize button pins
  pinMode(UP_BUTTON_PIN, INPUT_PULLUP);
  pinMode(DOWN_BUTTON_PIN, INPUT_PULLUP);
  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);

  // Initialize random seed based on analog pin
  randomSeed(analogRead(0));

  // Display menu
  displayMenu();
}

void displayMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 10);
  display.println("Select a Game:");
  display.setCursor(0, 30);
  display.println("1. Pong");
  display.setCursor(0, 40);
  display.println("2. Snake");
  display.display();
}

void waitForKeyPress() {
  while (true) {
    if (digitalRead(UP_BUTTON_PIN) == LOW || digitalRead(DOWN_BUTTON_PIN) == LOW ||
        digitalRead(LEFT_BUTTON_PIN) == LOW || digitalRead(RIGHT_BUTTON_PIN) == LOW) {
      break;
    }
    delay(100); // Check for button press every 100ms
  }
}

void resetGame() {
  gameRunning = true;
  gameStarted = true;
  if (selectedGame == 1) {
    // Start Pong game
    startPong();
  } else if (selectedGame == 2) {
    // Start Snake game
    startSnake();
  }
}

void startPong() {
  
}

void startSnake() {
  // Your Snake game initialization code here
}

void loop() {
  if (!gameStarted) {
    waitForKeyPress();
    gameStarted = true;
    resetGame();
  }

  // Game loop for the selected game
  if (gameRunning) {
    if (selectedGame == 1) {
  
    } else if (selectedGame == 2) {
      // Snake game loop
      // Implement Snake game loop logic here
    }
  }
}
