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
#define BORDER_TOP 8
#define BORDER_BOTTOM 64
#define BORDER_LEFT 0
#define BORDER_RIGHT 128

#define SNAKE_SIZE 3
#define INITIAL_SNAKE_LENGTH 5
#define FOOD_SIZE 3

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int snakeX[100] = {0};
int snakeY[100] = {0};
int snakeLength = INITIAL_SNAKE_LENGTH;

int foodX;
int foodY;

int direction = RIGHT;
bool gameRunning = false;

int score = 0;

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

  // Display start screen
  displayStartScreen();
  waitForKeyPress();
  resetGame();
}

void displayStartScreen() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 20);
  display.print("Press key to start");
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
  // Initialize snake position
  for (int i = 0; i < INITIAL_SNAKE_LENGTH; i++) {
    snakeX[i] = 30 - i * SNAKE_SIZE;
    snakeY[i] = 30;
  }
  snakeLength = INITIAL_SNAKE_LENGTH;
  direction = RIGHT;
  placeFood();
  score = 0;
  gameRunning = true;
}

void placeFood() {
  foodX = random(BORDER_LEFT + SNAKE_SIZE, BORDER_RIGHT - SNAKE_SIZE) / FOOD_SIZE * FOOD_SIZE;
  foodY = random(BORDER_TOP + SNAKE_SIZE, BORDER_BOTTOM - SNAKE_SIZE) / FOOD_SIZE * FOOD_SIZE;
}

void drawSnake() {
  for (int i = 0; i < snakeLength; i++) {
    display.fillRect(snakeX[i], snakeY[i], SNAKE_SIZE, SNAKE_SIZE, SH110X_WHITE);
  }
}

void drawFood() {
  display.fillRect(foodX, foodY, FOOD_SIZE, FOOD_SIZE, SH110X_WHITE);
}

void drawBorder() {
  display.drawRect(BORDER_LEFT, BORDER_TOP, SCREEN_WIDTH, 56, SH110X_WHITE);
}

void updateSnake() {
  // Move the body
  for (int i = snakeLength - 1; i > 0; i--) {
    snakeX[i] = snakeX[i - 1];
    snakeY[i] = snakeY[i - 1];
  }

  // Move the head
  switch (direction) {
    case UP:    snakeY[0] -= SNAKE_SIZE; break;
    case DOWN:  snakeY[0] += SNAKE_SIZE; break;
    case LEFT:  snakeX[0] -= SNAKE_SIZE; break;
    case RIGHT: snakeX[0] += SNAKE_SIZE; break;
  }
}

void checkCollision() {
  // Check collision with walls
  if (snakeX[0] < BORDER_LEFT || snakeX[0] >= BORDER_RIGHT ||
      snakeY[0] < BORDER_TOP || snakeY[0] >= BORDER_BOTTOM) {
    gameRunning = false;
  }

  // Check collision with itself
  for (int i = 1; i < snakeLength; i++) {
    if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
      gameRunning = false;
    }
  }

  // Check collision with food
  if (snakeX[0] == foodX && snakeY[0] == foodY) {
    snakeLength++;
    score++;
    placeFood();
  }
}

void loop() {
  if (gameRunning) {
    // Clear the display
    display.clearDisplay();

    // Read button states
    if (digitalRead(UP_BUTTON_PIN) == LOW && direction != DOWN) {
      direction = UP;
    }
    if (digitalRead(DOWN_BUTTON_PIN) == LOW && direction != UP) {
      direction = DOWN;
    }
    if (digitalRead(LEFT_BUTTON_PIN) == LOW && direction != RIGHT) {
      direction = LEFT;
    }
    if (digitalRead(RIGHT_BUTTON_PIN) == LOW && direction != LEFT) {
      direction = RIGHT;
    }

    // Update snake position
    updateSnake();

    // Check for collisions
    checkCollision();

    // Draw border
    drawBorder();

    // Draw snake and food
    drawSnake();
    drawFood();

    // Display score
    display.setCursor(38, 0);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print("Score: ");
    display.print(score);

    // Display the frame
    display.display();

    delay(100); // Adjust the speed of the game
  } else {
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 5);
    display.print("Game Over!");
    display.setTextSize(2);
    display.setCursor(15, 20);
    display.print("Score: ");
    display.print(score);
    display.setTextSize(1);
    display.setCursor(0, 40);
    display.print("Press key to restart");
    display.display();
    waitForKeyPress();
    resetGame();
  }
}
