#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


#define OLED_MOSI   9
#define OLED_CLK    10
#define OLED_DC     11
#define OLED_CS     12
#define OLED_RESET 13
// OLED display
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire, OLED_RESET);

// Define pin numbers for buttons
#define PADDLE1_UP_PIN 12
#define PADDLE1_DOWN_PIN 14
#define PADDLE2_UP_PIN 27
#define PADDLE2_DOWN_PIN 26

// Game variables
int paddle1Y = 26;
int paddle2Y = 26;
const int paddleHeight = 12;
const int paddleWidth = 2;

int ballX;
int ballY;
float ballVelocityX;
float ballVelocityY;
const int ballSize = 3;

int score1 = 0;
int score2 = 0;

bool gameRunning = false;
bool gameStarted = false;


#define YT_BMPWIDTH  128 // Replace with the actual width of your bitmap
#define YT_BMPHEIGHT 56 // Replace with the actual height of your bitmap


const unsigned char bitmap_YT[] PROGMEM = { 
  
};



void setup() {
  Serial.begin(115200);

  // Initialize display
  display.begin(0x3c, true); // initialize with the I2C addr 0x3c
  display.drawBitmap(
    (display.width()  - YT_BMPWIDTH ) / 2,
    (display.height() - YT_BMPHEIGHT) / 2,
    bitmap_YT, YT_BMPWIDTH, YT_BMPHEIGHT, 1);
    display.clearDisplay();
  display.drawBitmap(0, 0, bitmap_YT, 128, 56, FWRITE);
  display.display(); // show splashscreen
  delay(3000);
  display.clearDisplay();

  // Initialize button pins
  pinMode(PADDLE1_UP_PIN, INPUT_PULLUP);
  pinMode(PADDLE1_DOWN_PIN, INPUT_PULLUP);
  pinMode(PADDLE2_UP_PIN, INPUT_PULLUP);
  pinMode(PADDLE2_DOWN_PIN, INPUT_PULLUP);

  // Initialize random seed based on analog pin
  randomSeed(analogRead(0));

  // Display start screen
  displayStartScreen();
}

void drawPaddle(int x, int y) {
  display.fillRect(x, y, paddleWidth, paddleHeight, SH110X_WHITE);
}

void drawBall() {
  display.fillRect(ballX, ballY, ballSize, ballSize, SH110X_WHITE);
}

void updateBall() {
  ballX += ballVelocityX;
  ballY += ballVelocityY;

  // Bounce off top and bottom
  if (ballY <= 0 || ballY >= display.height() - ballSize) {
    ballVelocityY = -ballVelocityY;
  }

  // Check for paddle collisions
  if (ballX <= paddleWidth) {
    if (ballY >= paddle1Y && ballY <= paddle1Y + paddleHeight) {
      ballVelocityX = -ballVelocityX;
      ballVelocityY = random(-2, 3); // Random vertical velocity (-2, -1, 0, 1, 2)
    } else {
      score2++;
      if (score2 >= 5) {
        displayWinner("Player 2");
        gameRunning = false;
      } else {
        resetBall();
      }
    }
  } else if (ballX >= display.width() - paddleWidth - ballSize) {
    if (ballY >= paddle2Y && ballY <= paddle2Y + paddleHeight) {
      ballVelocityX = -ballVelocityX;
      ballVelocityY = random(-2, 3); // Random vertical velocity (-2, -1, 0, 1, 2)
    } else {
      score1++;
      if (score1 >= 5) {
        displayWinner("Player 1");
        gameRunning = false;
      } else {
        resetBall();
      }
    }
  }
}

void resetBall() {
  ballX = display.width() / 2 - ballSize / 2;
  ballY = display.height() / 2 - ballSize / 2;
  // Randomize initial ball direction
  ballVelocityX = random(2) == 0 ? -1 : 1; // Increase horizontal speed
  ballVelocityY = random(-1, 1); // Increase vertical speed range (-2, -1, 0, 1, 2)
}

void resetGame() {
  score1 = 0;
  score2 = 0;
  paddle1Y = 26; // Reset paddle positions
  paddle2Y = 26;
  gameRunning = true;
  resetBall();
}

void displayWinner(const char* winner) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(10, 20);
  display.print(winner);
  display.setCursor(10, 40);
  display.print("wins!");
  display.display();
  delay(2000); // Delay to show the winner message
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 30);
  display.print("Press any key");
  display.setCursor(10, 40);
  display.print("to restart");
  display.display();
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
    if (digitalRead(PADDLE1_UP_PIN) == LOW || digitalRead(PADDLE1_DOWN_PIN) == LOW ||
        digitalRead(PADDLE2_UP_PIN) == LOW || digitalRead(PADDLE2_DOWN_PIN) == LOW) {
      break;
    }
    delay(100); // Check for button press every 100ms
  }
}

void waitForRestart() {
  while (true) {
    if (digitalRead(PADDLE1_UP_PIN) == LOW || digitalRead(PADDLE1_DOWN_PIN) == LOW ||
        digitalRead(PADDLE2_UP_PIN) == LOW || digitalRead(PADDLE2_DOWN_PIN) == LOW) {
      resetGame();
      break;
    }
    delay(100); // Check for button press every 100ms
  }
}

void loop() {
  if (!gameStarted) {
    waitForKeyPress();
    gameStarted = true;
    gameRunning = true;
    resetGame();
  }

  if (gameRunning) {
    // Clear the display
    display.clearDisplay();

    // Read button states
    if (digitalRead(PADDLE1_UP_PIN) == LOW && paddle1Y > 0) {
      paddle1Y -= 2;
    }
    if (digitalRead(PADDLE1_DOWN_PIN) == LOW && paddle1Y < display.height() - paddleHeight) {
      paddle1Y += 2;
    }
    if (digitalRead(PADDLE2_UP_PIN) == LOW && paddle2Y > 0) {
      paddle2Y -= 2;
    }
    if (digitalRead(PADDLE2_DOWN_PIN) == LOW && paddle2Y < display.height() - paddleHeight) {
      paddle2Y += 2;
    }

    // Update ball position
    updateBall();

    // Draw paddles and ball
    drawPaddle(0, paddle1Y);
    drawPaddle(display.width() - paddleWidth, paddle2Y);
    drawBall();

    // Display scores
    display.setCursor(30, 0);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print(score1);
    display.setCursor(display.width() - 40, 0);
    display.print(score2);

    // Display the frame
    display.display();
  } else {
    // Game over, wait for reset
    waitForRestart();
  }
}
