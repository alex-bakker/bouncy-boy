#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <SPI.h>

//Colour constants to be used in the game. 
#define BLUE 0xF800
#define BLACK 0x0000 
#define WHITE   0xFFFF
#define RED 0x00FF
#define GREEN 0x07E0
#define YELLOW 0x07FF 

#define C0 BLUE
#define C1 WHITE
#define C2 BLACK
#define C3 RED
#define C4 RED

#define MENU 1
#define GAME 2
#define DEATH 3

//Initialize the TFT display where 10, 8, 9 correspond to wiring done on the screen.
static Adafruit_ST7735 TFT = Adafruit_ST7735(10, 8, 9);

//2D array to represent the graphics of the player
static unsigned int person[30][20] = {
  {C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C1,C2,C2,C2,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C1,C1,C2,C2,C2,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C1,C1,C2,C2,C2,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C1,C1,C1,C1,C2,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C2,C2,C1,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C2,C2,C2,C1,C1,C1,C2,C2,C2,C2,C2,C2,C2,C2,C0,C0,C0},
  {C0,C0,C0,C2,C2,C2,C1,C1,C2,C2,C2,C2,C2,C2,C2,C2,C0,C0,C0,C0},
  {C0,C0,C0,C2,C2,C2,C1,C1,C2,C2,C2,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C2,C2,C2,C1,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C2,C2,C2,C1,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C2,C2,C2,C1,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C3,C1,C1,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C3,C3,C4,C1,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C3,C3,C4,C1,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C3,C3,C0,C4,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C3,C3,C0,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C3,C0,C3,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C1,C1,C1,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0},
  {C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0,C0}
};

//Important constants for bounds and collisions.
static const int WIDTH = 128;
static const int GROUND = 111; 
static const int TOP = 9;

static const int P_WIDTH = 20;
static const int P_HEIGHT = 30;

//Values of the joystick
const int Y_pin = 0; // analog pin connected to X output
const int X_pin = 1; // analog pin connected to Y output

//Values for the two buttons
const int jetBtn = 7;
const int shootBtn = 6;

//This holds what state the game is
//Value is used in main loop to determine what to do
static int gameState = MENU;

//Variables to hold values for the time elapsed since starting a new game
long long int timeStart = millis();
int timeDisplayed = 0;

//Variable to record sesion high score
int topScore = 0;

//Struct to represent the player model
static struct PLAYER {
  int lives = 5;
  int score = 0;
  int x = 20;
  int y = GROUND - P_HEIGHT;
  int velY = 0;
  bool isPowerOn;
} player; 

//Struct to represent a bullet (could put in array but arduino will lag too much)
//Stick to only max of one bullet
static struct BULLET {
  int x = 0;
  int y = 0;
  bool isAlive = false;
} bullet; 

static struct TARGET {
  int vel = 3;
  int x = 128;
  int y = 50;
  bool isAlive = true;
} target;


static struct BOOST {
  int x = 78;
  int y = 90;
  bool isAlive = true;
} boost;

//Method to draw the player given an x and y, based on the 2D array model
//Draws flames only when player is trying to fly up
void drawPlayer(int x, int y){
  bool fire = false;
  if(analogRead(Y_pin) > 300){
    fire = true;
  } 
  for(int i = 0; i < P_HEIGHT; i++){
    for(int k = 0; k < P_WIDTH; k++){
      if(fire){
        if(person[i][k] == C3) TFT.drawPixel(x+k, y+i, BLUE);
        else if(person[i][k] == C4) TFT.drawPixel(x+k, y+i, WHITE);
        else TFT.drawPixel(x+k, y+i, person[i][k]);
      } else TFT.drawPixel(x+k, y+i, person[i][k]);
     }
  }

//Handle leftover pixels when falling down
  if(player.velY > 2)
    TFT.fillRect(player.x, player.y - 5, 20, 5, BLUE);
  else if(player.velY > 1)
    TFT.drawFastHLine(player.x + 5, player.y - 1, 5, BLUE);
   if(isPlayerAbove() == false){TFT.fillRect(player.x+3, player.y-4,6,4,BLUE);}
}

//Method that draws the bullet - called in the bulletUpdate()
//Uses the bullets x and y, needs no params.
void drawBullet(){
  TFT.fillRect(bullet.x - 7, bullet.y, 2, 2, BLUE);
  TFT.fillRect(bullet.x, bullet.y, 2, 2, BLACK);
}

//Method to draw the target.
void drawTarget(){
  TFT.fillRect(target.x + target.vel, target.y, 10, 8, BLUE);
  TFT.fillRect(target.x, target.y, 8, 8, RED);
}

void drawBoost(){
  TFT.fillCircle(boost.x, boost.y, 2, YELLOW);
}

//Returns true if the player is in the air; false otherwise.
bool isPlayerAbove(){
  if(player.y + P_HEIGHT < GROUND) return true;
  return false;
}

//Check all of the bounds to keep the player in the screen
void checkBounds(){
  if(player.x <= 0)
    player.x = 0;
  if(player.x + P_WIDTH >= WIDTH)
    player.x = WIDTH - P_WIDTH;
  if(player.y <= TOP){
    player.y = TOP;
    player.velY = 0;
  }
  if(player.y + P_HEIGHT > GROUND){
    player.y = GROUND - P_HEIGHT;
    player.velY = 0;
  }
}

//***NOTE: Horizontal and Vertical velocity are completely independent of eachother.
void horizontalMovement(){
  if(analogRead(X_pin) < 350){
    player.x += (3 - analogRead(X_pin)/100);
  }
  if(analogRead(X_pin) > 650){
    player.x -= (analogRead(X_pin)/100 - 7);
  }
}

//Work on acceleration downwards.
void verticalMovement(){
   if(isPlayerAbove()){
    if(player.velY > -3 && analogRead(Y_pin) < 300)
      player.velY--;
    else if(player.velY < 4 && analogRead(Y_pin) > 300)
      player.velY++;
   } else {
      if(player.velY > -3 && analogRead(Y_pin) < 300)
        player.velY--;
   }
   delay(15);
   player.y += player.velY;
}

//Function to handle the bullet, handle both when the player shoots, and to delete the bullet from the screen.
void buttonUpdate(){
  bool shot = digitalRead(shootBtn);
  if(bullet.isAlive){
    bullet.x += 7;
    drawBullet();
    if(bullet.x > WIDTH)
      bullet.isAlive = false;
   } else {
     if(shot == HIGH){
        target.vel = 3;
        bullet.y = player.y + 7;
        bullet.x = player.x + 15;
        bullet.isAlive = true;
     }
   }
   //Need to fix how to re write the score
   //Other than that this all works properly.
   if(target.vel == 3 && digitalRead(jetBtn) == HIGH && player.score >= 10){
      TFT.setCursor(37, 1);
      TFT.setTextColor(BLACK);
      TFT.print(player.score);
      player.score -= 10;
      target.vel = 1;
      return;
   }
}

//Check the collision between bullet and target
//Player's score is updated here
bool collision(){
  if(bullet.x + 2 >= target.x && bullet.y >= target.y && bullet.y <= target.y + 8 && bullet.isAlive)
    return true;
  return false;
}

//Collision between player and target, will also be run in the target update
bool playerCollision(){
  if(player.x + P_WIDTH >= target.x && player.x < target.x + 8 && player.y < target.y + 8 && player.y + P_HEIGHT > target.y)
    return true;
  return false;
}

bool hitBoost(){
  if(player.x + P_WIDTH > boost.x && player.x < boost.x + 4 && player.y + P_HEIGHT > boost.y && player.y < boost.y + 4 && boost.isAlive) 
    return true;
  return false;
}
void updateScore(){
  TFT.setCursor(37,1);
  TFT.setTextColor(WHITE, BLACK);
  TFT.print(player.score);
  TFT.setCursor(100, 1);
  TFT.print(player.lives);
}

//Rather than check the players score every loop, we will call this in the two conditions where the player may lose a life.
void checkLives(){
  if(player.lives <= 0){
    gameState = DEATH;
  }
}

//This handles the lifecycle of a coin
void boostUpdate(){
  if(boost.isAlive){
    drawBoost();
    if(hitBoost()){
      TFT.fillCircle(boost.x, boost.y, 2, BLUE);
      boost.isAlive = false;
      player.score += 2;
    }
  } else {
    if(random(0, 1000) > 950){
      boost.x = random(10, 90);
      boost.y = random(10,90);
      boost.isAlive = true;
    }
  }
}

//This will handle the lifecycle of the target, and the collision detection
//Check score is called twice here: 1. player is hit 2.target escapes screen
void targetUpdate(){
  //Check collision and update target's location
  if(target.isAlive){
    target.x -= target.vel;
    drawTarget();
    if(collision()){
      player.score++;
      TFT.fillRect(bullet.x - 8, target.y, 18, 10, BLUE);
      bullet.isAlive = false;
      target.isAlive = false;
    }
    if(playerCollision()){
      player.lives--;
      target.isAlive = false;
      TFT.fillRect(target.x, target.y, 8, 8, BLUE);
    }
    //If the target makes it to the end of the screen, lose a life.
    if(target.x + 8 < 0){
      player.lives--;
      target.isAlive = false;
    }
  } else {
    target.isAlive = true;
    target.x = 128;
    target.y = random(10, 88);
  }
}

//Function to keep track of time alive
void timeTrack(){
  long int timeNow = millis();
  if(timeNow - timeStart > 1000){
    timeDisplayed++;
    timeStart = timeNow;
  } 
  TFT.setCursor(114, 119);
  TFT.setTextColor(BLACK,GREEN);
  TFT.print(timeDisplayed);
}

//Load the upper header which displays the score and missed.
void setHeader(){
  TFT.setCursor(1,1);
  TFT.setTextColor(WHITE);
  TFT.print("COINS:");
  TFT.setCursor(62,1);
  TFT.print("LIVES: ");
  TFT.setCursor(86,119);
  TFT.setTextColor(BLACK);
  TFT.print("TIME:");
}

//Load the background of the game.
void loadGame(){
  //Reset the player
  player.x = 20;
  player.y = GROUND - P_HEIGHT;
  player.lives = 5;
  player.score = 0;
  
  TFT.fillScreen(BLUE);
  TFT.drawFastHLine(0, 111, 128, BLACK);
  TFT.drawFastHLine(0, 112, 128, BLACK); 
  TFT.fillRect(0, 113, 128, 15, GREEN);
  TFT.fillRect(0, 0, 128, 9, BLACK);
  setHeader();
  drawPlayer(player.x, player.y);
  timeDisplayed = 0;
}

//Initialize the buttons
void buttonSetup(){
  pinMode(shootBtn, INPUT);
  pinMode(jetBtn, INPUT);
}

void setup() {
  TFT.initR(INITR_BLACKTAB);
  TFT.setRotation(2);
  drawMenu();
  buttonSetup();
}

//Drawing the screen after the player dies.
void drawDeathScreen(){
  if(timeDisplayed > topScore) topScore = timeDisplayed;
  TFT.fillScreen(RED);
  TFT.setCursor(13,47);
  TFT.setTextColor(WHITE);
  TFT.setTextSize(2);
  TFT.print("You Died!");
  TFT.setCursor(1,70);
  TFT.setTextSize(1);
  TFT.print("You Lasted: ");
  TFT.setCursor(66,70);
  TFT.print(timeDisplayed);
  TFT.setCursor(80, 70);
  TFT.print("seconds");
  delay(5000);
  gameState = MENU;
}

//Draws the main menu screen
void drawMenu(){
  TFT.fillScreen(BLUE);
  TFT.setTextColor(WHITE);
  TFT.setCursor(4,6);
  TFT.setTextSize(2);
  TFT.print("Bouncy Boy");
  TFT.drawRect(30,55,68,30,BLACK);
  TFT.fillRect(31,56,66,28,GREEN);
  TFT.setCursor(48,65);
  TFT.setTextSize(1);
  TFT.setTextColor(BLACK);
  TFT.print("Begin!");
  TFT.setTextColor(WHITE);
  TFT.setCursor(30,90);
  TFT.print("Top Score:");
  TFT.setCursor(93,90);
  TFT.print(topScore);
  while(gameState == MENU){
    delay(10);
    if(digitalRead(shootBtn) == HIGH){
      loadGame();
      gameState = GAME;}
  }
}

void loop() {
  if(gameState == GAME){
    timeTrack();
    horizontalMovement();
    verticalMovement();
    buttonUpdate();
    checkBounds();
    targetUpdate();
    boostUpdate();
    drawPlayer(player.x, player.y);
    checkLives();
    updateScore();
  } else if (gameState == MENU){
    //Draw the menu and handle new button movement
    drawMenu();
  } else if(gameState == DEATH){
    drawDeathScreen();
  }
}
