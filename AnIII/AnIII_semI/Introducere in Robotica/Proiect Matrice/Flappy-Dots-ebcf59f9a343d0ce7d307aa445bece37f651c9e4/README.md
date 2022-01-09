# Matrix Project: Flappy Dots
<br/>

## Requirements

Flappy Bird game adaptation using Arduino Uno. 
The menu of the game is displayed on a Liquid Crystal Display. The main menu contains the Start Game, Settings, Highest Scores and About sections. 
The game is played on a 8x8 matrix.
The navigation in the menu and playing the game are possible using a joystick. 

<br/>

## Implementation Details

A greeting containing the name of the game is displayed when the game is launched. After 5 seconds the menu appears and the current menu item is indicated with a right arrow pointing towards it. With a joystick, the navigation through the menu is possible. When the button is pressed, an action occurs based on the current item selected: 

- **Start game**: a new game starts and the message "Game Started" is displayed.
- **Settings**: there are available settings for LCD contrast and brightness and matrix brightness
- **Highest Scores**: the first 3 highest scores are displayed along with the name of the player who achieved them
- **About**: the name of the game, author and github repository are displayed on separate lines. 

<br/>

### Game logic
- In the begining, the "bird" is formed from a single dot floating on the first column of the matrix. 
- An obstacle similar to those used in Flappy Bird is generated on the last column of the matrix. The obstacle travels towards the "bird" that must avoid it. If the obstacle is succesfully avoided, the score increases and a new obstacle is generated.
- If the player is inactive for a certain amount of time, the "bird" will fall one position. If the bird touches the bottom row, the player loses the game and a message is shown along with the score. 
- The current level is passed if the score passes a certain benchmark. The difficulty is increased by increasing the speed of the obstacles. At a certain level, the "bird" transforms from one dot into two dots. 

<br/>

## Setup picture phase 1
![](https://github.com/StefaniaCarutasu/Flappy-Dots/blob/main/setup_pictures/setup_picture_phase1.jpeg)

## Setup picture phase 2
![](https://github.com/StefaniaCarutasu/Flappy-Dots/blob/main/setup_pictures/setup_picture_phase2.jpeg)
