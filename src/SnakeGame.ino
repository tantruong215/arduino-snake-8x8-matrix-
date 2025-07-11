// SnakeGame.ino
#include <LedControl.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>

// ---------------------- user config ----------------------
struct Pin {
  static const short joystickX         = A2;
  static const short joystickY         = A3;
  static const short joystickVCC       = 15;
  static const short joystickGND       = 14;
  static const short potentiometer     = A5;
  static const short CLK               = 10;
  static const short CS                = 11;
  static const short DIN               = 12;
  static const short buttonPin         = 2;
  static const short intensity         = 6;
  static const short initialSnakeLength= 3;
  static constexpr float logarithmity  = 0.4;
  static const int joystickThreshold   = 160;
};

LedControl matrix(Pin::DIN, Pin::CLK, Pin::CS, 1);
const int HI_SCORE_ADDR = 0;

enum GameMode { CLASSIC, WALL_HIT, SPEED_CHALLENGE, REVERSE };
const int numModes = 4;
const char* modeNames[numModes] = {
  \"1:WRAP\", \"2:WALL\", \"3:SPEED\", \"4:REVRS\"
};

struct Point { int row, col; Point(int r=0,int c=0):row(r),col(c){} };
struct Coordinate { int x, y; Coordinate(int _x=0,int _y=0):x(_x),y(_y){} };

GameMode currentMode = CLASSIC;
bool invertedControls = false;
Point snake;
Point food(-1,-1);
int gameboard[8][8] = {};
int snakeLength = Pin::initialSnakeLength;
int snakeSpeed;
int snakeDirection = 0;
bool win = false, gameOver = false, paused = false;
int highScore = 0;

// PROGMEM bitmaps (paste your original arrays here)
const PROGMEM bool snakeMessage[8][56] = { /* ... */ };
const PROGMEM bool gameOverMessage[8][90] = { /* ... */ };
const PROGMEM bool scoreMessage[8][58] = { /* ... */ };
const PROGMEM bool digits[][8][8] = { /* ... */ };

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void scrollBitmap(const bool bmp[][8], int width) {
  for(int d=0; d<width-7; d++){
    for(int col=0; col<8; col++){
      delay(50);
      for(int row=0; row<8; row++){
        matrix.setLed(0,row,col, pgm_read_byte(&bmp[row][col+d]));
      }
    }
  }
  matrix.clearDisplay(0);
}

void showDigit(int d, int ms=500){
  for(int t=0; t<ms/50; t++){
    for(int row=0; row<8; row++){
      for(int col=0; col<8; col++){
        matrix.setLed(0,row,col, pgm_read_byte(&digits[d][row][col]));
      }
    }
    delay(50);
  }
  matrix.clearDisplay(0);
}

void showModeSelect(){
  int modeIdx = 0;
  unsigned long lastClick = 0;
  int lvl = map(analogRead(Pin::potentiometer), 0,1023,1,4);
  while(true){
    showDigit(modeIdx);
    if(digitalRead(Pin::buttonPin)==LOW && millis()-lastClick>200){
      lastClick = millis();
      modeIdx = (modeIdx+1) % numModes;
    }
    if(digitalRead(Pin::buttonPin)==LOW && millis()-lastClick>1000){
      currentMode = GameMode(modeIdx);
      snakeSpeed = map(lvl,1,4,600,150);
      return;
    }
  }
}

void showPausedScreen(bool p){
  matrix.clearDisplay(0);
  if(p){
    for(int i=0;i<3;i++){
      matrix.setRow(0,3,0xFF);
      delay(200);
      matrix.clearDisplay(0);
      delay(200);
    }
  }
}

void showTrophy(){
  for(int i=0;i<3;i++){
    matrix.setIntensity(0,15);
    for(int r=0;r<8;r++){
      for(int c=0;c<8;c++){
        matrix.setLed(0,r,c,1);
      }
    }
    delay(200);
    matrix.clearDisplay(0);
    delay(200);
  }
  matrix.setIntensity(0,Pin::intensity);
}

void resetGame(){
  win = gameOver = false;
  snakeLength = Pin::initialSnakeLength;
  snakeDirection = 0;
  food = {-1,-1};
  memset(gameboard,0,sizeof(gameboard));
  matrix.clearDisplay(0);
  snake.row = random(8);
  snake.col = random(8);
}

void generateFood(){
  if(food.row<0){
    if(snakeLength>=64){
      win = true;
      return;
    }
    do{
      food.col = random(8);
      food.row = random(8);
    } while(gameboard[food.row][food.col] > 0);
  }
}

Coordinate joystickHome(500,500);
void calibrateJoystick(){
  long sx = 0, sy = 0;
  for(int i=0;i<10;i++){
    sx += analogRead(Pin::joystickX);
    sy += analogRead(Pin::joystickY);
  }
  joystickHome.x = sx/10;
  joystickHome.y = sy/10;
}

void scanJoystick(){
  int prevDir = snakeDirection;
  unsigned long t0 = millis();
  while(millis() < t0 + snakeSpeed){
    float raw = mapf(analogRead(Pin::potentiometer),0,1023,0,1);
    snakeSpeed = mapf(pow(raw,3.5),0,1,10,1000);
    if(snakeSpeed < 1) snakeSpeed = 1;
    int y = analogRead(Pin::joystickY), x = analogRead(Pin::joystickX), dir = 0;
    if(y < joystickHome.y - Pin::joystickThreshold) dir = 1;
    if(y > joystickHome.y + Pin::joystickThreshold) dir = 3;
    if(x < joystickHome.x - Pin::joys
# PowerShell script to update your local repo with the full SnakeGame sketch,
# rebase on remote, and push your changes.

# 1) Configure your local repo path:
C:\Users\idyet\Projects\arduino-snake-8x8-matrix- = Join-Path C:\Users\idyet 'Projects\arduino-snake-8x8-matrix-'

if (-Not (Test-Path C:\Users\idyet\Projects\arduino-snake-8x8-matrix-)) {
    Write-Error "Repo folder not found: C:\Users\idyet\Projects\arduino-snake-8x8-matrix-"
    exit 1
}

# 2) Enter the repo
Set-Location C:\Users\idyet\Projects\arduino-snake-8x8-matrix-

# 3) Sync with remote main
Write-Host "🔄 Fetching and rebasing on origin/main..."
git fetch origin main
git rebase origin/main

# 4) Overwrite src/SnakeGame.ino with the full corrected code
// SnakeGame.ino
#include <LedControl.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>

// ---------------------- user config ----------------------
struct Pin {
  static const short joystickX         = A2;
  static const short joystickY         = A3;
  static const short joystickVCC       = 15;
  static const short joystickGND       = 14;
  static const short potentiometer     = A5;
  static const short CLK               = 10;
  static const short CS                = 11;
  static const short DIN               = 12;
  static const short buttonPin         = 2;
  static const short intensity         = 6;
  static const short initialSnakeLength= 3;
  static constexpr float logarithmity  = 0.4;
  static const int joystickThreshold   = 160;
};

LedControl matrix(Pin::DIN, Pin::CLK, Pin::CS, 1);

// ---------------------- EEPROM ----------------------------
const int HI_SCORE_ADDR = 0;

// ---------------------- game enums -----------------------
enum GameMode { CLASSIC, WALL_HIT, SPEED_CHALLENGE, REVERSE };
const int numModes = 4;
const char* modeNames[numModes] = {
  \"1:WRAP\", \"2:WALL\", \"3:SPEED\", \"4:REVRS\"
};

// ---------------------- helper types ---------------------
struct Point { int row, col; Point(int r=0,int c=0):row(r),col(c){} };
struct Coordinate { int x, y; Coordinate(int _x=0,int _y=0):x(_x),y(_y){} };

// ---------------------- globals --------------------------
GameMode currentMode = CLASSIC;
bool invertedControls = false;

Point snake;
Point food(-1,-1);
int gameboard[8][8] = {};

int snakeLength = Pin::initialSnakeLength;
int snakeSpeed;
int snakeDirection = 0;

bool win = false, gameOver = false, paused = false;
int highScore = 0;

// ---------------------- PROGMEM bitmaps ------------------
// (paste your original full arrays here:)
const PROGMEM bool snakeMessage[8][56] = {
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,1,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,1,1,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,1,1,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,0,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0}
};

const PROGMEM bool gameOverMessage[8][90] = {
  /* your original 8×90 array here */
};

const PROGMEM bool scoreMessage[8][58] = {
  /* your original 8×58 array here */
};

const PROGMEM bool digits[][8][8] = {
  /* your original digits array here */
};

// ---------------------------------------------------------------
float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void scrollBitmap(const bool bmp[][8], int width) {
  for(int d=0; d<width-7; d++){
    for(int col=0; col<8; col++){
      delay(50);
      for(int row=0; row<8; row++){
        matrix.setLed(0,row,col, pgm_read_byte(&bmp[row][col+d]));
      }
    }
  }
  matrix.clearDisplay(0);
}

void showDigit(int d, int ms=500){
  for(int t=0; t<ms/50; t++){
    for(int row=0; row<8; row++){
      for(int col=0; col<8; col++){
        matrix.setLed(0,row,col, pgm_read_byte(&digits[d][row][col]));
      }
    }
    delay(50);
  }
  matrix.clearDisplay(0);
}

void showModeSelect(){
  int modeIdx = 0;
  unsigned long lastClick = 0;
  int lvl = map(analogRead(Pin::potentiometer), 0,1023,1,4);
  while(true){
    showDigit(modeIdx);
    if(digitalRead(Pin::buttonPin)==LOW && millis()-lastClick>200){
      lastClick = millis();
      modeIdx = (modeIdx+1) % numModes;
    }
    if(digitalRead(Pin::buttonPin)==LOW && millis()-lastClick>1000){
      currentMode = GameMode(modeIdx);
      snakeSpeed = map(lvl,1,4,600,150);
      return;
    }
  }
}

void showPausedScreen(bool p){
  matrix.clearDisplay(0);
  if(p){
    for(int i=0;i<3;i++){
      matrix.setRow(0,3,0xFF);
      delay(200);
      matrix.clearDisplay(0);
      delay(200);
    }
  }
}

void showTrophy(){
  for(int i=0;i<3;i++){
    matrix.setIntensity(0,15);
    for(int r=0;r<8;r++){
      for(int c=0;c<8;c++){
        matrix.setLed(0,r,c,1);
      }
    }
    delay(200);
    matrix.clearDisplay(0);
    delay(200);
  }
  matrix.setIntensity(0,Pin::intensity);
}

void resetGame(){
  win = gameOver = false;
  snakeLength = Pin::initialSnakeLength;
  snakeDirection = 0;
  food = {-1,-1};
  memset(gameboard,0,sizeof(gameboard));
  matrix.clearDisplay(0);
  snake.row = random(8);
  snake.col = random(8);
}

void generateFood(){
  if(food.row<0){
    if(snakeLength>=64){
      win = true;
      return;
    }
    do{
      food.col = random(8);
      food.row = random(8);
    } while(gameboard[food.row][food.col] > 0);
  }
}

Coordinate joystickHome(500,500);
void calibrateJoystick(){
  long sx = 0, sy = 0;
  for(int i=0;i<10;i++){
    sx += analogRead(Pin::joystickX);
    sy += analogRead(Pin::joystickY);
  }
  joystickHome.x = sx/10;
  joystickHome.y = sy/10;
}

void scanJoystick(){
  int prevDir = snakeDirection;
  unsigned long t0 = millis();
  while(millis() < t0 + snakeSpeed){
    float raw = mapf(analogRead(Pin::potentiometer),0,1023,0,1);
    snakeSpeed = mapf(pow(raw,3.5),0,1,10,1000);
    if(snakeSpeed < 1) snakeSpeed = 1;
    int y = analogRead(Pin::joystickY), x = analogRead(Pin::joystickX), dir = 0;
    if(y < joystickHome.y - Pin::joystickThreshold) dir = 1;
    if(y > joystickHome.y + Pin::joystickThreshold) dir = 3;
    if(x < joystickHome.x - Pin::joystickThreshold) dir = 4;
    if(x > joystickHome.x + Pin::joystickThreshold) dir = 2;
    if(currentMode==REVERSE && invertedControls){
      if(dir==1) dir=3; else if(dir==3) dir=1;
      if(dir==4) dir=2; else if(dir==2) dir=4;
    }
    if(dir+2==prevDir || dir-2==prevDir) dir = prevDir;
    snakeDirection = dir;
    matrix.setLed(0,food.row,food.col,(millis()%100 < 50)?1:0);
  }
}

void fixEdge(){
  if(currentMode==WALL_HIT){
    if(snake.row<0 || snake.row>7 || snake.col<0 || snake.col>7){
      gameOver = true;
      return;
    }
  } else {
    snake.col = (snake.col + 8) % 8;
    snake.row = (snake.row + 8) % 8;
  }
}

void calculateSnake(){
  switch(snakeDirection){
    case 1: snake.row--; break;
    case 2: snake.col++; break;
    case 3: snake.row++; break;
    case 4: snake.col--; break;
    default: return;
  }
  fixEdge();
  if(gameOver) return;
  matrix.setLed(0,snake.row,snake.col,1);
  if(gameboard[snake.row][snake.col] > 1 && snakeDirection){
    gameOver = true;
    return;
  }
  if(snake.row==food.row && snake.col==food.col){
    food = {-1,-1};
    snakeLength++;
    if(currentMode==SPEED_CHALLENGE) snakeSpeed = max(30, snakeSpeed-20);
    if(currentMode==REVERSE && snakeLength%5==0) invertedControls = !invertedControls;
    for(int r=0;r<8;r++){
      for(int c=0;c<8;c++){
        if(gameboard[r][c] > 0) gameboard[r][c]++;
      }
    }
  }
  gameboard[snake.row][snake.col] = snakeLength + 1;
  for(int r=0;r<8;r++){
    for(int c=0;c<8;c++){
      if(gameboard[r][c] > 0){
        gameboard[r][c]--;
        matrix.setLed(0,r,c, gameboard[r][c] ? 1 : 0);
      }
    }
  }
}

void handleGameStates(){
  if(gameOver || win){
    int score = snakeLength - Pin::initialSnakeLength;
    if(score > highScore){
      highScore = score;
      EEPROM.write(HI_SCORE_ADDR, highScore);
      showTrophy();
    }
    scrollBitmap(gameOver ? gameOverMessage : scoreMessage,
                 gameOver ? 90 : 58);
    resetGame();
  }
}

void initialize(){
  pinMode(Pin::joystickVCC, OUTPUT); digitalWrite(Pin::joystickVCC, HIGH);
  pinMode(Pin::joystickGND, OUTPUT); digitalWrite(Pin::joystickGND, LOW);
  pinMode(Pin::buttonPin, INPUT_PULLUP);
  matrix.shutdown(0, false);
  matrix.setIntensity(0, Pin::intensity);
  matrix.clearDisplay(0);
  randomSeed(analogRead(A5));
  snake.row = random(8);
  snake.col = random(8);
}

void setup(){
  Serial.begin(115200);
  initialize();
  calibrateJoystick();
  highScore = EEPROM.read(HI_SCORE_ADDR);
  showModeSelect();
  scrollBitmap(snakeMessage, 56);
}

void loop(){
  if(digitalRead(Pin::buttonPin) == LOW){
    delay(50);
    if(digitalRead(Pin::buttonPin) == LOW){
      paused = !paused;
      showPausedScreen(paused);
      if(paused){
        unsigned long start = millis();
        while(digitalRead(Pin::buttonPin)==LOW){
          if(millis() - start > 2000){
            resetGame();
            paused = false;
            break;
          }
        }
      }
    }
  }
  if(paused) return;
  generateFood();
  scanJoystick();
  calculateSnake();
  handleGameStates();
} = @"
// SnakeGame.ino
#include <LedControl.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>

// ---------------------- user config ----------------------
struct Pin {
  static const short joystickX         = A2;
  static const short joystickY         = A3;
  static const short joystickVCC       = 15;
  static const short joystickGND       = 14;
  static const short potentiometer     = A5;
  static const short CLK               = 10;
  static const short CS                = 11;
  static const short DIN               = 12;
  static const short buttonPin         = 2;
  static const short intensity         = 6;
  static const short initialSnakeLength= 3;
  static constexpr float logarithmity  = 0.4;
  static const int joystickThreshold   = 160;
};

LedControl matrix(Pin::DIN, Pin::CLK, Pin::CS, 1);
const int HI_SCORE_ADDR = 0;

enum GameMode { CLASSIC, WALL_HIT, SPEED_CHALLENGE, REVERSE };
const int numModes = 4;
const char* modeNames[numModes] = {
  \"1:WRAP\", \"2:WALL\", \"3:SPEED\", \"4:REVRS\"
};

struct Point { int row, col; Point(int r=0,int c=0):row(r),col(c){} };
struct Coordinate { int x, y; Coordinate(int _x=0,int _y=0):x(_x),y(_y){} };

GameMode currentMode = CLASSIC;
bool invertedControls = false;
Point snake;
Point food(-1,-1);
int gameboard[8][8] = {};
int snakeLength = Pin::initialSnakeLength;
int snakeSpeed;
int snakeDirection = 0;
bool win = false, gameOver = false, paused = false;
int highScore = 0;

// PROGMEM bitmaps (paste your original arrays here)
const PROGMEM bool snakeMessage[8][56] = { /* ... */ };
const PROGMEM bool gameOverMessage[8][90] = { /* ... */ };
const PROGMEM bool scoreMessage[8][58] = { /* ... */ };
const PROGMEM bool digits[][8][8] = { /* ... */ };

float mapf(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void scrollBitmap(const bool bmp[][8], int width) {
  for(int d=0; d<width-7; d++){
    for(int col=0; col<8; col++){
      delay(50);
      for(int row=0; row<8; row++){
        matrix.setLed(0,row,col, pgm_read_byte(&bmp[row][col+d]));
      }
    }
  }
  matrix.clearDisplay(0);
}

void showDigit(int d, int ms=500){
  for(int t=0; t<ms/50; t++){
    for(int row=0; row<8; row++){
      for(int col=0; col<8; col++){
        matrix.setLed(0,row,col, pgm_read_byte(&digits[d][row][col]));
      }
    }
    delay(50);
  }
  matrix.clearDisplay(0);
}

void showModeSelect(){
  int modeIdx = 0;
  unsigned long lastClick = 0;
  int lvl = map(analogRead(Pin::potentiometer), 0,1023,1,4);
  while(true){
    showDigit(modeIdx);
    if(digitalRead(Pin::buttonPin)==LOW && millis()-lastClick>200){
      lastClick = millis();
      modeIdx = (modeIdx+1) % numModes;
    }
    if(digitalRead(Pin::buttonPin)==LOW && millis()-lastClick>1000){
      currentMode = GameMode(modeIdx);
      snakeSpeed = map(lvl,1,4,600,150);
      return;
    }
  }
}

void showPausedScreen(bool p){
  matrix.clearDisplay(0);
  if(p){
    for(int i=0;i<3;i++){
      matrix.setRow(0,3,0xFF);
      delay(200);
      matrix.clearDisplay(0);
      delay(200);
    }
  }
}

void showTrophy(){
  for(int i=0;i<3;i++){
    matrix.setIntensity(0,15);
    for(int r=0;r<8;r++){
      for(int c=0;c<8;c++){
        matrix.setLed(0,r,c,1);
      }
    }
    delay(200);
    matrix.clearDisplay(0);
    delay(200);
  }
  matrix.setIntensity(0,Pin::intensity);
}

void resetGame(){
  win = gameOver = false;
  snakeLength = Pin::initialSnakeLength;
  snakeDirection = 0;
  food = {-1,-1};
  memset(gameboard,0,sizeof(gameboard));
  matrix.clearDisplay(0);
  snake.row = random(8);
  snake.col = random(8);
}

void generateFood(){
  if(food.row<0){
    if(snakeLength>=64){
      win = true;
      return;
    }
    do{
      food.col = random(8);
      food.row = random(8);
    } while(gameboard[food.row][food.col] > 0);
  }
}

Coordinate joystickHome(500,500);
void calibrateJoystick(){
  long sx = 0, sy = 0;
  for(int i=0;i<10;i++){
    sx += analogRead(Pin::joystickX);
    sy += analogRead(Pin::joystickY);
  }
  joystickHome.x = sx/10;
  joystickHome.y = sy/10;
}

void scanJoystick(){
  int prevDir = snakeDirection;
  unsigned long t0 = millis();
  while(millis() < t0 + snakeSpeed){
    float raw = mapf(analogRead(Pin::potentiometer),0,1023,0,1);
    snakeSpeed = mapf(pow(raw,3.5),0,1,10,1000);
    if(snakeSpeed < 1) snakeSpeed = 1;
    int y = analogRead(Pin::joystickY), x = analogRead(Pin::joystickX), dir = 0;
    if(y < joystickHome.y - Pin::joystickThreshold) dir = 1;
    if(y > joystickHome.y + Pin::joystickThreshold) dir = 3;
    if(x < joystickHome.x - Pin::joystickThreshold) dir = 4;
    if(x > joystickHome.x + Pin::joystickThreshold) dir = 2;
    if(currentMode==REVERSE && invertedControls){
      if(dir==1) dir=3; else if(dir==3) dir=1;
      if(dir==4) dir=2; else if(dir==2) dir=4;
    }
    if(dir+2==prevDir || dir-2==prevDir) dir = prevDir;
    snakeDirection = dir;
    matrix.setLed(0,food.row,food.col,(millis()%100 < 50)?1:0);
  }
}

void fixEdge(){
  if(currentMode==WALL_HIT){
    if(snake.row<0 || snake.row>7 || snake.col<0 || snake.col>7){
      gameOver = true;
      return;
    }
  } else {
    snake.col = (snake.col + 8) % 8;
    snake.row = (snake.row + 8) % 8;
  }
}

void calculateSnake(){
  switch(snakeDirection){
    case 1: snake.row--; break;
    case 2: snake.col++; break;
    case 3: snake.row++; break;
    case 4: snake.col--; break;
    default: return;
  }
  fixEdge();
  if(gameOver) return;
  matrix.setLed(0,snake.row,snake.col,1);
  if(gameboard[snake.row][snake.col] > 1 && snakeDirection){
    gameOver = true;
    return;
  }
  if(snake.row==food.row && snake.col==food.col){
    food = {-1,-1};
    snakeLength++;
    if(currentMode==SPEED_CHALLENGE) snakeSpeed = max(30, snakeSpeed-20);
    if(currentMode==REVERSE && snakeLength%5==0) invertedControls = !invertedControls;
    for(int r=0;r<8;r++){
      for(int c=0;c<8;c++){
        if(gameboard[r][c] > 0) gameboard[r][c]++;
      }
    }
  }
  gameboard[snake.row][snake.col] = snakeLength + 1;
  for(int r=0;r<8;r++){
    for(int c=0;c<8;c++){
      if(gameboard[r][c] > 0){
        gameboard[r][c]--;
        matrix.setLed(0,r,c, gameboard[r][c] ? 1 : 0);
      }
    }
  }
}

void handleGameStates(){
  if(gameOver || win){
    int score = snakeLength - Pin::initialSnakeLength;
    if(score > highScore){
      highScore = score;
      EEPROM.write(HI_SCORE_ADDR, highScore);
      showTrophy();
    }
    scrollBitmap(gameOver ? gameOverMessage : scoreMessage,
                 gameOver ? 90 : 58);
    resetGame();
  }
}

void initialize(){
  pinMode(Pin::joystickVCC, OUTPUT); digitalWrite(Pin::joystickVCC, HIGH);
  pinMode(Pin::joystickGND, OUTPUT); digitalWrite(Pin::joystickGND, LOW);
  pinMode(Pin::buttonPin, INPUT_PULLUP);
  matrix.shutdown(0, false);
  matrix.setIntensity(0, Pin::intensity);
  matrix.clearDisplay(0);
  randomSeed(analogRead(A5));
  snake.row = random(8);
  snake.col = random(8);
}

void setup(){
  Serial.begin(115200);
  initialize();
  calibrateJoystick();
  highScore = EEPROM.read(HI_SCORE_ADDR);
  showModeSelect();
  scrollBitmap(snakeMessage, 56);
}

void loop(){
  if(digitalRead(Pin::buttonPin) == LOW){
    delay(50);
    if(digitalRead(Pin::buttonPin) == LOW){
      paused = !paused;
      showPausedScreen(paused);
      if(paused){
        unsigned long start = millis();
        while(digitalRead(Pin::buttonPin)==LOW){
          if(millis() - start > 2000){
            resetGame();
            paused = false;
            break;
          }
        }
      }
    }
  }
  if(paused) return;
  generateFood();
  scanJoystick();
  calculateSnake();
  handleGameStates();
}
