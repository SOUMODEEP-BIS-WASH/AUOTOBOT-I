#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <stdlib.h> // For random()

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int eyeX = 32; // Initial X position of the eyes
int eyeY = 16; // Initial Y position of the eyes

// Define the five positions
struct Position {
  int x;
  int y;
};
Position lookAroundPositions[5] = {
  {30, 16},  // Extreme left
  {36, 16}, // Bit left to the center
  {40, 16}, // Center
  {48, 16}, // Bit right
  {56, 16}  // Extreme right
};
Position positions[5] = {
  {32, 16}, // Center
  {48, 16},  // Top right
  {30, 16},   // Top left
  {48, 24}, // Bottom right
  {30, 24}   // Bottom left
};

void setup() {
  // Initialize the display
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.display();
  randomSeed(analogRead(0)); // Initialize random seed
}
void drawHappyEyes(int x, int y) {
  display.clearDisplay();

  // Left eye: 16x16 rounded rectangle
  display.fillRoundRect(x - 8, y - 8, 30, 16, 10, SSD1306_WHITE);
  
    display.fillCircle(x+7, y + 12,15, SSD1306_BLACK); // Carve out bottom part to create happy effect
  

  // Right eye: 16x16 rounded rectangle (64 pixels to the right of the left eye)
  display.fillRoundRect(x + 48, y - 8, 30, 16, 10, SSD1306_WHITE);
  
    display.fillCircle(x + 63, y + 12,15, SSD1306_BLACK); // Carve out bottom part to create happy effect
  

  display.display();
}
void drawEyes(int x, int y) {
  display.clearDisplay();

  // Left eye: 16x16 rounded rectangle
  display.fillRoundRect(x - 8, y - 8, 30, 16, 4, SSD1306_WHITE);

  // Right eye: 16x16 rounded rectangle (64 pixels to the right of the left eye)
  display.fillRoundRect(x + 48, y - 8, 30, 16, 4, SSD1306_WHITE);

  display.display();
}

void drawShakeEyes(int x, int y) {
  display.clearDisplay();

  // Left eye: 16x16 rounded rectangle
  display.fillRoundRect(x - 8, y - 8, 30, 24, 4, SSD1306_WHITE);

  // Right eye: 16x16 rounded rectangle (64 pixels to the right of the left eye)
  display.fillRoundRect(x + 48, y - 8, 30, 24, 4, SSD1306_WHITE);

  display.display();
}

void moveEyesSmoothly(int targetX, int targetY) {
  int steps = 20; // Number of steps for smooth movement

  // Calculate step sizes for X and Y
  float stepX = (float)(targetX - eyeX) / steps;
  float stepY = (float)(targetY - eyeY) / steps;

  // Smoothly move eyes to target position
  for (int i = 0; i < steps; i++) {
    eyeX += stepX;
    eyeY += stepY;

    // Ensure eyes stay within screen bounds
    //eyeX = constrain(eyeX, 0, SCREEN_WIDTH - 64); // Constrain X position
    //eyeY = constrain(eyeY, 0, SCREEN_HEIGHT - 16); // Constrain Y position

    drawEyes((int)eyeX, (int)eyeY);
    delay(20); // Adjust speed of movement
  }
}

void blinkEyes() {
  display.clearDisplay();

  // Left eye: Small square
  display.fillRoundRect(eyeX - 8, eyeY, 25, 4,4, SSD1306_WHITE);

  // Right eye: Small square
  display.fillRoundRect(eyeX + 48, eyeY, 25, 4,4, SSD1306_WHITE);

  display.display();
  delay(1000); // Adjust blink speed as needed

  // Redraw the eyes normally
  drawEyes((int)eyeX, (int)eyeY);
}
void shakeEyes() {
  int shakeAmount = 3; // The range of shaking

  for (int i = 0; i < 20; i++) {
    int shakeX = eyeX + random(-shakeAmount, shakeAmount);
    int shakeY = eyeY + random(-shakeAmount, shakeAmount);
    drawShakeEyes(shakeX, shakeY);
    delay(50); // Adjust speed of shaking
  }
}
void lookAround() {
  for (int i = 0; i < 5; i++) {
    Position targetPosition = lookAroundPositions[i];
    moveEyesSmoothly(targetPosition.x, targetPosition.y);
    delay(500); // Pause at each position
  }
}
void Cheeky(int x, int y) {
  display.clearDisplay();

  // Left eye: 16x16 rounded rectangle
  display.fillRoundRect(x - 8, y - 8, 30, 16, 4, SSD1306_WHITE);

  // Right eye: 16x16 rounded rectangle (64 pixels to the right of the left eye)
 // Right eye: 16x16 rounded rectangle (64 pixels to the right of the left eye)
  display.fillRoundRect(x + 48, y - 8, 30, 15, 10, SSD1306_WHITE);
  
    display.fillCircle(x + 63, y + 8,15, SSD1306_BLACK); // Carve out bottom part to create happy effect
  display.display();
}
void loop() {
  // Move eyes to a random predefined position every 2 seconds

  lookAround();
  drawHappyEyes(eyeX, eyeY);
  delay(2000);
  drawEyes(eyeX, eyeY);
  delay(1000);
  Cheeky(eyeX,eyeY);
  delay(1000);
  int randomIndex = random(0, 5); // Get a random index from 0 to 4
  Position targetPosition = positions[randomIndex]; // Get the target position from the array
  moveEyesSmoothly(targetPosition.x, targetPosition.y);
  delay(2000); // Delay to display the new position
 //lookAround(); 
shakeEyes();
delay(1000);
  // Blink eyes
  blinkEyes();
  delay(1000);
}
