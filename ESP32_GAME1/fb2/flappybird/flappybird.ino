#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

// Define the pin for the button
#define BUTTON_PIN 4

// Game variables
float birdY;
float birdVelocity;
const float gravity = 0.3;  // Gravity affecting the bird
const float lift = -3;      // The lift force when the button is pressed (bounciness)
int score;
bool gameStarted;
bool gameOver;

const int pipeWidth = 8;
const int pipeGap = 30;
float pipeX;
float pipeGapY;

unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(115200);

  // Initialize display
  display.begin(0x3c, true); // initialize with the I2C addr 0x3c
  display.display(); // show splashscreen
  delay(1000);
  display.clearDisplay();

  // Initialize button pin
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // Initialize game variables
  resetGame();
}

void drawBird() {
  display.fillCircle(20, birdY, 3, SH110X_WHITE);
}

void drawPipe() {
  display.fillRect(pipeX, 0, pipeWidth, pipeGapY, SH110X_WHITE);
  display.fillRect(pipeX, pipeGapY + pipeGap, pipeWidth, display.height() - pipeGapY - pipeGap, SH110X_WHITE);
}

void resetGame() {
  birdY = display.height() / 2;
  birdVelocity = 0;
  score = 0;
  pipeX = display.width();
  pipeGapY = random(10, display.height() - pipeGap - 10);
  gameStarted = false;
  gameOver = false;
}

bool isButtonPressed() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    unsigned long currentTime = millis();
    if (currentTime - lastButtonPress > debounceDelay) {
      lastButtonPress = currentTime;
      return true;
    }
  }
  return false;
}

void loop() {
  // Clear the display
  display.clearDisplay();

  if (!gameStarted) {
    display.setCursor(10, 20);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print("Press button to start");

    drawBird(); // Draw the bird in the initial position

    if (isButtonPressed()) {
      gameStarted = true;
      birdVelocity = lift; // Start the game with an initial lift
    }
  } else if (gameOver) {
    display.setCursor(10, 20);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print("Game Over!");
    display.setCursor(10, 30);
    display.print("Press to restart");

    if (isButtonPressed()) {
      resetGame();
    }
  } else {
    if (isButtonPressed()) {
      birdVelocity = lift; // Apply lift when button is pressed
    }

    birdVelocity += gravity; // Apply gravity
    birdY += birdVelocity; // Update bird position

    // Move pipe
    pipeX -= 2;
    if (pipeX < -pipeWidth) {
      pipeX = display.width();
      pipeGapY = random(10, display.height() - pipeGap - 10);
      score++;
    }

    // Check for collision
    if (birdY - 3 < 0 || birdY + 3 > display.height() || 
        (birdY - 3 < pipeGapY && pipeX < 20 && pipeX + pipeWidth > 20) ||
        (birdY + 3 > pipeGapY + pipeGap && pipeX < 20 && pipeX + pipeWidth > 20)) {
      gameOver = true;
    }

    drawBird();
    drawPipe();

    display.setCursor(0, 0);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print("Score: ");
    display.print(score);
  }

  display.display();
}
