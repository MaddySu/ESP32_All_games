#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define OLED_RESET -1
Adafruit_SH1106G display = Adafruit_SH1106G(128, 64, &Wire);

#define BUTTON1_PIN 12  // Menu select Flying Bird
#define BUTTON2_PIN 13  // Menu select Ping Pong
#define BUTTON3_PIN 14  // Menu select Snake
#define BUTTON4_PIN 27  // Game control button (e.g., jump in Flying Bird)
#define BUTTON5_PIN 26  // Exit to menu


const unsigned char bitmap_YT[] PROGMEM = { 
  
  0x00,0x00,0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ........................##......................................................................................................
  0x00,0x00,0x01,0xE0,0x00,0x00,0x00,0x01,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .......................####....................................####.............................................................
  0x00,0x00,0x03,0xE0,0x00,0x00,0x00,0x01,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ......................#####....................................#####............................................................
  0x00,0x00,0x03,0xE0,0x00,0x00,0x00,0x01,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ......................#####....................................#####............................................................
  0x00,0x00,0x01,0xF0,0x00,0x00,0x00,0x01,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .......................#####...................................#####............................................................
  0x00,0x00,0x00,0x18,0x03,0xFF,0xC0,0x02,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ...........................##.........############............#.###.............................................................
  0x00,0x00,0x00,0x0C,0x1F,0xFF,0xF8,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ............................##.....##################........#..................................................................
  0x00,0x00,0x00,0x04,0x7F,0xFF,0xFE,0x08,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .............................#...######################.....#...................................................................
  0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0x90,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ..............................###########################..#....................................................................
  0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ..............................##############################....................................................................
  0x00,0x00,0x00,0x07,0xFF,0xFF,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .............................##############################.....................................................................
  0x00,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ............................################################....................................................................
  0x00,0x00,0x00,0x1F,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ...........................##################################...................................................................
  0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ..........................####################################..................................................................
  0x00,0x00,0x00,0x40,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .........................#......#########################.......................................................................
  0x00,0x00,0x00,0x00,0x3F,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ..................................#####################.........................................................................
  0x07,0xF8,0x00,0x7F,0x8F,0xFF,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .....########............########...#################....#######................................................................
  0x3F,0xFF,0x81,0xFF,0xE0,0x00,0xF3,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ..###############......############.............####..############..............................................................
  0x7F,0xFF,0xE3,0xFF,0xF3,0xFE,0x07,0xFF,0xE0,0x00,0x1F,0xFF,0xFF,0x0F,0xFF,0xF8, // .##################...##############..#########......##############................#####################....#################...
  0x60,0x01,0xF7,0xC1,0xFF,0xFF,0x8F,0xC1,0xFF,0xFF,0xFF,0xFF,0xFF,0xDF,0xFF,0xF8, // .##............#####.#####.....##################...######.....###########################################.##################...
  0x60,0x00,0x7F,0x00,0x7F,0xFF,0xFF,0x00,0x7F,0xFF,0xFC,0x1C,0x01,0xFC,0x00,0x08, // .##..............#######.........#######################.........#####################.....###.........#######..............#...
  0x60,0x00,0x3E,0x00,0x1C,0x00,0xFE,0x00,0x3C,0x04,0x38,0x0C,0x00,0x7C,0x00,0x18, // .##...............#####............###..........#######...........####.......#....###.......##...........#####.............##...
  0x60,0x00,0x1C,0x78,0x0C,0x00,0x3C,0x0F,0x1C,0x04,0x08,0x0C,0x00,0x1C,0x00,0x18, // .##................###...####.......##............####......####...###.......#......#.......##.............###.............##...
  0x20,0x00,0x1C,0xFE,0x0C,0x00,0x18,0x3F,0xCC,0x04,0x18,0x0C,0x00,0x0C,0x00,0x30, // ..#................###..#######.....##.............##.....########..##.......#.....##.......##..............##............##....
  0x20,0x00,0x19,0xFF,0x04,0x00,0x18,0x7F,0xCC,0x00,0x18,0x0C,0x00,0x0C,0x00,0x30, // ..#................##..#########.....#.............##....#########..##.............##.......##..............##............##....
  0x20,0x00,0x1B,0xFF,0x84,0x00,0x10,0x7F,0xEC,0x00,0x38,0x0C,0x00,0x04,0x00,0x60, // ..#................##.###########....#.............#.....##########.##............###.......##...............#...........##.....
  0x20,0x10,0x1B,0xFF,0x84,0x04,0x10,0xFF,0xE4,0x00,0x38,0x0C,0x00,0x04,0x00,0x60, // ..#........#.......##.###########....#.......#.....#....###########..#............###.......##...............#...........##.....
  0x20,0x1C,0x13,0xFF,0x84,0x06,0x10,0xFF,0xF4,0x00,0x78,0x0C,0x06,0x07,0xC0,0xC0, // ..#........###.....#..###########....#.......##....#....############.#...........####.......##.......##......#####......##......
  0x20,0x1C,0x13,0xFF,0x82,0x06,0x30,0xFF,0xF4,0x00,0xF8,0x0C,0x07,0x07,0xC0,0xC0, // ..#........###.....#..###########.....#......##...##....############.#..........#####.......##.......###.....#####......##......
  0x20,0x18,0x3B,0xF7,0x86,0x00,0x30,0xFF,0xF6,0x00,0xFC,0x0E,0x07,0x87,0x81,0xC0, // ..#........##.....###.######.####....##...........##....############.##.........######......###......####....####......###......
  0x20,0x00,0x7B,0xE7,0x86,0x00,0x70,0xFC,0xE6,0x01,0xFC,0x0E,0x07,0x87,0x81,0x80, // ..#..............####.#####..####....##..........###....######..###..##........#######......###......####....####......##.......
  0x20,0x00,0xFB,0xF7,0x86,0x04,0x70,0x7C,0xEE,0x00,0xFC,0x1E,0x07,0x0F,0x81,0xE0, // ..#.............#####.######.####....##......#...###.....#####..###.###.........######.....####......###....#####......####.....
  0x30,0x01,0xF9,0xFF,0x06,0x0E,0x38,0x7F,0xCE,0x00,0x7C,0x1E,0x07,0x0F,0x83,0xF0, // ..##...........######..#########.....##.....###...###....#########..###..........#####.....####......###....#####.....######....
  0x30,0x00,0xFC,0xFE,0x0E,0x04,0x38,0x3F,0xDE,0x08,0x3C,0x1E,0x06,0x0F,0x03,0xF0, // ..##............######..#######.....###......#....###.....########.####.....#.....####.....####......##.....####......######....
  0x30,0x10,0x7E,0x7C,0x1E,0x00,0x7C,0x0F,0x1E,0x0C,0x1C,0x1E,0x00,0x1F,0x00,0x30, // ..##.......#.....######..#####.....####..........#####......####...####.....##.....###.....####............#####..........##....
  0x30,0x10,0x3E,0x00,0x3E,0x00,0xFE,0x00,0x3E,0x0C,0x7C,0x1E,0x00,0x3F,0x00,0x60, // ..##.......#......#####...........#####.........#######...........#####.....##...#####.....####...........######.........##.....
  0x30,0x18,0x7F,0x80,0x7F,0xFF,0xEF,0x00,0x7F,0xFF,0xFF,0xFE,0x00,0xFE,0x00,0x60, // ..##.......##....########........##################.####.........##############################.........#######..........##.....
  0x3F,0xFD,0xFF,0xF3,0xFF,0xFF,0xCF,0xF3,0xFF,0xFF,0xDF,0xFF,0xFF,0xEF,0xFF,0xE0, // ..############.#############..####################..########..####################.########################.###############.....
  0x1F,0xFF,0xF3,0xFF,0xF1,0xFE,0x03,0xFF,0xE0,0x0F,0x00,0x0F,0xFF,0x8F,0xFF,0xC0, // ...#################..##############...########.......#############.........####............#############...##############......
  0x0F,0xFF,0xC1,0xFF,0xC0,0x00,0x71,0xFF,0xC0,0x00,0x00,0x03,0xFC,0x00,0x00,0x00, // ....##############.....###########...............###...###########............................########..........................
  0x00,0x03,0x00,0x7F,0x8F,0xFF,0xF8,0x7F,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ..............##.........########...#################....#######................................................................
  0x00,0x00,0x00,0x00,0x3F,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ..................................#####################.........................................................................
  0x00,0x00,0x00,0x41,0xFF,0xFF,0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .........................#.....##########################.......................................................................
  0x00,0x00,0x00,0x7F,0xFF,0xFF,0xFF,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .........................######################################.................................................................
  0x00,0x00,0x00,0x3F,0xFC,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ..........................############...........#############..................................................................
  0x00,0x00,0x00,0x3F,0xFE,0x00,0x7F,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ..........................#############..........#############..................................................................
  0x00,0x00,0x00,0x3F,0xFF,0x81,0xFF,0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ..........................###############......###############..................................................................
  0x00,0x00,0x00,0x1F,0xFF,0xEF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ...........................################.#################...................................................................
  0x00,0x00,0x00,0x0F,0xFF,0xFF,0xFF,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ............................################################....................................................................
  0x00,0x00,0x00,0x03,0xFF,0xFF,0xFF,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ..............................############################......................................................................
  0x00,0x00,0x00,0x00,0xFF,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ................................########################........................................................................
  0x00,0x00,0x00,0x00,0x3F,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // ..................................###################...........................................................................
  0x00,0x00,0x00,0x00,0x07,0xFF,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .....................................##############.............................................................................
  0x00,0x00,0x00,0x00,0x01,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .......................................#########................................................................................
  0x00,0x00,0x00,0x00,0x00,0x7C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // .........................................#####..................................................................................
  0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00  // ...........................................#....................................................................................

};


/////////////////////////////////////////////FB-stsrt//////////////////////////////////////////////////////////////////////////////////////////////////

// Game variables
float birdY;
float birdVelocity;
const float gravity = 0.3;  // Gravity affecting the bird
const float lift = -3;      // The lift force when the button is pressed (bounciness)
int scoreFB;
bool gameStartedFB;
bool gameOver;

const int pipeWidth = 8;
const int pipeGap = 30;
float pipeX;
float pipeGapY;

unsigned long lastButtonPress = 0;
const unsigned long debounceDelay = 50;

/////////////////////////////////////////////FB-stsrt//////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////ping_pong-stsrt//////////////////////////////////////////////////////////////////////////////////////////////////

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


#define YT_BMPWIDTH 128  // Replace with the actual width of your bitmap
#define YT_BMPHEIGHT 56  // Replace with the actual height of your bitmap



/////////////////////////////////////////////ping_pong-end//////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////sank-stsrt//////////////////////////////////////////////////////////////////////////////////////////////////
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

int snakeX[100] = { 0 };
int snakeY[100] = { 0 };
int snakeLength = INITIAL_SNAKE_LENGTH;

int foodX;
int foodY;

int direction = RIGHT;

int score = 0;


enum GameState { MENU,
                 FLYING_BIRD,
                 PING_PONG,
                 SNAKE };
GameState currentState = MENU;
/////////////////////////////////////////////sank-end//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////ping_pong-stsrt//////////////////////////////////////////////////////////////////////////////////////////////////

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
      ballVelocityY = random(-2, 3);  // Random vertical velocity (-2, -1, 0, 1, 2)
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
      ballVelocityY = random(-2, 3);  // Random vertical velocity (-2, -1, 0, 1, 2)
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
  ballVelocityX = random(2) == 0 ? -1 : 1;  // Increase horizontal speed
  ballVelocityY = random(-1, 1);            // Increase vertical speed range (-2, -1, 0, 1, 2)
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
  delay(2000);  // Delay to show the winner message
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
    if (digitalRead(BUTTON1_PIN) == LOW || digitalRead(BUTTON3_PIN) == LOW || digitalRead(BUTTON4_PIN) == LOW || digitalRead(BUTTON5_PIN) == LOW) {
      break;
    }
    delay(100);  // Check for button press every 100ms
  }
}

void waitForRestart() {
  while (true) {
    if (digitalRead(BUTTON1_PIN) == LOW || digitalRead(BUTTON3_PIN) == LOW || digitalRead(BUTTON4_PIN) == LOW || digitalRead(BUTTON5_PIN) == LOW) {
      resetGame();
      break;
    }
    delay(100);  // Check for button press every 100ms
  }
}

/////////////////////////////////////////////ping_pong-end//////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);
  pinMode(BUTTON5_PIN, INPUT_PULLUP);

  Serial.begin(115200);
  display.begin(0x3c, true); 
  display.drawBitmap(
    (display.width()  - YT_BMPWIDTH ) / 2,
    (display.height() - YT_BMPHEIGHT) / 2,
    bitmap_YT, YT_BMPWIDTH, YT_BMPHEIGHT, 1); // initialize with the I2C addr 0x3c
  //display.display();
   display.clearDisplay();
   display.drawBitmap(0, 0, bitmap_YT, 128, 56, FWRITE);
  display.display();
  delay(5000);
  display.clearDisplay();

  // Initialize random seed based on analog pin
  randomSeed(analogRead(0));

  // Display start screen
  displayStartScreen();
  waitForKeyPress();
  resetGame();
}

/////////////////////////////////////////////sank-stsrt//////////////////////////////////////////////////////////////////////////////////////////////////


void resetGame() {
  // Initialize snake position sankresetGame
  for (int i = 0; i < INITIAL_SNAKE_LENGTH; i++) {
    snakeX[i] = 30 - i * SNAKE_SIZE;
    snakeY[i] = 30;
  }
  snakeLength = INITIAL_SNAKE_LENGTH;
  direction = RIGHT;
  placeFood();
  score = 0;
  gameRunning = true;

  //ping poing resetGame
  score1 = 0;
  score2 = 0;
  paddle1Y = 26;  // Reset paddle positions
  paddle2Y = 26;
  gameRunning = true;
  resetBall();

  //FB resetGame
  birdY = display.height() / 2;
  birdVelocity = 0;
  scoreFB = 0;
  pipeX = display.width();
  pipeGapY = random(10, display.height() - pipeGap - 10);
  gameStartedFB = false;
  gameOver = false;
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
    case UP: snakeY[0] -= SNAKE_SIZE; break;
    case DOWN: snakeY[0] += SNAKE_SIZE; break;
    case LEFT: snakeX[0] -= SNAKE_SIZE; break;
    case RIGHT: snakeX[0] += SNAKE_SIZE; break;
  }
}

void checkCollision() {
  // Check collision with walls
  if (snakeX[0] < BORDER_LEFT || snakeX[0] >= BORDER_RIGHT || snakeY[0] < BORDER_TOP || snakeY[0] >= BORDER_BOTTOM) {
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




/////////////////////////////////////////////sank-end//////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////FB-end//////////////////////////////////////////////////////////////////////////////////////////////////

void drawBird() {
  display.fillCircle(20, birdY, 3, SH110X_WHITE);
}

void drawPipe() {
  display.fillRect(pipeX, 0, pipeWidth, pipeGapY, SH110X_WHITE);
  display.fillRect(pipeX, pipeGapY + pipeGap, pipeWidth, display.height() - pipeGapY - pipeGap, SH110X_WHITE);
}



bool isButtonPressed() {
  if (digitalRead(BUTTON2_PIN) == LOW) {
    unsigned long currentTime = millis();
    if (currentTime - lastButtonPress > debounceDelay) {
      lastButtonPress = currentTime;
      return true;
    }
  }
  return false;
}

/////////////////////////////////////////////FB-end//////////////////////////////////////////////////////////////////////////////////////////////////

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
  display.clearDisplay();

  if (!gameStartedFB) {
    display.setCursor(2, 20);
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.print("Press button to start");

    //drawBird(); // Draw the bird in the initial position

    if (isButtonPressed()) {
      gameStartedFB = true;
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
      scoreFB++;
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
    display.print("scoreFB: ");
    display.print(scoreFB);
  }

  display.display();
   if (digitalRead(BUTTON5_PIN) == LOW) { // Exit to menu
      currentState = MENU;
      delay(200);
    }
}

void playPingPong() {
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
    if (digitalRead(BUTTON1_PIN) == LOW && paddle1Y > 0) {
      paddle1Y -= 2;
    }
    if (digitalRead(BUTTON2_PIN) == LOW && paddle1Y < display.height() - paddleHeight) {
      paddle1Y += 2;
    }
    if (digitalRead(BUTTON3_PIN) == LOW && paddle2Y > 0) {
      paddle2Y -= 2;
    }
    if (digitalRead(BUTTON4_PIN) == LOW && paddle2Y < display.height() - paddleHeight) {
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

   if (digitalRead(BUTTON5_PIN) == LOW) { // Exit to menu
      currentState = MENU;
      delay(200);
    }
}

void playSnake() {
  if (gameRunning) {
    // Clear the display
    display.clearDisplay();

    // Read button states
    if (digitalRead(BUTTON1_PIN) == LOW && direction != DOWN) {
      direction = UP;
    }
    if (digitalRead(BUTTON2_PIN) == LOW && direction != UP) {
      direction = DOWN;
    }
    if (digitalRead(BUTTON3_PIN) == LOW && direction != RIGHT) {
      direction = LEFT;
    }
    if (digitalRead(BUTTON4_PIN) == LOW && direction != LEFT) {
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

    delay(100 - score * 2.5);  // Adjust the speed of the game
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
   if (digitalRead(BUTTON5_PIN) == LOW) { // Exit to menu
      currentState = MENU;
      delay(200);
    }
}
