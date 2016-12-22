void coord(int * x, int * y, int * z);

//Max x-coordinates the player can move to, since there are walls.
#define leftMax_co 41
#define rightMax_co 87

//Initial coordinates of the player.
#define X_INIT_CO 64
#define Y_INIT_CO 19

static int buttonState = 0;
static int buttonState2 = 0;
static int duck = 0;
static boolean  ducked = false;
static boolean jumped = false, top = false;
static int jump = 0;
static int x, y, z;
static int * xp = & x, * yp = & y, * zp = & z;
static int left = -1, right = 1;
static int direction;

//Character jumps when up button is pressed
int jumpYCo(int y_co) {
  //If the character is ducking, do not jump until finished.
  if (y_co > 19) return y_co;
  buttonState = digitalRead(buttonPinUp);
  
  //If the jump is complete, reset variables.
  if (jumped) {
    jump = 0;
    jumped = false;
    top = false;
  }
  //If button is pressed and person has not jumped, start the jump.
  //Otherwise, do not jump until player is on ground level.
  if (buttonState == HIGH && jump == 0 && !jumped) jump++;
  
  if (jump > 0) {
    //The jump is complete.
    if (y_co == Y_INIT_CO && top) {
      jumped = true;
      top = false;
      return y_co;
    }
    if (top) y_co += 1; //If top is reached, player starts falling.
    if (y_co == 3) top = true; //Reached top.
    //If top of jump isn't reached, player starts rising.
    if (y_co > 3 && !top) y_co -= 1; 
  }
  return y_co;
}

//Player ducks when lower button is pressed.
int duckYCo(int y_co) {
  //If the player is in a jump, do not duck until finished.
  if (y_co < 19) return y_co;
  
  buttonState2 = digitalRead(buttonPinDown);
  //If the duck is complete, reset variables.
  if (ducked == 1) {
    y_co = 19;
    duck = 0;
    ducked = false;
  }
  //If the button is pressed and person has not ducked, start ducking.
  if (buttonState2 == HIGH && !ducked) duck++;

  //Caps the duck variable's value to 30 to prevent overflow.
  if (duck > 30) duck = 30;
  if (duck > 0) {
    //Makes the duck time at lesat 30 iterations long(0.45s)
    if (y_co == 25 && duck >= 30) {
      ducked = true;
      return y_co;
    }
    duck++;
    y_co = 25;
  }
  return y_co;
}

//Used the x-acceleration to move the character.
int accelXCo(int x_co) {
  coord(xp, yp, zp);

  if (x < 0) direction = right;
  else if (x > 0) direction = left;
  
  if (x != 0) {
    if (x_co + direction >= leftMax_co && x_co + direction <= rightMax_co) {
      x_co += direction;
    }
  }
  return x_co;
}
