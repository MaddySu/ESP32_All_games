This Arduino code is designed to run on a microcontroller equipped with an SH1106 OLED display, multiple buttons, and implements a simple game menu system with three 
different games: **Flying Bird**, **Ping Pong**, and **Snake**. The code uses the Adafruit GFX library and the Adafruit SH110X library to control the OLED display.

### Key Components:

1. **Libraries Used:**
   - `Wire.h`: Used for I2C communication.
   - `Adafruit_GFX.h` and `Adafruit_SH110X.h`: Provide the functionality to draw shapes, text, and bitmaps on the SH1106 OLED display.

2. **Hardware Setup:**
   - **OLED Display**: Controlled via I2C, used to display the game graphics and menu.
   - **Buttons**: Five buttons are used to interact with the game:
     - `BUTTON1_PIN` (Pin 12): Menu selection for Flying Bird.
     - `BUTTON2_PIN` (Pin 13): Menu selection for Ping Pong.
     - `BUTTON3_PIN` (Pin 14): Menu selection for Snake.
     - `BUTTON4_PIN` (Pin 27): Game control button, e.g., jump in Flying Bird.
     - `BUTTON5_PIN` (Pin 26): Exit to menu button.

3. **Games Implemented:**
   - **Flying Bird**:
     - A simple side-scrolling game where a bird must avoid obstacles (pipes) by jumping. The bird is affected by gravity and can be lifted by pressing a button.
     - The game ends when the bird collides with an obstacle or the screen boundaries.
   - **Ping Pong**:
     - A two-player Pong game where players control paddles to keep a ball in play. The game keeps score and ends when one player reaches a set score limit.
   - **Snake**:
     - A classic snake game where the player controls a snake to eat food and grow longer. The game ends if the snake collides with the walls or itself.

4. **Game State Management:**
   - The `GameState` enum defines the current state of the game (`MENU`, `FLYING_BIRD`, `PING_PONG`, `SNAKE`).
   - The `loop()` function checks the current state and calls the corresponding function to either display the menu or play the selected game.

5. **Game Mechanics:**
   - **Flying Bird**:
     - The bird's position is controlled by gravity and lift. The pipes move horizontally, and the game checks for collisions between the bird and the pipes or the screen edges.
   - **Ping Pong**:
     - Paddles are controlled by the players, and the ball bounces between them. The game checks for collisions with the paddles and the screen edges.
   - **Snake**:
     - The snake moves continuously in the selected direction. The game checks for collisions with the walls, itself, and food. Eating food increases the snake's length and score.

6. **Menu System:**
   - The menu allows the player to select one of the three games using the buttons. Once a game is selected, the corresponding game loop starts, and the player can play the game until it ends or they choose to exit to the menu.

### Summary:
This code creates an interactive, multi-game environment on an Arduino platform using an OLED display. It showcases the versatility of microcontroller-based projects, integrating real-time gameplay, 
display management, and input handling to deliver a simple yet entertaining gaming experience. The modular design allows for easy addition of new games or features.
