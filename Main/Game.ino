#define INIT_SPEED 4
#define CYCLES_PER_SECOND 67

int jumpYCo(int y_co);
int duckYCo(int y_co);
int accelXCo(int x_co);

int checkCollision(int x_co, int y_co);
void continuousArray();
void initRandomGen();
void printArray();
void moveArray();
void refreshArray();

void drawInitCharacter();
void drawCharacter(int x_co, int y_co);

void drawTree(int x_co, int y_co);
void drawEdge();
void showInstructions();

static int x_co = X_INIT_CO; //initial coordinates
static int y_co = Y_INIT_CO;
static int speed = INIT_SPEED; // rate at which the game moves
//initalise game terrain, initalise character, pressed a button
static boolean start = false, startGame = false, pressed = false; 
//Timing variables for homescreen.
static int homeCycles=0, flash=0;
//Timing variables for game.
static int iterations = 0, cycles = 0, seconds = 0;
static int score = 0;
static boolean instructions = true; // show instructions on button click

void homeScreen() {
  //If lower button isn't pressed, display homescreen.
  if (!pressed) {
    OrbitOledClearBuffer();
    OrbitOledSetCharUpdate(0);

    //After 15 iterations, flash incremented.
    if(homeCycles==15){
      flash++;
      homeCycles=0;
    }
    //Title flashes every second time.
    if(flash%2==0){
      OrbitOledSetCursor(1, 1);
      OrbitOledPutString("Run Trevor Run");
    }
    OrbitOledSetCursor(0, 4);
    OrbitOledPutString("  Duck to start");

    //Draws the initial character at start of game.
    if(!startGame){
      drawInitCharacter();
      startGame=true;
    }
    x_co = accelXCo(x_co);
    y_co = jumpYCo(y_co);
    y_co = duckYCo(y_co);  
    drawCharacter(x_co,y_co);
    
    OrbitOledUpdate();
    homeCycles++;
    delay(15);
  }
  
  if (digitalRead(buttonPinDown) == HIGH) {
    if (instructions) showInstructions();
    pressed = true;
  }
}

void moveCharacter() {

  if (pressed) {
    if (!start) { //initalise random terrain
      score = 0;
      initRandomGen();
      start = true;
    }

    OrbitOledClearBuffer();
    score++;

    if(iterations > speed) iterations = speed;

    //Obstacles are moved depending on speed variable.
    if (!(iterations % speed)) {
      moveArray();
      continuousArray();
      iterations = 0;
    }
    if (seconds == 30) speed = INIT_SPEED - 1;
    else if (seconds == 60) speed = INIT_SPEED - 2;
    else if (seconds == 90) speed = INIT_SPEED - 3;
    

    if (cycles == CYCLES_PER_SECOND) {
      seconds++;
      cycles = 0;
    }

    x_co = accelXCo(x_co);
    y_co = jumpYCo(y_co);
    y_co = duckYCo(y_co);

    //Prints obstacle array.
    printArray();
    drawEdge();
    drawCharacter(x_co, y_co);

    OrbitOledUpdate();

    //When player collides with obstacle, all variables are reset.
    if (checkCollision(x_co, y_co) == 1) {
      OrbitOledSetCursor(3, 0);
      printArray();
      drawCharacter(x_co, y_co);
      drawEdge();

      OrbitOledPutString("-GAME OVER-");
      OrbitOledUpdate();
      delay(600);
      OrbitOledClear();
      OrbitOledSetCursor(5, 2);
      OrbitOledPutString("SCORE");
      OrbitOledSetCursor(11, 2);
      char scoreBuffer[1000];
      OrbitOledPutString(itoa(score / 40 - 4, scoreBuffer, 10));
      OrbitOledUpdate();

      refreshArray();
      pressed = false;
      start = false;
      speed = INIT_SPEED;
      instructions = true;
      seconds = 0;
      delay(2000);
    }

    iterations++;
    cycles++;
    delay(15);
  }
}

void showInstructions() {

  OrbitOledClear();

  OrbitOledSetCursor(10, 0);
  OrbitOledPutString("JUMP o");

  OrbitOledSetCursor(10, 1);
  OrbitOledPutString("DUCK o");

  OrbitOledSetCursor(8, 3);
  OrbitOledPutString("3");
  OrbitOledUpdate();
  delay(1000);

  OrbitOledSetCursor(8, 3);
  OrbitOledPutString("2");
  OrbitOledUpdate();
  delay(1000);

  OrbitOledSetCursor(8, 3);
  OrbitOledPutString("1");
  OrbitOledUpdate();

  delay(1000);
  instructions = false;

}
