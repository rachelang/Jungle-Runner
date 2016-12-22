#include <stdio.h>

#define FREE_SPACE  0      //         you cant see it because it's a free SPACE :p
#define SOLID_WALL  1     //       |||
#define LONG_HURDLE 2    //        |--|
#define HURDLE 5        //         |-|
#define RIVER 6        //          ===
#define LEG_POSITION -7


void drawCharacter(int x_co, int y_co);
void drawRiver(int x_co, int y_co);
void drawHurdle(int x_co, int y_co);
void drawLongHurdle(int x_co, int y_co);
void drawLogLeft(int x_co, int y_co);
void drawLogRight(int x_co, int y_co);
void randomTerrainGen(int a[][3], int n);

static int a[40][3] = { 
  0 
}; //will contain Random generated terrain.
static int count = 0;
static int yCoArray[5][5] = {0}; //Temporary display for obstacle array.

int checkCollision(int x_co, int y_co) { // standing means neither in a jump state nor a duck state
  for (int i = 0; i < 5; i++) {
    int y_coObj = yCoArray[i][0];
    //If the character and obstacle are at same Y check for collision in X
    if (y_coObj == 23 && (y_co == Y_INIT_CO || y_co == 25)) {
      for (int j = 1; j < 4; j++) {
        int x_coObj = 42 + (j - 1) * 16 + (j - 1) * 2;

        if (yCoArray[i][j] == RIVER && y_coObj >= 23 && y_coObj <= 31) { // if the person is standing or has ducked &  the hurdle is a river
          return 1; // detect collision
        }
        if (yCoArray[i][j] == SOLID_WALL) { // if it's a solid wall and the person is within the limist of it's x cordinates
          if (x_co >= x_coObj && x_co <= x_coObj + OBSTACLE_LENGTH) return 1; // detect collision
        }
        if (yCoArray[i][j] == LONG_HURDLE) {
          //If ducked but character is in front of a hurdle leg, detect collision
          if (y_co == 25) {
            if ((x_co <= x_coObj && x_co >= x_coObj + LEG_POSITION) || (x_co >= x_coObj + LONG_HURDLE_LENGTH + LEG_POSITION && x_co <= x_coObj + LONG_HURDLE_LENGTH))
              return 1;
          } else if (x_co >= x_coObj && x_co <= x_coObj + LONG_HURDLE_LENGTH) return 1; // if the pesron is standing and withing the limits of hurdle inclusive of legs detect colision
        }
        if (yCoArray[i][j] == HURDLE) {
          //If ducked but character is in front of a hurdle leg, detect collision.
          if (y_co == 25) {
            if ((x_co <= x_coObj && x_co >= x_coObj + LEG_POSITION) || (x_co >= x_coObj + OBSTACLE_LENGTH + LEG_POSITION && x_co <= x_coObj + OBSTACLE_LENGTH)) 
              return 1;
          } else if (x_co >= x_coObj && x_co <= x_coObj + OBSTACLE_LENGTH) return 1; // if the pesron is standing and withing the limits of hurdle inclusive of legs detect colision
        }
      }
    }
  }
  return 0;
}

void refreshArray() {
  for (int i = 0; i < 40; i++) {
    for (int j = 0; j < 3; j++) {
      a[i][j] = 0;
    }
  }
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 5; j++) {
      yCoArray[i][j] = 0;
    }
  }
  count = 0;
}

//Draws the obstacles in the array on the screen.
void printArray() {
  for (int i = 0; i < 5; i++) {
    //Draw all 3 obstacles for the row.
    if (yCoArray[i][4] == 1) {
      for (int j = 1; j < 4; j++) {
        int x_co = 42 + (j - 1) * 16 + (j - 1) * 2;
        if (yCoArray[i][0] == -8) yCoArray[i][0] = 0;
        if (yCoArray[i][j] == 6) {
          drawRiver(x_co, yCoArray[i][0]);
          break;
        }
        if (yCoArray[i][j] == 1) {
          drawWall(x_co, yCoArray[i][0]);
        }
        if (yCoArray[i][j] == 2) {
          drawLongHurdle(x_co, yCoArray[i][0]);
        }
        if (yCoArray[i][j] == 5) {
          drawHurdle(x_co, yCoArray[i][0]);
        }
      }
    }
  }
}

void moveArray() {
  //If there are no obstacles, initializes first 5 rows.
  if (yCoArray[0][4] == 0) {
    int num = -8;
    //Accesses the 5 temporary obstacle rows.
    for (int i = 0; i < 5; i++) {
      //Writes number of obstacle into the temp array.
      for (int j = 1; j < 4; j++) {
        yCoArray[i][0] = -16 + i * num;
        yCoArray[i][j] = a[count][j - 1];
      }
      count++;
      yCoArray[i][4] = 1;
    }
  }

  //When a row reaches the bottom of screen, replaces its contents
  for (int i = 0; i < 5; i++) {
    if (yCoArray[i][0] == 32) {
      for (int j = 1; j < 4; j++) {
        yCoArray[i][0] = -16;
        yCoArray[i][j] = a[count][j - 1];
      }
      if (count == 39) count = 0;
      else count++;
    }
  }

  //Move the obstacles.
  for (int i = 0; i < 5; i++) {
    if (yCoArray[i][4] == 1)
      yCoArray[i][0]++;
  }
}

void initRandomGen() {
    randomTerrainGen(a + 2, 38);
  }
  
  
  // Instead of creating an array of a really large size or using a data structure like vector we can re-initalise the current array
  // and set the interations back to 0, or iterations %= 40 to ensure a continual list of random obstacles.
void continuousArray() {
  //When at 38, re-generates the first 37 rows
  if (count == 37) {
    randomTerrainGen(a, 37);
    //Ensures that there is a space after next random gen.
    for (int i = 0; i < 3; i++) {
      a[0][i] = 0;
    }
  }
  //When at 0, re-generates the last 3 rows
  if (count == 0) {
    randomTerrainGen(a + 37, 3);
    for (int i = 0; i < 3; i++) {
      a[36][i] = 0;
    }
  }
}

//Sets empty rows in array
void setPadding(int a[][3], int & i, int n) { // free spaces between two row of hurdles
  int padding = random(2) + 2;
  i++;

  for (int q = i; q < q + padding && q < n; ++q) {
    for (int j = 0; j < 3; ++j)
      a[q][j] = 0;
  }

  i = i + padding - 1 < n ? i + padding - 1 : n;
}

void randomTerrainGen(int a[][3], int n) {

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 3; ++j) {

      int river = random(20);
      // 2 in 20 chance for hurdle
      if (river == 17 || river == 5) {
        a[i][0] = a[i][1] = a[i][2] = RIVER;
        setPadding(a, i, n);
        break;
      }

      int hurdle = random(8);
      if (hurdle == 6) { // 1 in 8 chance for hurdle
        a[i][j] = HURDLE;
        if (j == 2) setPadding(a, i, n);
        continue;
      }
      a[i][j] = random(3);
      if (j == 2)
      while (a[i][j] == LONG_HURDLE) a[i][j] = random(2);
      //can't have a long hurdle start in the last coloumn

      if (a[i][j] == LONG_HURDLE) a[i][++j] = FREE_SPACE; // for long hurdle the next element must empty so that it's not re-drawn over

      if (j == 2) {
        setPadding(a, i, n);
      }
    }
  }
}
