# Run-Trevor
INTRODUCTION
Run Trevor is a runner game which I coded on Tiva C Series(TM4C123G) connected to the Orbit Booster Pack. My game makes use of most of the elements on the boosterpack, including the accelerometer and buttons for movement, and the LCD screen for hand-drawn bitmap graphics. 

In order to run this program, I recommend using Energia on board selection tmc4c123g (80Mhz) and import the OLED library which is included in this repository. 

CHALLENGES
One of the challenges when creating this game was due to its nature as an endless runner. In order to keep things efficient I made a function to circulate the array without disrupting the random-gen algorithm, so that when the array is overwritten the probabilities of generating certain obstacles would be kept the same. 
