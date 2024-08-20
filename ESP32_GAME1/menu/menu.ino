#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define OLED_RESET    -1
Adafruit_SH110X display = Adafruit_SH110X(128, 64, &Wire, OLED_RESET);

#define BUTTON1_PIN 12  // Menu select Flying Bird
#define BUTTON2_PIN 13  // Menu select Ping Pong
#define BUTTON3_PIN 14  // Menu select Snake
#define BUTTON4_PIN 27  // Game control button (e.g., jump in Flying Bird)
#define BUTTON5_PIN 26  // Exit to menu

enum GameState { MENU, FLYING_BIRD, PING_PONG, SNAKE };
GameState currentState = MENU;

void setup() {
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);
  pinMode(BUTTON5_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  display.begin(SH1106_I2C_ADDRESS, OLED_RESET);
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  switch (currentState) {
    case MENU:
      displayMenu();
      break;
    case FLYING_BIRD:
      playFlyingBird();
      break;
    case PING_PONG:
      playPingPong();
      break;
    case SNAKE:
      playSnake();
      break;
  }
}

void displayMenu() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.println("Select Game:");
  display.println("1. Flying Bird");
  display.println("2. Ping Pong");
  display.println("3. Snake");
  display.display();

  if (digitalRead(BUTTON1_PIN) == LOW) {
    currentState = FLYING_BIRD;
    delay(200);  // Debounce delay
  } else if (digitalRead(BUTTON2_PIN) == LOW) {
    currentState = PING_PONG;
    delay(200);
  } else if (digitalRead(BUTTON3_PIN) == LOW) {
    currentState = SNAKE;
    delay(200);
  }
}

void playFlyingBird() {
  int birdY = 32;
  int gravity = 1;
  int velocity = 0;
  int birdX = 20;

  while (currentState == FLYING_BIRD) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Flying Bird Game");
    
    if (digitalRead(BUTTON4_PIN) == LOW) {
      velocity = -5;
    }

    velocity += gravity;
    birdY += velocity;

    if (birdY >= 63) {
      birdY = 63;
      velocity = 0;
    } else if (birdY <= 0) {
      birdY = 0;
      velocity = 0;
    }

    display.fillRect(birdX, birdY, 5, 5, SSD1306_WHITE);
    display.display();
    delay(50);

    if (digitalRead(BUTTON5_PIN) == LOW) { // Exit to menu
      currentState = MENU;
      delay(200);
    }
  }
}

void playPingPong() {
  int ballX = 64;
  int ballY = 32;
  int ballDX = 2;
  int ballDY = 2;
  int paddleY = 32;
  int paddleHeight = 10;
  
  while (currentState == PING_PONG) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Ping Pong Game");
    
    if (digitalRead(BUTTON4_PIN) == LOW) {
      paddleY -= 2;
    }
    if (digitalRead(BUTTON2_PIN) == LOW) {
      paddleY += 2;
    }

    ballX += ballDX;
    ballY += ballDY;

    if (ballX <= 0 || ballX >= 127) {
      ballDX = -ballDX;
    }
    if (ballY <= 0 || ballY >= 63) {
      ballDY = -ballDY;
    }
    
    if (ballX <= 10 && ballY >= paddleY && ballY <= paddleY + paddleHeight) {
      ballDX = -ballDX;
    }

    display.fillRect(0, paddleY, 3, paddleHeight, SSD1306_WHITE);
    display.fillRect(ballX, ballY, 3, 3, SSD1306_WHITE);
    display.display();
    delay(50);

    if (digitalRead(BUTTON5_PIN) == LOW) { // Exit to menu
      currentState = MENU;
      delay(200);
    }
  }
}

void playSnake() {
  int snakeX[50] = {20, 19, 18, 17, 16};
  int snakeY[50] = {30, 30, 30, 30, 30};
  int snakeLength = 5;
  int direction = 1; // 0 = up, 1 = right, 2 = down, 3 = left
  int foodX = random(0, 127);
  int foodY = random(0, 63);
  bool gameover = false;

  while (currentState == SNAKE && !gameover) {
    display.clearDisplay();
    display.setTextSize(1);
    display.setCursor(0, 0);
    display.println("Snake Game");

    if (digitalRead(BUTTON4_PIN) == LOW) {
      direction = (direction == 0) ? 3 : direction - 1;
    }
    if (digitalRead(BUTTON2_PIN) == LOW) {
      direction = (direction == 3) ? 0 : direction + 1;
    }

    for (int i = snakeLength - 1; i > 0; i--) {
      snakeX[i] = snakeX[i - 1];
      snakeY[i] = snakeY[i - 1];
    }

    if (direction == 0) snakeY[0]--;
    if (direction == 1) snakeX[0]++;
    if (direction == 2) snakeY[0]++;
    if (direction == 3) snakeX[0]--;

    if (snakeX[0] == foodX && snakeY[0] == foodY) {
      snakeLength++;
      foodX = random(0, 127);
      foodY = random(0, 63);
    }

    for (int i = 0; i < snakeLength; i++) {
      display.drawPixel(snakeX[i], snakeY[i], SSD1306_WHITE);
    }

    display.drawPixel(foodX, foodY, SSD1306_WHITE);
    display.display();
    delay(100);

    if (snakeX[0] < 0 || snakeX[0] >= 128 || snakeY[0] < 0 || snakeY[0] >= 64) {
      gameover = true;
    }
    for (int i = 1; i < snakeLength; i++) {
      if (snakeX[0] == snakeX[i] && snakeY[0] == snakeY[i]) {
        gameover = true;
      }
    }

    if (digitalRead(BUTTON5_PIN) == LOW) { // Exit to menu
      currentState = MENU;
      delay(200);
    }
  }
}
